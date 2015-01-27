/*
 * Wire.h
 *
 *  Created on: Jan 26, 2015
 *      Author: dwagstaff
 */

#ifndef WIRE_H_
#define WIRE_H_
#include <stdint.h>



class Wire {
private:
	uint8_t addr;			// Address to send data to
	uint8_t buffer[16];		// Buffer for read/write options
	uint8_t size;			// Pending read/write size
	uint8_t cursor;			// Current position

public:
	enum eWireErrorCodes {
		err_Ok= 0,
		err_TooLarge= 1,
		err_NackTX= 2,
		err_NackRX= 3,
		err_Other=4,
		err_BusNotAvailable
	};

	void begin(void);
	void beginTransmission(uint8_t addr);
	uint8_t write(uint8_t data);
	uint8_t endTransmission(bool sendStop= true);
	uint8_t requestFrom(uint8_t addr, uint8_t len, bool sendStop= true);
	uint8_t read(void);
	uint16_t available(void);
};


#endif /* WIRE_H_ */
