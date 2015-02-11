/*
 * GyroMPU6500.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: dwagstaff
 */

#include "GyroMPU6500.h"

#include <math.h>
#include "Arduino.h"

#include "diag/Trace.h"

#include "string.h"
#include <cstdlib>
extern "C" {
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
}
#include "PWMServoDriver.h"


#define DEBUG_I2C 0

/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (100)



 Wire *GyroMPU6500::_pWire= 0;
 struct int_param_s int_param;




 // Calibration Data
 const float degPulse= 5.6e-6;

static float calData[] __attribute__ ((section(".text"))) = {
		0,
		degPulse * 90,
		degPulse * 10,
		degPulse * 20,
		degPulse * 30,
		degPulse * 40,
		degPulse * 30,
		degPulse * 20,
		degPulse * 10,
		0};

const size_t CAL_COUNT= sizeof(calData) / sizeof(calData[0]);

static float calResult[CAL_COUNT][2];



 /* The sensors can be mounted onto the board in any orientation. The mounting
  * matrix seen below tells the MPL how to rotate the raw data from thei
  * driver(s).
  * TODO: The following matrices refer to the configuration on an internal test
  * board at Invensense. If needed, please modify the matrices to match the
  * chip-to-body matrix for your particular set up.
  */
 static signed char gyro_orientation[9] = {-1, 0, 0,
                                            0,-1, 0,
                                            0, 0, 1};



GyroMPU6500::GyroMPU6500()
: _inMotion(false)
{
	resetPosition();
}

static void tap_cb(unsigned char direction, unsigned char count)
{
//    char data[2];
//    data[0] = (char)direction;
//    data[1] = (char)count;
//    send_packet(PACKET_TYPE_TAP, data);
}

static void android_orient_cb(unsigned char orientation)
{
//    send_packet(PACKET_TYPE_ANDROID_ORIENT, &orientation);
}

/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static inline unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static inline unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}



uint8_t GyroMPU6500::i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len,
		uint8_t* pData) {
#if DEBUG_I2C
	trace_printf("I2C Write: %x:%x %d: ", slaveAddr, regAddr, len);
	for(int i= 0; i < len; i++)
		trace_printf("%02x ", pData[i]);
	trace_putchar('\n');
#endif
	if( !_pWire ) {
		_pWire= new Wire();
		_pWire->begin();
	}
	_pWire->beginTransmission(slaveAddr);
	_pWire->write(regAddr);
	while(len--)
		_pWire->write(*pData++);
	return( _pWire->endTransmission() == 0);

}

