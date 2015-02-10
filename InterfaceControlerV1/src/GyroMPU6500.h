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
	int16_t _lastGyro[3];		// Last read gyro values
	int16_t _lastAccel[3];		// Last Accelerometer values
	long _lastQuat[4];			// Last Quat


public:
	GyroMPU6500();
	virtual ~GyroMPU6500();
	bool init(void);
	/**
	 * Return Data Ready status
	 * @return true: Data is ready
	 *         false: Data is not ready
	 */
	bool getDataReady(void);

	/**
	 * Process data stream
	 * @return true: Data Processed
	 * 	       false: Error during processing (data not available?)
	 */
	bool processData(void);

	static uint8_t i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData);
	static uint8_t i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData);
};

#endif /* GYROMPU6500_H_ */
