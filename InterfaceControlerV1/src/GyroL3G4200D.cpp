/*
 * GyroL3G4200D.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: davew
 */

#include "GyroL3G4200D.h"

GyroL3G4200D::GyroL3G4200D(Wire wire, uint8_t addr) {
	_wire= wire;
	_addr= addr;
}

GyroL3G4200D::~GyroL3G4200D() {
	// TODO Auto-generated destructor stub
}

bool GyroL3G4200D::init(bool xEnable, bool yEnable, bool zEnable) {
	// Compute the enable flag
	uint8_t ctrl_reg1= (zEnable ? 0x04 : 0 ) |
					   (yEnable ? 0x02 : 0 ) |
					   (xEnable ? 0x01 : 0 ) |
					   0x08;
	uint8_t ctrl_reg2= 0;
	uint8_t ctrl_reg3= 0;
	uint8_t ctrl_reg4= 0;
	uint8_t ctrl_reg5= 0;
	return true;
}
