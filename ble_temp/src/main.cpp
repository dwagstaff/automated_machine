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


void oneSecondEvent(void) {
	pow->reset();
	checkBatteryLevel();
	checkTemp();
}


int main()
{
	uint32_t err;
	OneWire ow(25);
	pow= &ow;
	uint8_t addr[8];
	uint8_t data[9];
	uint8_t t= ow.search(addr);

	// Start the application
	startApp();

	// Should never get here
	return 0;
}
