/*
 * ble_support.h
 *
 *  Created on: Jan 25, 2015
 *      Author: dwagstaff
 */

#ifndef BLE_SUPPORT_H_
#define BLE_SUPPORT_H_
#include <stdint.h>


/**
 * Start application (also starts the BLE stack)
 */
extern void startApp(void);

/**
 * Register new tempreture amount
 * @param sensorNumber - Temp Sensor reading was taken from
 * @param temp - Temp in x100 format
 */
extern void registerTemp(uint8_t sensorNumber, int16_t temp);



// Callbacks
void oneSecondEvent(void);



#endif /* BLE_SUPPORT_H_ */
