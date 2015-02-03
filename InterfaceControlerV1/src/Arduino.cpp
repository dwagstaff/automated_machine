/*
 * Arduino.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: davew
 */


#include "Arduino.h"

#ifdef STM32F407xx
#include "Timer.h"
#endif



void Arduino::delay(uint16_t ms) {
#ifdef STM32F407xx
	Timer::sleep(ms);
#endif
}



