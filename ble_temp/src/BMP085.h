/* BMP085 Extended Example Code
 by: Jim Lindblom
 SparkFun Electronics
 date: 1/18/11
 license: CC BY-SA v3.0 - http://creativecommons.org/licenses/by-sa/3.0/

 Get pressure and temperature from the BMP085 and calculate altitude.
 Serial.print it out at 9600 baud to serial monitor.

 Update (7/19/11): I've heard folks may be encountering issues
 with this code, who're running an Arduino at 8MHz. If you're
 using an Arduino Pro 3.3V/8MHz, or the like, you may need to
 increase some of the delays in the bmp085ReadUP and
 bmp085ReadUT functions.
 */

#include <stdint.h>
#include "Arduino.h"
#include "Wire.h"

#define BMP085_ADDRESS 0x77  // I2C address of BMP085

class BMP085: public Arduino {
private:
	const uint8_t OSS = 0;  // Oversampling Setting
	class Wire Wire;


// Calibration values
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
	int32_t b5;

	int16_t temperature;
	int32_t pressure;

public:
	void setup(void);

	void loop(void);

// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
	void bmp085Calibration(void);

// Calculate temperature given ut.
// Value returned will be in units of 0.1 deg C
	int16_t bmp085GetTemperature(uint16_t ut);

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
	int32_t bmp085GetPressure(uint32_t up);

// Read 1 byte from the BMP085 at 'address'
	int8_t bmp085Read(uint8_t address);

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
	int16_t bmp085ReadInt(uint8_t address);

// Read the uncompensated temperature value
	uint16_t bmp085ReadUT();

// Read the uncompensated pressure value
	uint32_t bmp085ReadUP();
};

