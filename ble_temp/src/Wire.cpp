/*
 * Wire.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: davew
 */

#include "Wire.h"


extern "C" {
#include "twi_master.h"
#include "app_error.h"
}


void Wire::begin(void) {
	if(!twi_master_init())
		APP_ERROR_HANDLER(err_BusNotAvailable);
}

void Wire::beginTransmission(uint8_t addr) {
	size= cursor= 0;
	this->addr= addr;
}

uint8_t Wire::write(uint8_t data) {
	// Check for overflow
	if( cursor == sizeof(buffer) )
		return 0;
	else {
		buffer[cursor++]= data;
		return 1;
	}
}

uint8_t Wire::endTransmission(bool sendStop) {
	bool status= twi_master_transfer( (addr << 1),
								   buffer,
								   cursor,
								   sendStop ? TWI_ISSUE_STOP : TWI_DONT_ISSUE_STOP
			                      );
	return status ? err_Ok : err_Other;
}

uint8_t Wire::requestFrom(uint8_t addr, uint8_t len, bool sendStop) {
	// Insure data is not too large
	if( len > sizeof(buffer) )
		return 0;

	// Issue the request
	size= len;
	cursor= 0;
	bool status= twi_master_transfer( (addr << 1) | 1,
									  buffer,
									  len,
									  sendStop ? TWI_ISSUE_STOP : TWI_DONT_ISSUE_STOP
			                        );
	return len;
}

uint8_t Wire::read(void) {
	if( cursor >= size )
		return 0;
	else
		return buffer[cursor++];
}

uint16_t Wire::available(void) {
	return size - cursor;
}
