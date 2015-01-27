/*
 * Wire.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: davew
 */

#include "Wire.h"

extern "C" {
#include "twi_master.h"
}

void Wire::begin(void) {
}

void Wire::beginTransmission(uint8_t addr) {
}

uint8_t Wire::write(uint8_t data) {
}

uint8_t Wire::endTransmission(void) {
}

uint8_t Wire::requestFrom(uint8_t addr, uint8_t len) {
}

uint8_t Wire::read(void) {
}

uint16_t Wire::available(void) {
}
