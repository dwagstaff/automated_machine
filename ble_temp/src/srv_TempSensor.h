/*
 * srv_TempSensor.h
 *
 *  Created on: Jan 25, 2015
 *      Author: dwagstaff
 */

#ifndef SRV_TEMPSENSOR_H_
#define SRV_TEMPSENSOR_H_


#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

#define TSS_UUID_BASE {0x23, 0xD1, 0xBC, 0xEA, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00}
#define TSS_UUID_SERVICE 0x1523
#define TSS_UUID_TEMP_CHAR 0x1525


/**@brief Battery Service event type. */
typedef enum
{
    srv_TempSensor_EVT_NOTIFICATION_ENABLED,                             /**< Temp Sensor value notification enabled event. */
    srv_TempSensor_EVT_NOTIFICATION_DISABLED                             /**< Temp Sensor value notification disabled event. */
} srv_TempSensor_evt_type_t;

/**@brief Temp Sensor Service event. */
typedef struct
{
    srv_TempSensor_evt_type_t evt_type;                                  /**< Type of event. */
} srv_TempSensor_evt_t;

// Forward declaration of the srv_TempSensor_t type.
typedef struct srv_TempSensor_s srv_TempSensor_t;

/**@brief Temp Sensor Service event handler type. */
typedef void (*srv_TempSensor_evt_handler_t) (srv_TempSensor_t * p_bas, srv_TempSensor_evt_t * p_evt);

/**@brief Temp Sensor Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    srv_TempSensor_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Battery Service. */
    bool                          support_notification;           /**< TRUE if notification of Temp Level measurement is supported. */
    ble_srv_cccd_security_mode_t  battery_level_char_attr_md;     /**< Initial security level for battery characteristics attribute */
} srv_TempSensor_init_t;

/**@brief Battery Service structure. This contains various status information for the service. */
typedef struct srv_TempSensor_s
{
    srv_TempSensor_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Battery Service. */
    uint16_t                      service_handle;                 /**< Handle of Battery Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t      battery_level_handles;          /**< Handles related to the Battery Level characteristic. */
    uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    bool                          is_notification_supported;      /**< TRUE if notification of Battery Level is supported. */
    uint8_t                     uuid_type;
} srv_TempSensor_t;

/**@brief Function for initializing the Battery Service.
 *
 * @param[out]  p_bas       Battery Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_bas_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t srv_TempSensor_init(srv_TempSensor_t * p_bas, const srv_TempSensor_init_t * p_bas_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note For the requirements in the BAS specification to be fulfilled,
 *       srv_TempSensor_battery_level_update() must be called upon reconnection if the
 *       battery level has changed while the service has been disconnected from a bonded
 *       client.
 *
 * @param[in]   p_bas      Battery Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void srv_TempSensor_on_ble_evt(srv_TempSensor_t * p_bas, ble_evt_t * p_ble_evt);



/**@brief Function for updating the battery level.
 *
 * @details The application calls this function after having performed a battery measurement. If
 *          notification has been enabled, the battery level characteristic is sent to the client.
 *
 * @note For the requirements in the BAS specification to be fulfilled,
 *       this function must be called upon reconnection if the battery level has changed
 *       while the service has been disconnected from a bonded client.
 *
 * @param[in]   p_bas          Battery Service structure.
 * @param[in]   battery_level  New battery measurement value (in percent of full capacity).
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t srv_TempSensor_temp_level_update(srv_TempSensor_t * p_bas, int16_t temp);



#endif /* SRV_TEMPSENSOR_H_ */
