//============================================================================
// Name        : main.cpp
// Author      : Dave Wagstaff
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++
//============================================================================

//#include <iostream>
//using namespace std;

//
// Print a greeting message on standard output and exit.
//
// On embedded platforms this might require semi-hosting or similar.
//
// For example, for toolchains derived from GNU Tools for Embedded,
// to enable semi-hosting, the following was added to the linker:
//
// --specs=rdimon.specs -Wl,--start-group -lgcc -lc -lc -lm -lrdimon -Wl,--end-group
//
// Adjust it for other toolchains.
//

#include "OneWire.h"

extern "C" {
#include "ble_support.h"
#include "nrf_delay.h"
#include "srv_Battery.h"
#include "srv_Therm.h"
}

OneWire *pow;
uint8_t addr[8];


void oneSecondEvent(void) {
	uint8_t data[9];
	// Read current temp
	pow->reset();
	pow->select(addr);
	pow->write(0xBE);
	pow->read_bytes(data, 9);
	pow->reset();
	pow->write(0xCC);
	pow->write(0x44);
	int16_t v= (data[1] << 8) | data[0];
	registerTemp(1, (v*100)/16);
	checkBatteryLevel();
	checkTemp();
}


int main()
{
	uint32_t err;
	OneWire ow(25);
	pow= &ow;
	uint8_t data[9];
	uint8_t t= ow.search(addr);

	// Start the application
	startApp();

	// Should never get here
	return 0;
}
