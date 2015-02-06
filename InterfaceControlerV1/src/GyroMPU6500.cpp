/*
 * GyroMPU6500.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: dwagstaff
 */

#include "GyroMPU6500.h"
#include "Arduino.h"


 Wire *GyroMPU6500::_pWire= 0;


GyroMPU6500::GyroMPU6500() {
}

void GyroMPU6500::i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len,
		uint8_t* pData) {
	if( !_pWire ) {
		_pWire= new Wire();
		_pWire->begin();
	}
	_pWire->beginTransmission(slaveAddr);
	_pWire->write(regAddr);
	while(len--)
		_pWire->write(*pData++);
	_pWire->endTransmission();
}

void GyroMPU6500::i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len,
		uint8_t* pData) {
	if( !_pWire ) {
		_pWire= new Wire();
		_pWire->begin();
	}
	_pWire->beginTransmission(slaveAddr);
	_pWire->write(regAddr);
	_pWire->endTransmission();
	_pWire->requestFrom(slaveAddr, len);
	while(len--)
		*pData++= _pWire->read();
}

GyroMPU6500::~GyroMPU6500() {
	// TODO Auto-generated destructor stub
}



extern "C" void Sensors_I2C_WriteRegister(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData) {
	GyroMPU6500::i2c_write(slaveAddr, regAddr, len, pData);
}

extern "C" void Sensors_I2C_ReadRegister(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData) {
	GyroMPU6500::i2c_read(slaveAddr, regAddr, len, pData);
}


extern "C" void mdelay(uint32_t ms) {
	Arduino::delay(ms);
}
