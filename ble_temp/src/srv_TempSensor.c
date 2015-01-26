
#include "srv_TempSensor.h"
#include <string.h>
#include "nordic_common.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "app_util.h"

#include "ble_hts.h"


#define INVALID_BATTERY_LEVEL  255
#define OPCODE_LENGTH  1                                                    /**< Length of opcode inside Health Thermometer Measurement packet. */
#define HANDLE_LENGTH  2                                                    /**< Length of handle inside Health Thermometer Measurement packet. */
#define MAX_HTM_LEN   (BLE_L2CAP_MTU_DEF - OPCODE_LENGTH - HANDLE_LENGTH)   /**< Maximum size of a transmitted Health Thermometer Measurement. */

// Health Thermometer Measurement flag bits
#define HTS_MEAS_FLAG_TEMP_UNITS_BIT                (0x01 << 0)             /**< Temperature Units flag. */
#define HTS_MEAS_FLAG_TIME_STAMP_BIT                (0x01 << 1)             /**< Time Stamp flag. */
#define HTS_MEAS_FLAG_TEMP_TYPE_BIT                 (0x01 << 2)             /**< Temperature Type flag. */



/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_bas       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(srv_TempSensor_t * p_bas, ble_evt_t * p_ble_evt)
{
    p_bas->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}


/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_bas       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(srv_TempSensor_t * p_bas, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_bas->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_bas       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(srv_TempSensor_t * p_bas, ble_evt_t * p_ble_evt)
{
    if (p_bas->is_notification_supported)
    {
        ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
        
        if (
            (p_evt_write->handle == p_bas->battery_level_handles.cccd_handle)
            &&
            (p_evt_write->len == 2)
        )
        {
            // CCCD written, call application event handler
            if (p_bas->evt_handler != NULL)
            {
                srv_TempSensor_evt_t evt;
                
                if (ble_srv_is_notification_enabled(p_evt_write->data))
                {
                    evt.evt_type = srv_TempSensor_EVT_NOTIFICATION_ENABLED;
                }
                else
                {
                    evt.evt_type = srv_TempSensor_EVT_NOTIFICATION_DISABLED;
                }

                p_bas->evt_handler(p_bas, &evt);
            }
        }
    }
}


void srv_TempSensor_on_ble_evt(srv_TempSensor_t * p_bas, ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_bas, p_ble_evt);
            break;
            
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_bas, p_ble_evt);
            break;
            
        case BLE_GATTS_EVT_WRITE:
            on_write(p_bas, p_ble_evt);
            break;
            
        default:
            break;
    }
}


