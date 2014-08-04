/*
 * AX12.h
 *
 *  Created on: Aug 3, 2014
 *      Author: dwagstaff
 */

#ifndef AX12_H_
#define AX12_H_


void AX12_init(void);

HAL_StatusTypeDef AX12Write16Register(uint8_t id, uint8_t reg, uint16_t value);
HAL_StatusTypeDef AX12Write8Register(uint8_t id, uint8_t reg, uint8_t value);
HAL_StatusTypeDef AX12Read8Register(uint8_t id, uint8_t reg, uint8_t *value);
HAL_StatusTypeDef AX12Read16Register(uint8_t id, uint8_t reg, uint16_t *value);

HAL_StatusTypeDef AX12SetPosition(uint8_t id, uint16_t pos);



#endif /* AX12_H_ */
