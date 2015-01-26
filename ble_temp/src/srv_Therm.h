/*
 * srv_Therm.h
 *
 *  Created on: Jan 25, 2015
 *      Author: dwagstaff
 */

#ifndef SRV_THERM_H_
#define SRV_THERM_H_


#define TEMP_TYPE_AS_CHARACTERISTIC          0                                          /**< Determines if temperature type is given as characteristic (1) or as a field of measurement (0). */




extern void therm_init(void);
extern void checkTemp(void);


#ifndef __cplusplus
#include "ble_hts.h"
extern void handle_ble_hts_event(ble_evt_t *evt);
#endif



#endif /* SRV_THERM_H_ */