bool GyroMPU6500::init(void) {
    int result;
    uint8_t accel_fsr;
    uint16_t gyro_rate, gyro_fsr;

	  result= mpu_init(&int_param);
	  if( result )
		  return false;

	    /* Get/set hardware configuration. Start gyro. */
	    /* Wake up all sensors. */
	    mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
	    /* Push both gyro and accel data into the FIFO. */
	    mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
	    mpu_set_sample_rate(DEFAULT_MPU_HZ);
	    /* Read back configuration in case it was set improperly. */
	    mpu_get_sample_rate(&gyro_rate);
	    mpu_get_gyro_fsr(&gyro_fsr);
	    mpu_get_accel_fsr(&accel_fsr);
	    mpu_set_gyro_fsr(500);

	    /* To initialize the DMP:
	      * 1. Call dmp_load_motion_driver_firmware(). This pushes the DMP image in
	      *    inv_mpu_dmp_motion_driver.h into the MPU memory.
	      * 2. Push the gyro and accel orientation matrix to the DMP.
	      * 3. Register gesture callbacks. Don't worry, these callbacks won't be
	      *    executed unless the corresponding feature is enabled.
	      * 4. Call dmp_enable_feature(mask) to enable different features.
	      * 5. Call dmp_set_fifo_rate(freq) to select a DMP output rate.
	      * 6. Call any feature-specific control functions.
	      *
	      * To enable the DMP, just call mpu_set_dmp_state(1). This function can
	      * be called repeatedly to enable and disable the DMP at runtime.
	      *
	      * The following is a short summary of the features supported in the DMP
	      * image provided in inv_mpu_dmp_motion_driver.c:
	      * DMP_FEATURE_LP_QUAT: Generate a gyro-only quaternion on the DMP at
	      * 200Hz. Integrating the gyro data at higher rates reduces numerical
	      * errors (compared to integration on the MCU at a lower sampling rate).
	      * DMP_FEATURE_6X_LP_QUAT: Generate a gyro/accel quaternion on the DMP at
	      * 200Hz. Cannot be used in combination with DMP_FEATURE_LP_QUAT.
	      * DMP_FEATURE_TAP: Detect taps along the X, Y, and Z axes.
	      * DMP_FEATURE_ANDROID_ORIENT: Google's screen rotation algorithm. Triggers
	      * an event at the four orientations where the screen should rotate.
	      * DMP_FEATURE_GYRO_CAL: Calibrates the gyro data after eight seconds of
	      * no motion.
	      * DMP_FEATURE_SEND_RAW_ACCEL: Add raw accelerometer data to the FIFO.
	      * DMP_FEATURE_SEND_RAW_GYRO: Add raw gyro data to the FIFO.
	      * DMP_FEATURE_SEND_CAL_GYRO: Add calibrated gyro data to the FIFO. Cannot
	      * be used in combination with DMP_FEATURE_SEND_RAW_GYRO.
	      */
	     dmp_load_motion_driver_firmware();
	     dmp_set_orientation(
	         inv_orientation_matrix_to_scalar(gyro_orientation));
	     dmp_register_tap_cb(tap_cb);
	     dmp_register_android_orient_cb(android_orient_cb);
	     /*
	      * Known Bug -
	      * DMP when enabled will sample sensor data at 200Hz and output to FIFO at the rate
	      * specified in the dmp_set_fifo_rate API. The DMP will then sent an interrupt once
	      * a sample has been put into the FIFO. Therefore if the dmp_set_fifo_rate is at 25Hz
	      * there will be a 25Hz interrupt from the MPU device.
	      *
	      * There is a known issue in which if you do not enable DMP_FEATURE_TAP
	      * then the interrupts will be at 200Hz even if fifo rate
	      * is set at a different rate. To avoid this issue include the DMP_FEATURE_TAP
	      */
	     uint16_t features= DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
	    	        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
	    	        DMP_FEATURE_GYRO_CAL;
	     features= DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_TAP;
	     dmp_enable_feature(features);
	     dmp_set_fifo_rate(100);
	     dmp_set_interrupt_mode(DMP_INT_CONTINUOUS);

	     // Compute the intergral period
	     float sens;
	     mpu_get_gyro_sens(&sens);
	     _integralPeriod= sens *  SampleRate;

	     // Compute Zero Motion which is <= 0.5_deg/s
	     _zeroMotion= int16_t(sens) / 2;

	     // Turn on motion detect mode
//	     mpu_lp_motion_interrupt(100, 5, 40);
	     mpu_set_dmp_state(1);


	     // Wait for calibration to complete
		 for(;;) {
			 if( processData() )
				 if( getTravelTime() > 100 )
					 if( abs(_lastGyro[0] < _zeroMotion) )
						 break;
		 }

//	     //TODO: Debug
//	     {
//	    	 float angles[3];
//		     getQuaternion();
//		     getEuler(angles);
//		     trace_puts("Done with init of MPU-6050");
//	     }

//	     servo.setPulseWidth(0, 1.035e-3);
//	     {
//	            short gyro[3], accel[3], sensors;
//	            unsigned char more;
//	            long quat[4];
//	            unsigned long sensor_timestamp;
//	            static long values[100];
//	            static short g[100];
//
//	            long temp;
//	            int status;
//	            memset(values, 0, sizeof(values));
//	            for(int i= 0; i < 100; i++) {
//					do {
//			            memset(gyro, 0, sizeof(gyro));
//			            memset(quat, 0, sizeof(quat));
//						status= dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,
//								&more);
//					} while(status);
//					values[i]= quat[0];
//					g[i]= gyro[2];
//	            }
//	            {
//	            	unsigned short fsr;
//	            	float sens;
//	            	float angle= 0.0f;
//	            	mpu_get_gyro_fsr(&fsr);
//	            	mpu_get_gyro_sens(&sens);
//	            	trace_printf("FSR=%d\n", fsr);
//	            	for(int i= 0; i < 100; i++) {
//	            		angle+= ((float)(g[i]) / sens) / 100.0f;
//	            		trace_printf("Angle[%d]= %d\n", i, (int)angle);
//	            	}
//	            }
//	            trace_printf("dmp_read_status=%d\n", status);
//	            status= mpu_get_gyro_reg(gyro, NULL);
//	            trace_printf("reg status=%f\n", status);
//	            mpu_get_temperature(&temp, NULL);
//	            trace_printf("Temp: %ld\n", temp);
//	            trace_printf("Temp: %f\n", temp / 65536.0f);
//	     }

	     return true;
}

