/*
 * GyroMPU6500.h
 *
 *  Created on: Feb 6, 2015
 *      Author: dwagstaff
 */

#ifndef GYROMPU6500_H_
#define GYROMPU6500_H_

#include <stdint.h>
#include "Wire.h"

#include "Servo.h"

// Math used for Servo computations
// Pulse vs. Travel=   90 deg / 0.5 ms
// Speed= 60 deg / 0.14 s
// Top Speed= 428.571 deg/s
// Pulse/Degree= 5.6us / deg
// Pulse Width= deg * 5.6us
//

class GyroMPU6500 {
private:
	static Wire *_pWire;
	int16_t _lastGyro[3];		// Last read gyro values
	int16_t _lastAccel[3];		// Last Accelerometer values
	long _lastQuat[4];			// Last Quat
	float _w, _x, _y, _z;		// Quaternion
	bool _inMotion;				// True if inmotion
	float _position[3];		// Current position for all axis
	float _integralPeriod;		// Intergral period interval
	float _travelTime;		// Measure of travel time (in seconds)

	int16_t _zeroMotion;		// Zero motion threshold
	const float SampleRate= 100.0;	// Sample Rate (FIFO)

public:
	GyroMPU6500();
	virtual ~GyroMPU6500();
	bool init(void);
	/**
	 * Return Data Ready status
	 * @return true: Data is ready
	 *         false: Data is not ready
	 */
	bool getDataReady(void);

	/**
	 * Process data stream
	 * @return true: Data Processed
	 * 	       false: Error during processing (data not available?)
	 */
	bool processData(void);

	/**
	 * Compute the Quaternion from the last reading
	 * @return
	 */
	bool getQuaternion(void);

	/**
	 * Get Euler angle from last reading
	 * @param data
	 * @return
	 */
	bool getEuler(float *data);

	/**
	 * Determine if device is in motion
	 * @return true - Device/Servo is moving
	 *         false- Device/Servo is stopped
	 */
	bool getInMotion(void);

	/**
	 * Reset current position vectors
	 */
	void resetPosition(void);

	/**
	 * Return current positions
	 * @param pPositions - float, three values
	 */
	void getPositions(float *pPositions);

	/**
	 * Get current travel time
	 * @return
	 */
	float getTravelTime(void) { return _travelTime;}


	/**
	 * Calibrate the servo
	 * @return true: Calibration successful
	 *         false: Unable to calibrate
	 *
	 */
	bool calibrateServo(Servo &servo);

	float findLimit(Servo servo, float start, float delta);


	static uint8_t i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData);
	static uint8_t i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData);
};

#endif /* GYROMPU6500_H_ */
