/*
 * Arduino.h
 *
 *  Created on: Jan 26, 2015
 *      Author: davew
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_
#include <stdint.h>

class Arduino {
private:
public:
	/**
	 * Delay for xx milliseconds
	 * @param ms - Milliseconds to delay for
	 */
	static void delay(uint16_t ms);
};




#endif /* ARDUINO_H_ */