/**@brief Function for encoding a Health Thermometer Measurement.
 *
 * @param[in]   p_hts              Health Thermometer Service structure.
 * @param[in]   p_hts_meas         Measurement to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t hts_measurement_encode(srv_TempSensor_t *      p_hts,
                                      ble_hts_meas_t * p_hts_meas,
                                      uint8_t *        p_encoded_buffer)
{
    uint8_t flags = 0;
    uint8_t len   = 1;
    uint32_t encoded_temp;

    // Flags field
    if (p_hts_meas->temp_in_fahr_units)
    {
        flags |= HTS_MEAS_FLAG_TEMP_UNITS_BIT;
    }
    if (p_hts_meas->time_stamp_present)
    {
        flags |= HTS_MEAS_FLAG_TIME_STAMP_BIT;
    }

    // Temperature Measurement Value field
    if (p_hts_meas->temp_in_fahr_units)
    {
        flags |= HTS_MEAS_FLAG_TEMP_UNITS_BIT;

        encoded_temp = ((p_hts_meas->temp_in_fahr.exponent << 24) & 0xFF000000) |
                       ((p_hts_meas->temp_in_fahr.mantissa <<  0) & 0x00FFFFFF);
    }
    else
    {
        encoded_temp = ((p_hts_meas->temp_in_celcius.exponent << 24) & 0xFF000000) |
                       ((p_hts_meas->temp_in_celcius.mantissa <<  0) & 0x00FFFFFF);
    }
    len += uint32_encode(encoded_temp, &p_encoded_buffer[len]);

    // Time Stamp field
    if (p_hts_meas->time_stamp_present)
    {
        flags |= HTS_MEAS_FLAG_TIME_STAMP_BIT;
        len   += ble_date_time_encode(&p_hts_meas->time_stamp, &p_encoded_buffer[len]);
    }

    // Temperature Type field
    if (p_hts_meas->temp_type_present)
    {
        flags                   |= HTS_MEAS_FLAG_TEMP_TYPE_BIT;
        p_encoded_buffer[len++]  = p_hts_meas->temp_type;
    }

    // Flags field
    p_encoded_buffer[0] = flags;

    return len;
}



/**@brief Function for adding the Battery Level characteristic.
 *
 * @param[in]   p_bas        Battery Service structure.
 * @param[in]   p_bas_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t battery_level_char_add(srv_TempSensor_t * p_tss, const srv_TempSensor_init_t * p_tss_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    ble_hts_meas_t      initial_htm;
    uint8_t             encoded_htm[MAX_HTM_LEN];
    
    // Add Battery Level characteristic
    if (p_tss->is_notification_supported)
    {
        memset(&cccd_md, 0, sizeof(cccd_md));
    
        // According to BAS_SPEC_V10, the read operation on cccd should be possible without
        // authentication.
        BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
        cccd_md.write_perm = p_tss_init->battery_level_char_attr_md.cccd_write_perm;
        cccd_md.vloc = BLE_GATTS_VLOC_STACK;
    }
    
    memset(&char_md, 0, sizeof(char_md));
    
    char_md.char_props.read   = 1;
    char_md.char_props.notify = (p_tss->is_notification_supported) ? 1 : 0;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = (p_tss->is_notification_supported) ? &cccd_md : NULL;
    char_md.p_sccd_md         = NULL;
    
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR);
    
    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_tss_init->battery_level_char_attr_md.read_perm;
    attr_md.write_perm = p_tss_init->battery_level_char_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    
    ieee_float32_t v;
    v.mantissa= 82;
    v.exponent= 0;
    initial_htm.temp_in_fahr= v;
    initial_htm.temp_in_fahr_units= true;
    initial_htm.temp_type_present= false;
    initial_htm.time_stamp_present= false;
    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = hts_measurement_encode(p_tss, &initial_htm, encoded_htm);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = MAX_HTM_LEN;
    attr_char_value.p_value      = encoded_htm;
    
    err_code = sd_ble_gatts_characteristic_add(p_tss->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_tss->battery_level_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    
    return NRF_SUCCESS;
}


uint32_t srv_TempSensor_init(srv_TempSensor_t * p_tss, const srv_TempSensor_init_t * p_tss_init)
{
    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_tss->evt_handler               = p_tss_init->evt_handler;
    p_tss->conn_handle               = BLE_CONN_HANDLE_INVALID;
    p_tss->is_notification_supported = p_tss_init->support_notification;
    
    // Add service
    ble_uuid128_t base_uuid = TSS_UUID_BASE;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_tss->uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    ble_uuid.type = p_tss->uuid_type;
    ble_uuid.uuid = TSS_UUID_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_tss->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    // Add battery level characteristic
    return battery_level_char_add(p_tss, p_tss_init);
}


/**
 * Update the current Temp Sensor Level
 * @param p_tss
 * @param battery_level
 * @return
 */
uint32_t srv_TempSensor_temp_level_update(srv_TempSensor_t * p_tss, int16_t temp)
{
    uint32_t err_code = NRF_SUCCESS;

//    if (battery_level != p_tss->battery_level_last)
    {
    	// Encode the temp
    	ieee_float32_t v;
    	v.exponent= -2;
    	v.mantissa= temp;
    	ble_hts_meas_t meas;
    	meas.temp_in_celcius= v;
    	meas.temp_in_fahr_units= false;
    	meas.temp_type_present= false;
    	meas.time_stamp_present= false;
        uint8_t             encoded_htm[MAX_HTM_LEN];

    	uint16_t len= hts_measurement_encode(p_tss, &meas, encoded_htm );
        
        // Save new battery value
//        p_tss->battery_level_last = battery_level;
        
        // Update database
        err_code = sd_ble_gatts_value_set(p_tss->battery_level_handles.value_handle,
                                          0,
                                          &len,
                                          encoded_htm);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        
        // Send value if connected and notifying
        if ((p_tss->conn_handle != BLE_CONN_HANDLE_INVALID) && p_tss->is_notification_supported)
        {
            ble_gatts_hvx_params_t hvx_params;
            
            memset(&hvx_params, 0, sizeof(hvx_params));
            len = sizeof(uint8_t);
            
            hvx_params.handle   = p_tss->battery_level_handles.value_handle;
            hvx_params.type     = BLE_GATT_HVX_NOTIFICATION;
            hvx_params.offset   = 0;
            hvx_params.p_len    = &len;
            hvx_params.p_data   = encoded_htm;
            
            err_code = sd_ble_gatts_hvx(p_tss->conn_handle, &hvx_params);
        }
        else
        {
            err_code = NRF_ERROR_INVALID_STATE;
        }
    }

    return err_code;
}
