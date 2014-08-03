/*
 * Servo.c
 *
 *  Created on: Aug 2, 2014
 *      Author: dwagstaff
 */

#include <stdio.h>
#include "diag/Trace.h"
#include "stm32f4_discovery.h"
#include "Servo.h"
#include "Timer.h"
#include <math.h>

/**
 * Init Servo system
 */
void Servo_init() {
	write8(PCA9685_MODE1, 0x0);

	// compute the prescale value
	uint8_t prescale = floor(PRESCALE_VALUE + 0.5);

	uint8_t oldmode = read8(PCA9685_MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep
	write8(PCA9685_MODE1, newmode); // go to sleep
	write8(PCA9685_PRESCALE, prescale); // set the prescaler
	write8(PCA9685_MODE1, oldmode);
	// Delay for 5 milliseconds
	timer_sleep(TIMER_FREQUENCY_HZ / 1000 * 5);
	//delay(5);
	write8(PCA9685_MODE1, oldmode | 0xa1);
	write8(ALLLED_ON_L, 0);
	write8(ALLLED_ON_H, 0);
}

/***
 * Set the positon of the servo in Milliseconds
 * @param servoNumber - Servo number to set
 * @param millisecond - Pulse width in milliseconds
 */
void Servo_Position(uint8_t servoNumber, float millisecond) {
	uint16_t pos = millisecond / RESOLUTION_SERVO;
	register uint8_t reg = LED0_ON_L + (4 * servoNumber);
	write8(reg + 2, pos & 0xff);
	write8(reg + 3, pos >> 8);
}

