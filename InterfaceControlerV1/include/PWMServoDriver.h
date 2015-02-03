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

#ifndef _PWMServoDriver_H
#define _PWMServoDriver_H
#include <stdint.h>
#include "Arduino.h"


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


class PWMServoDriver: public Arduino {
 public:
  PWMServoDriver(uint8_t addr = 0x40);
  void begin(void);
  void reset(void);
  void setPWMFreq(float freq);
  void setPWM(uint8_t num, uint16_t on, uint16_t off);
  void setPin(uint8_t num, uint16_t val, bool invert=false);

  /**
   * Set the pulse width for a servo
   * @param num - Servo number to position
   * @param pulseWidth - Pulse width
   */
  void setPulseWidth(uint8_t num, float pulseWidth);

  /**
   * Set servo to degree
   * @param num - Servo number to set
   * @param degree - 0 .. 180 (position in degrees)
   */
  void setDegree(uint8_t num, uint16_t degree);

 private:
  uint8_t _i2caddr;
  float _period;
  float _resolution;
  uint16_t _lowMark;		// Low Count
  uint16_t _hiMark;			// High Count
  uint16_t _range;			// Range

  uint8_t read8(uint8_t addr);
  void write8(uint8_t addr, uint8_t d);
};

#endif
