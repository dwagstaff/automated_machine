/*
 * GyroMPU6500.h
 *
 *  Created on: Feb 6, 2015
 *      Author: dwagstaff
 */

#ifndef GYROMPU6500_H_
#define GYROMPU6500_H_

#include <stdint.h>
#include "Wire.h"

class GyroMPU6500 {
private:
	static Wire *_pWire;


public:
	GyroMPU6500();
	virtual ~GyroMPU6500();
	bool init(void);

	static uint8_t i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData);
	static uint8_t i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData);
};

#endif /* GYROMPU6500_H_ */
