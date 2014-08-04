/*
 * Servo.h
 *
 *  Created on: Aug 2, 2014
 *      Author: dwagstaff
 */

#ifndef SERVO_H_
#define SERVO_H_


#define PRESCALE_VALUE (25E6 / (4096 * 60.0)) -1
#define RESOLUTION_SERVO  (( 1.0 / 60.0 ) / 4096.0)


// Shortcuts for sending and receving data
#define write8(reg,value) I2Cx_WriteData(0x40 << 1, reg, value)
#define read8(reg) I2Cx_ReadData(0x40 <<1, reg)


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

extern void Servo_init();
extern void Servo_Position(uint8_t servoNumber, float millisecond);



#endif /* SERVO_H_ */
