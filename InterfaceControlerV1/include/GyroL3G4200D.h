/*
 * GyroL3G4200D.h
 *
 *  Created on: Feb 3, 2015
 *      Author: davew
 */

#ifndef GYROL3G4200D_H_
#define GYROL3G4200D_H_

#include <stdint.h>
#include "Wire.h"

class GyroL3G4200D {
private:
	Wire _wire;
	uint8_t _addr;
public:
	/***
	 * Construct a new Gryo Instance
	 * @parm wire - I2C interface to use
	 * @return bool - status, true is ok
	 */
	GyroL3G4200D(Wire wire, uint8_t addr= 0x34);

	/**
	 * Configure the Gyro
	 * @param xEnable, yEnable, zEnable: defaults to on (true)
	 */
	bool init(bool xEnable=true, bool yEnable=true, bool zEnable=true);

	int16_t getTemp(void);
	bool dataReady(void);
	bool getData(int16_t &xDelta, int16_t &yDelta, int16_t &zDelta);

	virtual ~GyroL3G4200D();
};

#endif /* GYROL3G4200D_H_ */