bool GyroMPU6500::getDataReady(void) {
    short s;
  	 mpu_get_int_status(&s);

  	 // Check for overflow
  	 if( s & 0x10 )
  		 trace_puts("FIFO Overflow");

  	 // Check for motion detect
  	 if( s & 0x40 )
  		 trace_puts("Motion Detected");

  	 return s & 0x02;
}

bool GyroMPU6500::processData(void) {
	 short sensors;
	 unsigned long sensor_timestamp;
	 unsigned char more;
	 int status;

	 // See if we have data ready
	 if( !getDataReady() )
		 return false;			// Data is not ready

	 status= dmp_read_fifo(_lastGyro, _lastAccel, _lastQuat, &sensor_timestamp, &sensors, &more);
	 if( status )
		 return false;

	 // Compute the inMotion flag
//	 _inMotion= (abs(_lastGyro[2]) > _zeroMotion) ||
//			 	(abs(_lastGyro[1]) > _zeroMotion) ||
//			 	(abs(_lastGyro[2]) > _zeroMotion);

	 // If inMotion, then increment position vectors
	 _travelTime++;
	 for(int i= 0; i < 3; i++) {
		 _position[i]+= ((float)_lastGyro[i]) / _integralPeriod;
	 }
	 return true;
}

bool GyroMPU6500::getQuaternion(void) {
#define DIV  1073741824.0f
	_w=  (float)_lastQuat[0] / DIV;
	_x=  (float)_lastQuat[1] / DIV;
	_y=  (float)_lastQuat[2] / DIV;
	_z=  (float)_lastQuat[3] / DIV;
	return true;
}

bool GyroMPU6500::getEuler(float* data) {
	// PSI (alpha)= N an X  (rotation around z axis)
	// PHI = x and N        (rotation around Z axis)
	// Theta = z and Z      (rotation around N axis)
    data[0] = atan2(2* _x* _y - 2*_w*_z, 2*_w*_w + 2*_x*_x - 1);   // psi
    data[1] = -asin(2*_x*_z + 2*_w*_y);                              // theta
    data[2] = atan2(2*_y*_z - 2*_w*_x, 2*_w*_w + 2*_z*_z - 1);   // phi
    return true;
}

bool GyroMPU6500::getInMotion(void) {
	return _inMotion;
}

void GyroMPU6500::resetPosition(void) {
	memset(_position, 0, sizeof(_position));
	mpu_reset_fifo();
	_travelTime= 0;
}

void GyroMPU6500::getPositions(float* pPositions) {
	memcpy(pPositions, _position, sizeof(_position));
}

bool GyroMPU6500::calibrateServo(PWMServoDriver &servo) {
	float lastPos= 0.0f;
	// Position servo to zero position
	servo.setPulseWidth(0, 1e-3 + lastPos);
	Arduino::delay(1000);
	for (uint16_t i = 0; i < CAL_COUNT; i++) {
		// Position Servo
		resetPosition();
		servo.setPulseWidth(0, 1e-3 + calData[i]);

		// Measure Servo travel
		do {
			processData();
		} while( getTravelTime() < 100);

		// Save off the results
		calResult[i][0]= fabs(lastPos - calData[i]);
		calResult[i][1]= fabs(_position[2]);
		lastPos= calData[i];
	}
	return true;
}

uint8_t GyroMPU6500::i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len,
		uint8_t* pData) {
#if DEBUG_I2C
	trace_printf("I2C Read: %x:%x %d: ", slaveAddr, regAddr, len);
#endif
	if( !_pWire ) {
		_pWire= new Wire();
		_pWire->begin();
	}
	_pWire->beginTransmission(slaveAddr);
	_pWire->write(regAddr);
	if( _pWire->endTransmission() == 0)
		return 1;
	_pWire->requestFrom(slaveAddr, len);
	if( _pWire->available() == 0 )
		return 1;
	while(len--) {
		uint8_t d;
		d= _pWire->read();
#if DEBUG_I2C
		trace_printf("%02x ", d);
#endif
		*pData++= d;
	}
#if DEBUG_I2C
	trace_putchar('\n');
#endif
	return 0;
}

GyroMPU6500::~GyroMPU6500() {
	// TODO Auto-generated destructor stub
}



extern "C" uint8_t stm32f4_i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData) {
	return GyroMPU6500::i2c_write(slaveAddr, regAddr, len, pData);
}

extern "C" uint8_t stm32f4_i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData) {
	return GyroMPU6500::i2c_read(slaveAddr, regAddr, len, pData);
}


extern "C" int stm32f4_delay_ms(uint32_t ms) {
	Arduino::delay(ms);
	return 0;
}

extern "C" int stm32f4_get_clock_ms(uint32_t *pMS) {
	return 0;
}
