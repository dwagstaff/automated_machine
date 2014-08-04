/*
 * AX12.c
 *
 *  Created on: Aug 3, 2014
 *      Author: dwagstaff
 */

#include "stm32f4_discovery.h"
#include "AX12.h"
#include <string.h>


// Structure for AX-12 usart
UART_HandleTypeDef ax12_uart;


static HAL_StatusTypeDef DoAX12Transacton(uint8_t id, uint8_t instruction, uint8_t *parms, uint8_t parmSize, uint8_t *recvData, uint8_t recvSize);



void AX12_init(void) {

	// We are using USART4 for the AX-12 servo(s)
	// Enable the clock for the USART module
	__UART4_CLK_ENABLE();

	// Enable the clock for the GPIO module (TX & RX= PA0, Half-Duplex)
	__GPIOA_CLK_ENABLE();

	// Setup the GPIO Pin for the USART
	{
		GPIO_InitTypeDef txPin;
		txPin.Pin= GPIO_PIN_0;
		txPin.Mode= GPIO_MODE_AF_PP;
		txPin.Pull= GPIO_NOPULL;
		txPin.Speed= GPIO_SPEED_FAST;
		txPin.Alternate= GPIO_AF8_UART4;
		// This is both for the TX and RX
		HAL_GPIO_Init(GPIOA, &txPin);
	}


	// Configure the Usart init structure
	ax12_uart.Init.BaudRate= 1e6;
	ax12_uart.Init.WordLength= UART_WORDLENGTH_8B;
	ax12_uart.Init.StopBits= USART_STOPBITS_1;
	ax12_uart.Init.Parity= UART_PARITY_NONE;
	ax12_uart.Init.Mode= UART_MODE_TX_RX;
	ax12_uart.Init.HwFlowCtl= UART_HWCONTROL_NONE;
	ax12_uart.Init.OverSampling= UART_OVERSAMPLING_8;
	ax12_uart.Instance= UART4;

	if( HAL_HalfDuplex_Init(&ax12_uart) != HAL_OK)
		printf("Got a problem"); //TODO: Need to correct this

	// Turn off torque
//	AX12Write8Register(1, 0x3, 2);
	{
		uint16_t pos= 1802;
		HAL_StatusTypeDef result= AX12Read16Register(2,0x24,&pos);
		printf("Status and pos %d, %d", result, pos);
	}
	AX12Write8Register(1, 0x18, 1);
#define MINPOS 167
#define MAXPOS 860
	while(1) {
		for(uint8_t j= 1; j < 3; j++) {
			for(uint16_t i= MINPOS; i < MAXPOS; i+=10) {
				AX12SetPosition(j, i);
				HAL_Delay(10);
			}
			for(uint16_t i= MAXPOS; i > MINPOS; i-=10) {
				AX12SetPosition(j, i);
				HAL_Delay(10);
			}
		}
	}
}

/***
 * Do a transaction with the AX-12
 * @param id - ID of AX-12 to send transaction to
 * #param instruction - Instruction to send
 * @param parmData - Parameter data
 * @param parmSize - The size of the parameters
 * @param recvData - Point to buffer to receive data
 * @param recvSize - Number of characters expected
 * @return HAL_Status
 */
static HAL_StatusTypeDef DoAX12Transacton(uint8_t id, uint8_t instruction, uint8_t *parms, uint8_t parmSize, uint8_t *recvData, uint8_t recvSize) {
	uint8_t buffer[20];
	HAL_StatusTypeDef result;

	// First compute the checksum
	uint8_t checksum= id+(parmSize+2)+instruction;
	for(int i= 0; i < parmSize; i++)
		checksum+= parms[i];
	buffer[0]= buffer[1]= 0xff;
	buffer[2]= id;
	buffer[3]= parmSize+2;
	buffer[4]= instruction;
	for(int i=0; i < parmSize; i++)
		buffer[5+i]= parms[i];
	buffer[5+parmSize]= ~checksum;

	// Send the data off
	result= HAL_UART_Transmit(&ax12_uart, buffer, parmSize+6, 500);
	if( result != HAL_OK )
		return result;
	result= HAL_UART_Receive(&ax12_uart, recvData, recvSize, 500);
	return result;
}

HAL_StatusTypeDef doWrite(uint8_t id, uint8_t reg, uint8_t *data, uint8_t size) {
	HAL_StatusTypeDef result;
	uint8_t buffer[7];
	buffer[0]= reg;
	memcpy(buffer+1, data, size);
	result= DoAX12Transacton(id, 0x03, buffer, size+1, buffer, sizeof(buffer));
	if( result != HAL_OK )
		return result;
	return HAL_OK;
}

HAL_StatusTypeDef AX12Write16Register(uint8_t id, uint8_t reg, uint16_t value) {
	uint8_t buffer[2];
	buffer[0]= value & 0xff;
	buffer[1]= value >> 8;
	return doWrite(id, reg, buffer, sizeof(buffer));
}

HAL_StatusTypeDef AX12Write8Register(uint8_t id, uint8_t reg, uint8_t value) {
	return doWrite(id, reg, &value, sizeof(value));
}

HAL_StatusTypeDef AX12SetPosition(uint8_t id, uint16_t pos) {
	return AX12Write16Register(id, 0x1e, pos);
}

static HAL_StatusTypeDef doRead(uint8_t id, uint8_t reg, uint8_t *value, uint8_t size) {
	uint8_t buffer[7+2];
	HAL_StatusTypeDef result;

	// Form the parameters
	buffer[0]= reg;
	buffer[1]= size;

	// Issue the read request and get the data
	result= DoAX12Transacton(id, 0x02, buffer, 2, buffer, 7+size);
	if( result != HAL_OK )
		return result;
	memcpy(value, buffer+6, size);
	return HAL_OK;
}

HAL_StatusTypeDef AX12Read8Register(uint8_t id, uint8_t reg, uint8_t *value) {
	return doRead(id, reg, value, sizeof(uint8_t));
}

HAL_StatusTypeDef AX12Read16Register(uint8_t id, uint8_t reg, uint16_t *value) {
	uint8_t buffer[2];
	HAL_StatusTypeDef result= doRead(id, reg, buffer, 2);
	if( result != HAL_OK )
		return result;
	*value= (buffer[1] << 8) + buffer[0];
	return HAL_OK;
}

