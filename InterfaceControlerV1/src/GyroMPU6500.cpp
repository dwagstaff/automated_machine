/*
 * GyroMPU6500.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: dwagstaff
 */

#include "GyroMPU6500.h"
#include "Arduino.h"

#include "diag/Trace.h"


 Wire *GyroMPU6500::_pWire= 0;


GyroMPU6500::GyroMPU6500() {
}

uint8_t GyroMPU6500::i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len,
		uint8_t* pData) {
	trace_printf("I2C Write: %x:%x %d: ", slaveAddr, regAddr, len);
	for(int i= 0; i < len; i++)
		trace_printf("%02x ", pData[i]);
	trace_putchar('\n');
	if( !_pWire ) {
		_pWire= new Wire();
		_pWire->begin();
	}
	_pWire->beginTransmission(slaveAddr);
	_pWire->write(regAddr);
	while(len--)
		_pWire->write(*pData++);
	return( _pWire->endTransmission() == 0);

}

uint8_t GyroMPU6500::i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len,
		uint8_t* pData) {
	trace_printf("I2C Read: %x:%x %d: ", slaveAddr, regAddr, len);
	if( !_pWire ) {
		_pWire= new Wire();
		_pWire->begin();
	}
	_pWire->beginTransmission(slaveAddr);
	_pWire->write(regAddr);
	if( _pWire->endTransmission() == 0)
		return 1;
	_pWire->requestFrom(slaveAddr, len);
	if( _pWire->available() == 0 )
		return 1;
	while(len--) {
		uint8_t d;
		d= _pWire->read();
		trace_printf("%02x ", d);
		*pData++= d;
	}
	trace_putchar('\n');
	return 0;
}

GyroMPU6500::~GyroMPU6500() {
	// TODO Auto-generated destructor stub
}



extern "C" uint8_t stm32f4_i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData) {
	return GyroMPU6500::i2c_write(slaveAddr, regAddr, len, pData);
}

extern "C" uint8_t stm32f4_i2c_read(uint8_t slaveAddr, uint8_t regAddr, uint8_t len, uint8_t *pData) {
	return GyroMPU6500::i2c_read(slaveAddr, regAddr, len, pData);
}


extern "C" void stm32f4_delay_ms(uint32_t ms) {
	Arduino::delay(ms);
}

extern "C" uint32_t stm32f4_get_clock_ms(void) {
	return 0;
}
