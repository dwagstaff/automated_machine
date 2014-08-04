/*
 * EasyVR.c
 *
 *  Created on: Aug 3, 2014
 *      Author: dwagstaff
 */


#include <stdio.h>
#include "diag/Trace.h"
#include "stm32f4_discovery.h"

#include "EasyVR.h"

UART_HandleTypeDef evr_uart;


static GPIO_InitTypeDef txPin;

/***
 * Init the Easy VR module
 */
void EasyVR_init(void) {

	// We are using USART3 for the EasyVR module
	// Enable the clock for the USART module
	__USART3_CLK_ENABLE();

	// Enable the clock for the GPIO module (TX= PD8, RX= PD9)
	__GPIOD_CLK_ENABLE();

	// Setup the GPIO Pins for the USART
	{
		txPin.Pin= GPIO_PIN_8;
		txPin.Mode= GPIO_MODE_AF_OD;
		txPin.Pull= GPIO_NOPULL;
		txPin.Speed= GPIO_SPEED_FAST;
		txPin.Alternate= GPIO_AF7_USART3;
		// TX
		HAL_GPIO_Init(GPIOD, &txPin);
		// RX
		txPin.Pin= GPIO_PIN_9;
		txPin.Mode= GPIO_MODE_INPUT;
		HAL_GPIO_Init(GPIOD, &txPin);
	}


	// Configure the Usart init structure
	evr_uart.Init.BaudRate= 9600;
	evr_uart.Init.WordLength= UART_WORDLENGTH_8B;
	evr_uart.Init.StopBits= UART_STOPBITS_1;
	evr_uart.Init.Parity= UART_PARITY_NONE;
	evr_uart.Init.Mode= UART_MODE_TX_RX;
	evr_uart.Init.HwFlowCtl= UART_HWCONTROL_NONE;
	evr_uart.Init.OverSampling= UART_OVERSAMPLING_16;
	evr_uart.Instance= USART3;

	if( HAL_UART_Init(&evr_uart) != HAL_OK)
		printf("Got a problem");

	HAL_UART_Transmit(&evr_uart,"b",3,1000);
	{
		uint8_t buffer[10];
		memset(buffer, 0, sizeof(buffer));
		HAL_StatusTypeDef result;
		result= HAL_UART_Receive(&evr_uart, buffer,1, 1000);
		printf("Got status of %d\n", result);
	}


}


//void HAL_UART_MspInit(UART_InitTypeDef *udef) {
//	// Enable the clock for the USART we are using
//	EASYVR_CLOCK_ENABLE;
//	EASYVR_GPIO_CLOCK_ENABLE;
//
//
//}
