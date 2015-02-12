/*
 * Servo.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: dwagstaff
 */

#include "Servo.h"


Servo::~Servo() {
	// TODO Auto-generated destructor stub
}

bool Servo::setPosition(float deg) {
	_servoDriver.setPulseWidth(_unit, _lowLimit + (deg * _pulseDegSlope));
	return true;
}

bool Servo::setPulseWidth(float pulseWidth) {
	_servoDriver.setPulseWidth(_unit, pulseWidth);
	return true;
}
