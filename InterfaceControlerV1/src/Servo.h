/*
 * Servo.h
 *
 *  Created on: Feb 11, 2015
 *      Author: dwagstaff
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "PWMServoDriver.h"

class Servo {
private:
	PWMServoDriver& _servoDriver;
	uint8_t _unit;
	float _lowLimit;
	float _hiLimit;
	float _pulseDegSlope;

public:
	Servo(PWMServoDriver& servoDriver, uint8_t unit) : _servoDriver(servoDriver), _unit(unit) {};
	virtual ~Servo();

	/**
	 * Set position of servo
	 * @param deg - degress to position to
	 * @return true - positioning started
	 *         false - unable to start positioning
	 */
	bool setPosition(float deg);

	/**
	 * Set pulse width for servo
	 * @param pulseWidth - pulse width in seconds
	 * @return true : successful
	 *         false: failure
	 */
	bool setPulseWidth(float pulseWidth);

	float getHiLimit() const {
		return _hiLimit;
	}

	void setHiLimit(float hiLimit) {
		_hiLimit = hiLimit;
	}

	float getLowLimit() const {
		return _lowLimit;
	}

	void setLowLimit(float lowLimit) {
		_lowLimit = lowLimit;
	}

	float getPulseDegSlope() const {
		return _pulseDegSlope;
	}

	void setPulseDegSlope(float pulseDegSlope) {
		_pulseDegSlope = pulseDegSlope;
	}
};

#endif /* SERVO_H_ */
