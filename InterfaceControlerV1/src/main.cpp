//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
// By Dave Wagstaff
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "Led.h"

#include "PWMServoDriver.h"
#include "Wire.h"
#include <cstdlib>

#include "GyroMPU6500.h"



PWMServoDriver servo;
GyroMPU6500 gyro;

// Define the LEDs on the board for later use
Led orangeLED(Led::Ports::D, 13);
Led greenLED(Led::Ports::D, 12);
Led redLED(Led::Ports::D, 14);
Led blueLED(Led::Ports::D, 15);

// ----------------------------------------------------------------------------
//
// STM32F4 led blink sample (trace via STDOUT).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// To demonstrate POSIX retargetting, reroute the STDOUT and STDERR to the
// trace device and display messages on both of them.
//
// Then demonstrates how to blink a led with 1Hz, using a
// continuous loop and SysTick delays.
//
// On DEBUG, the uptime in seconds is also displayed on the trace device.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the STDOUT output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// Definitions visible only within this translation unit.
namespace
{
  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 2 / 3;
  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
      - BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	float a;
	float b;
	a= atof("323");
	b= atof("123");
	a= a+ b + atof("321");

	// Turn on the Orange LED to indicate in Init Mode
	orangeLED.turnOn();

  // By customising __initialize_args() it is possible to pass arguments,
  // for example when running tests with semihosting you can pass various
  // options to the test.
  // trace_dump_args(argc, argv);

  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  // Reset servo
  servo.begin();
  servo.setPWMFreq(60.0);
//  servo.setPWM(1, 0, 1);
//  servo.setPWM(1, 0, 2);
//  servo.setPWM(1, 0, 3);
//  servo.setPWM(1, 0, 4);

  servo.setPulseWidth(1, 1.0e-3);
  servo.setPulseWidth(1, 1.5e-3);
  servo.setPulseWidth(1, 2.0e-3);

  // Configure the Gyro
  if( !gyro.init() )
	  trace_puts("ERROR: Unable to init Gryo");

  // Indicate out of Init mode and running
  orangeLED.turnOff();
  greenLED.turnOn();

// gyro.resetPosition();
// servo.setPulseWidth(0, 1.318e-3);   // 27 degrees

 blueLED.turnOn();
 gyro.calibrateServo(servo);
 blueLED.turnOff();

  // Reset position and move servo
//  for(;;) {
//	  i= mpu_get_accel_reg(acce, NULL);
//	  trace_printf("Result=%d\n", i);
//	  trace_printf("Value=%d\n", acce[2]);
//	  i= mpu_get_gyro_reg(gryo, NULL);
//	  trace_printf("G=%d\n", gryo[0]);
//  }

//  // Test for Gyro
//  {
//	  static uint8_t data;
//	  Wire wire;
//	  wire.begin();
//	  wire.beginTransmission(0x68);
//	  wire.write(107);
//	  wire.endTransmission();
//	  wire.requestFrom(0x68, 1);
//	  data= wire.read();
//	  trace_printf("Value of whoami is %x\n", data);
//	  i= dmp_load_motion_driver_firmware();
//  }

  // Init the Servo Driver
#define PRESCALE_VALUE (25E6 / (4096 * 60.0)) -1
#define RESOLUTION_SERVO  (( 1.0 / 60.0 ) / 4096.0)
  	  for(;;) {
  		  Timer::sleep(1000/3);
//  		  servo.setPulseWidth(0, 0.5e-3);
  		  servo.setDegree(0, 0);
  		  servo.setDegree(1, 0);
  		  Timer::sleep(1000/3);
//  		  servo.setPulseWidth(0, 1.5e-3);
  		  servo.setDegree(0, 90);
  		  servo.setDegree(1, 90);
  		  Timer::sleep(1000/3);
//  		  servo.setPulseWidth(0, 2.5e-3);
  		  servo.setDegree(0, 180);
  		  servo.setDegree(1, 180);
  		  Timer::sleep(1000/3);
//  		  servo.setPulseWidth(0, 1.5e-3);
  		  servo.setDegree(0, 90);
  		  servo.setDegree(1, 90);
  	  }

//  servo.setPWM(0, 0, 0);
//  servo.setPWM(0, 0, 2048);
//  servo.setPWM(0, 0, 1.5E-3 / RESOLUTION_SERVO);


  // The standard output and the standard error should be forwarded to
  // the trace device. For this to work, a redirection in _write.c is
  // required.
  puts("Standard output message.");
  fprintf(stderr, "Standard error message.\n");

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %uHz\n", SystemCoreClock);
}



// ----------------------------------------------------------------------------
