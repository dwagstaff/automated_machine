/*
 * Wire.h
 *
 *  Created on: Jan 26, 2015
 *      Author: dwagstaff
 */

#ifndef WIRE_H_
#define WIRE_H_


class Wire {
private:
public:
	void begin(void);
	void beginTransmission(uint8_t addr);
	uint8_t write(uint8_t data);
	uint8_t endTransmission(void);
	uint8_t requestFrom(uint8_t addr, uint8_t len);
	uint8_t read(void);
	uint16_t available(void);
};


#endif /* WIRE_H_ */
