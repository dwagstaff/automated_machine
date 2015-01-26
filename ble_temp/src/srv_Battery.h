/*
 * srv_Battery.h
 *
 *  Created on: Jan 25, 2015
 *      Author: dwagstaff
 */

#ifndef SRV_BATTERY_H_
#define SRV_BATTERY_H_


#define MIN_BATTERY_LEVEL                    81                                         /**< Minimum simulated battery level. */
#define MAX_BATTERY_LEVEL                    100                                        /**< Maximum simulated battery level. */
#define BATTERY_LEVEL_INCREMENT              1                                          /**< Increment between each simulated battery level measurement. */



extern void bas_init(void);

#ifndef __cplusplus
#include "ble_bas.h"
extern void handle_ble_bas_event(ble_evt_t *evt);
#endif

extern void checkBatteryLevel(void);


#endif /* SRV_BATTERY_H_ */
