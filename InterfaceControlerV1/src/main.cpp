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
using namespace std;

#include "GyroMPU6500.h"
#include "Servo.h"
#include "Stats.h"
#include "usart.h"
#include <string.h>
#include "stm32f4_discovery.h"


PWMServoDriver servoDriver;
Servo servo(servoDriver, 0);

GyroMPU6500 gyro;

// Define the LEDs on the board for later use
Led orangeLED(Led::Ports::D, 13);
Led greenLED(Led::Ports::D, 12);
Led redLED(Led::Ports::D, 14);
Led blueLED(Led::Ports::D, 15);

/* UART handler declaration */
UART_HandleTypeDef UartHandle;


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

static void processInput(uint8_t* buffer) {
//#define MSG "GOT: "
//	HAL_UART_Transmit(&UartHandle, (uint8_t *)MSG, strlen(MSG), 5000);
//	HAL_UART_Transmit(&UartHandle, buffer, strlen((const char *)buffer), 5000);
//	HAL_UART_Transmit(&UartHandle, (uint8_t *)"\n\r", 2, 5000);

	if( buffer[0] == 'l' ) {
		Led *pLed;
		if( buffer[1] == '1' )
			pLed= &orangeLED;
		else if( buffer[1] == '2' ) pLed= &blueLED;
		else if( buffer[1] == '3' ) pLed= &greenLED;
		else pLed= &redLED;
		if( buffer[2] == '1' )
			pLed->turnOn();
		else
			pLed->turnOff();
	}
}

int
main(int argc, char* argv[])
{
//	Arduino::delay(1000);

	// Init Serial Port
	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART1 configured as follow:
	      - Word Length = 8 Bits
	      - Stop Bit = One Stop bit
	      - Parity = None
	      - BaudRate = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance          = USARTx;

	  UartHandle.Init.BaudRate     = 9600;
	  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits     = UART_STOPBITS_1;
	  UartHandle.Init.Parity       = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode         = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  if(HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    //Error_Handler();
	  }

	  /* Configure KEY Button */
	  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

//	  HAL_UART_Transmit(&UartHandle, (uint8_t*)"123\n\r", 5, 5000);
	  {
		  static int inp= 0;
		  uint32_t lastPress= RESET;
		  for(;;) {
			  static uint8_t buffer[10];
			  uint8_t c;
			  // Handle switch
			  if( BSP_PB_GetState(BUTTON_KEY) != lastPress ) {
				  lastPress= BSP_PB_GetState(BUTTON_KEY);
				  if( BSP_PB_GetState(BUTTON_KEY) == RESET ) {
					  HAL_UART_Transmit(&UartHandle, (uint8_t*)"S0\r", 3, 5000);
					  redLED.turnOff();
				  } else {
					  HAL_UART_Transmit(&UartHandle, (uint8_t*)"S1\r", 3, 5000);
					  redLED.turnOn();
				  }
			  }
			  if( HAL_UART_Receive(&UartHandle, &c, 1, 0) == HAL_OK ) {
				  if( c == '\r' ) {
					  buffer[inp]= 0;
					  processInput(buffer);
					  inp= 0;
				  } else {
					  buffer[inp++]= c;
				  }
			  }
		  }
	  }

	// Turn on the Orange LED to indicate in Init Mode
	orangeLED.turnOn();

  // By customising __initialize_args() it is possible to pass arguments,
  // for example when running tests with semihosting you can pass various
  // options to the test.
  // trace_dump_args(argc, argv);

  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  // Configure Servo Driver
  servoDriver.begin();
  servoDriver.setPWMFreq(60.0);
  servo.setPulseWidth(1.5e-3);
  servo.setPulseWidth(1.3e-3);
  servo.setPulseWidth(1.7e-3);
  servo.setPulseWidth(1.0e-3);
  servo.setPulseWidth(2.0e-3);

  // Configure the Gyro
  if( !gyro.init() )
	  trace_puts("ERROR: Unable to init Gryo");

  // Indicate out of Init mode and running
  orangeLED.turnOff();
  greenLED.turnOn();


 blueLED.turnOn();
 gyro.calibrateServo(servo);
 blueLED.turnOff();

 servo.setPosition(0);
 servo.setPosition(135);
 blueLED.turnOff();



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
