/*
 * Arduino.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: davew
 */


#include "Arduino.h"

extern "C" {
#include "nrf_delay.h"
}


void Arduino::delay(uint16_t ms) {
	nrf_delay_ms(ms);
}



