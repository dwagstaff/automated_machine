/*
 * srv_DeviceInfo.c
 *
 *  Created on: Jan 25, 2015
 *      Author: dwagstaff
 */

#include <string.h>
#include "srv_DeviceInfo.h"
#include "ble_dis.h"


/**@brief Function for initializing Device Information Service.
 */
void dis_init(void)
{
    uint32_t         err_code;
    ble_dis_init_t   dis_init_obj;
    ble_dis_pnp_id_t pnp_id;

    pnp_id.vendor_id_source = PNP_ID_VENDOR_ID_SOURCE;
    pnp_id.vendor_id        = PNP_ID_VENDOR_ID;
    pnp_id.product_id       = PNP_ID_PRODUCT_ID;
    pnp_id.product_version  = PNP_ID_PRODUCT_VERSION;

    memset(&dis_init_obj, 0, sizeof(dis_init_obj));

    ble_srv_ascii_to_utf8(&dis_init_obj.manufact_name_str, MANUFACTURER_NAME);
    ble_srv_ascii_to_utf8(&dis_init_obj.model_num_str,     MODEL_NUM);
    ble_srv_ascii_to_utf8(&dis_init_obj.fw_rev_str,    FIRMWARE_REVISION);
    ble_srv_ascii_to_utf8(&dis_init_obj.sw_rev_str,    SOFTWARE_REVISION);
    ble_srv_ascii_to_utf8(&dis_init_obj.hw_rev_str,    HARDWARE_REVISION);


    dis_init_obj.p_pnp_id = &pnp_id;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&dis_init_obj.dis_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&dis_init_obj.dis_attr_md.write_perm);

    err_code = ble_dis_init(&dis_init_obj);
    APP_ERROR_CHECK(err_code);
}


