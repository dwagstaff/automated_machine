/*
 * Wire.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: davew
 */


//#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_gpio.h"
//#include "stm32f4xx_hal_i2c.h"
//#include "stm32f4xx_hal_rcc.h"
//#include "stm32f4xx_hal_cortex.h"
//#include "stm32f4xx_hal_def.h"

extern "C" {
#include "stm32f4_discovery.h"
#include "stm32f4xx_hal.h"
}
#include "Wire.h"



static I2C_HandleTypeDef    I2cHandle;


// Forward defs
static void I2Cx_MspInit(void);


/******************************* I2C Routines**********************************/
/**
  * @brief  Configures I2C interface.
  * @param  None
  * @retval None
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&I2cHandle) == HAL_I2C_STATE_RESET)
  {
    /* DISCOVERY_I2Cx peripheral configuration */
    I2cHandle.Init.ClockSpeed = BSP_I2C_SPEED;
    I2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
    I2cHandle.Init.OwnAddress1 = 0x33;
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Instance = DISCOVERY_I2Cx;

    /* Init the I2C */
    I2Cx_MspInit();
    HAL_I2C_Init(&I2cHandle);
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the I2C comunication bus */
  HAL_I2C_DeInit(&I2cHandle);

  /* Re-Initiaize the I2C comunication bus */
  I2Cx_Init();
}
#pragma GCC diagnostic pop

/**
  * @brief I2C MSP Initialization
  * @param None
  * @retval None
  */
static void I2Cx_MspInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Enable I2C GPIO clocks */
  DISCOVERY_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();

  /* DISCOVERY_I2Cx SCL and SDA pins configuration ---------------------------*/
  GPIO_InitStruct.Pin = DISCOVERY_I2Cx_SCL_PIN | DISCOVERY_I2Cx_SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Alternate  = DISCOVERY_I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT, &GPIO_InitStruct);

  /* Enable the DISCOVERY_I2Cx peripheral clock */
  DISCOVERY_I2Cx_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  DISCOVERY_I2Cx_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  DISCOVERY_I2Cx_RELEASE_RESET();

  /* Enable and set I2Cx Interrupt to the highest priority */
  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_EV_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_EV_IRQn);

  /* Enable and set I2Cx Interrupt to the highest priority */
  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_ER_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_ER_IRQn);
}


void Wire::begin(void) {
	  I2Cx_Init();
}

void Wire::beginTransmission(uint8_t addr) {
	size= cursor= 0;
	this->addr= addr;
}

uint8_t Wire::write(uint8_t data) {
	// Check for overflow
	if( cursor == sizeof(buffer) )
		return 0;
	else {
		buffer[cursor++]= data;
		return 1;
	}
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
uint8_t Wire::endTransmission(bool sendStop) {
//	bool status= twi_master_transfer( (addr << 1),
//								   buffer,
//								   cursor,
//								   sendStop ? TWI_ISSUE_STOP : TWI_DONT_ISSUE_STOP
//			                      );
//	return status ? err_Ok : err_Other;
	  HAL_StatusTypeDef status = HAL_OK;

	  status= HAL_I2C_Master_Transmit(&I2cHandle, addr << 1, buffer, cursor, 0x1000);
//	  status = HAL_I2C_Mem_Write(&I2cHandle, addr << 1, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout);

	  /* Check the communication status */
	  if(status != HAL_OK)
	  {
	    /* Execute user timeout callback */
	    I2Cx_Error(addr);
	    return 0;
	  }
	  return cursor;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
uint8_t Wire::requestFrom(uint8_t addr, uint8_t len, bool sendStop) {
	  HAL_StatusTypeDef status = HAL_OK;
	// Insure data is not too large
	if( len > sizeof(buffer) )
		return 0;

	// Issue the request
	size= len;
	cursor= 0;
	status= HAL_I2C_Master_Receive(&I2cHandle, (addr << 1 ), buffer, len, 0x100);
	  /* Check the communication status */
	  if(status != HAL_OK)
	  {
	    /* Execute user timeout callback */
	    I2Cx_Error(addr);
	    return 0;
	  }
	  return len;

//	bool status= twi_master_transfer( (addr << 1) | 1,
//									  buffer,
//									  len,
//									  sendStop ? TWI_ISSUE_STOP : TWI_DONT_ISSUE_STOP
//			                        );
	return len;
}
#pragma GCC diagnostic pop

uint8_t Wire::read(void) {
	if( cursor >= size )
		return 0;
	else
		return buffer[cursor++];
}

uint16_t Wire::available(void) {
	return size - cursor;
}
