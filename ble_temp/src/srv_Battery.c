/*
 * srv_Battery.c
 *
 *  Created on: Jan 25, 2015
 *      Author: dwagstaff
 */


#include <string.h>
#include "srv_Battery.h"
#include "ble_bas.h"

static ble_bas_t                             m_bas;                                     /**< Structure used to identify the battery service. */


/**@brief Function for performing a battery measurement, and update the Battery Level characteristic in the Battery Service.
 */
void checkBatteryLevel(void)
{
    uint32_t err_code;
    static uint8_t  battery_level= 1;

    battery_level++;

    err_code = ble_bas_battery_level_update(&m_bas, battery_level);
    if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != BLE_ERROR_NO_TX_BUFFERS) &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
    )
    {
        APP_ERROR_HANDLER(err_code);
    }
}



/**
 * Handle BLE event for battery service
 * @param evt
 */
void handle_ble_bas_event(ble_evt_t *evt) {
	ble_bas_on_ble_evt(&m_bas, evt);
}




/**
 * Handle Init of Battery Service
 */
void bas_init(void)
{
    uint32_t       err_code;
    ble_bas_init_t bas_init;

    // Initialize Battery Service.
    memset(&bas_init, 0, sizeof(bas_init));

    // Here the sec level for the Battery Service can be changed/increased.
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init.battery_level_char_attr_md.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init.battery_level_char_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&bas_init.battery_level_char_attr_md.write_perm);

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init.battery_level_report_read_perm);

    bas_init.evt_handler          = NULL;
    bas_init.support_notification = true;
    bas_init.p_report_ref         = NULL;
    bas_init.initial_batt_level   = 100;

    err_code = ble_bas_init(&m_bas, &bas_init);
    APP_ERROR_CHECK(err_code);
}

