/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "PWMServoDriver.h"
#include "Wire.h"
#include <math.h>



Wire WIRE;

// Set to true to print some debug messages, or false to disable them.
#define ENABLE_DEBUG_OUTPUT false

PWMServoDriver::PWMServoDriver(uint8_t addr)
	: _period(0.0f), _resolution(0.0f), _lowMark(0), _hiMark(0),  _range(0)
	{
  _i2caddr = addr;
}

void PWMServoDriver::begin(void) {
 WIRE.begin();
 reset();
}


void PWMServoDriver::reset(void) {
 write8(PCA9685_MODE1, 0x0);
}

void PWMServoDriver::setPWMFreq(float freq) {
	_period= 1.0f / freq;
  // Compute the resolution and save it
//  _resolution= (1.0f / freq) / 4096.0f;
//	_resolution= 4.117e-3 / 1000.0;
	_period= 1.0f / 59.31f;
	_resolution= _period / 4096.0;

  //Serial.print("Attempting to set freq ");
  //Serial.println(freq);
//  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
//  float prescaleval = 25000000;
//  prescaleval /= 4096;
//  prescaleval /= freq;
//  prescaleval -= 1;
//  if (ENABLE_DEBUG_OUTPUT) {
//    Serial.print("Estimated pre-scale: "); Serial.println(prescaleval);
//  }
//  uint8_t prescale = floor(prescaleval + 0.5);
//  if (ENABLE_DEBUG_OUTPUT) {
//    Serial.print("Final pre-scale: "); Serial.println(prescale);
//  }
  float fPreScale= (25e6/(4096.0 * (freq * 0.90))) - 1.0;
  uint8_t prescale= floor(fPreScale + 0.5);
  
  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  delay(5);
  write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
                                          // This is why the beginTransmission below was not working.
  //  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);


  // Compute default low value to 0.5e-3
  _lowMark= uint16_t(0.5e-3 / _resolution);

  // Compute default hi value to 2.5e-3
  _hiMark= uint16_t(2.5e-3 / _resolution);

  // Compute the range
  _range= _hiMark - _lowMark;
}

void PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);

  WIRE.beginTransmission(_i2caddr);
  WIRE.write(LED0_ON_L+4*num);
  WIRE.write(on);
  WIRE.write(on>>8);
  WIRE.write(off);
  WIRE.write(off>>8);
  WIRE.endTransmission();
}

// Sets pin without having to deal with on/off tick placement and properly handles
// a zero value as completely off.  Optional invert parameter supports inverting
// the pulse for sinking to ground.  Val should be a value from 0 to 4095 inclusive.
void PWMServoDriver::setPin(uint8_t num, uint16_t val, bool invert)
{
  // Clamp value between 0 and 4095 inclusive.
#define min(a,b) (a<b? a : b)
  val = min(val, 4095);
  if (invert) {
    if (val == 0) {
      // Special value for signal fully on.
      setPWM(num, 4096, 0);
    }
    else if (val == 4095) {
      // Special value for signal fully off.
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, 4095-val);
    }
  }
  else {
    if (val == 4095) {
      // Special value for signal fully on.
      setPWM(num, 4096, 0);
    }
    else if (val == 0) {
      // Special value for signal fully off.
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, val);
    }
  }
}

uint8_t PWMServoDriver::read8(uint8_t addr) {
  WIRE.beginTransmission(_i2caddr);
  WIRE.write(addr);
  WIRE.endTransmission();

  WIRE.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return WIRE.read();
}

void PWMServoDriver::write8(uint8_t addr, uint8_t d) {
  WIRE.beginTransmission(_i2caddr);
  WIRE.write(addr);
  WIRE.write(d);
  WIRE.endTransmission();
}

void PWMServoDriver::setPulseWidth(uint8_t num, float pulseWidth) {
	setPWM(num, 0, uint16_t(pulseWidth / _resolution));
}

void PWMServoDriver::setDegree(uint8_t num, uint16_t degree) {
	uint16_t pos= ((degree * _range) / 180) + _lowMark;
	setPWM(num, 0, pos);
}
