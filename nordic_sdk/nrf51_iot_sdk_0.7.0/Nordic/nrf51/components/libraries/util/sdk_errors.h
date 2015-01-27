/* Copyright (c) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/**@file
 *
 * @defgroup sdk_error SDK error codes
 * @{
 * @ingroup app_common
 * @{
 * @brief Error codes for the nRF51 SDK.
 *
 * @details 
 * Error codes are 32-bit unsigned integers. The most significant 16 bits (MSB) are reserved for
 *          identifying the module where the error occurred. The least significant 16 bits (LSB)
 *          are used to provide the cause or nature of error. Each module is assigned a 16-bit
 *          unsigned integer, which it will use to identify all errors that occurred in the module.
 *          For example, if 0x8800 identifies a certain SDK module, all error codes from 
 *          0x88000000 to 0x8800FFFF are reserved for this module.
 *
 *          Note that common error reasons have been assigned values to make it 
 *          possible to decode error reasons easily. As an example, if a module is not initialized, 
 *          this error is assigned the error code 0x000A0. If an application encounters an error code
 *          0xZZZZ00A0, the application knows that it tried to access a certain module without 
 *          initializing it.
 *
 *          Each module can define error codes that are not covered by
 *          the common codes. These values must be defined in a range that does not conflict
 *          with the common error values. Such module-specific error values might be used by
 *          different modules to indicate errors of very different nature; so the same error code LSB 
 *          does not necessarily indicate the same error. If an error is already defined by the NRF 
 *          common error codes, however, these codes are reused.
 *
 *          A specific range is also reserved for the application. The application can use this range 
 *          to define application-specific errors.
 *
 *          The success code NRF_SUCCESS does not include a module identifier.          

 */

#ifndef SDK_ERRORS_H__
#define SDK_ERRORS_H__

#include "nrf_error.h"

/**
 * @defgroup sdk_err_base Base values defined for SDK modules
 * @{
 */
#define SDK_ERROR_BASE         (NRF_ERROR_BASE_NUM + 0x8000)   /**< Base value defined for SDK module identifiers. */
#define SDK_COMMON_ERROR_BASE  (NRF_ERROR_BASE_NUM + 0x0080)   /**< Base error value to be used for SDK error values. */
/* @} */

/**
 * @defgroup sdk_module_codes Module codes
 * @brief Codes reserved as identification for the module where the error occurred.
 * @{
 */
#define DEVICE_MANAGER_ERR_BASE           (0x8000)
#define MEMORY_MANAGER_ERR_BASE           (0x8100)
#define BLE_HPS_ERR_BASE                  (0x9000)
#define BLE_IPSP_ERR_BASE                 (0x9100)
#define BLE_6LOWPAN_ERR_BASE              (0x9200)

#define IOT_ERR_BASE                      (0xA000)
#define IOT_PBUFFER_ERR_BASE              (IOT_ERR_BASE+0x0100)
#define IOT_CONTEXT_MANAGER_ERR_BASE      (IOT_ERR_BASE+0x0200)
#define IOT_IPV6_ERR_BASE                 (IOT_ERR_BASE+0x1000)
#define IOT_ICMP6_ERR_BASE                (IOT_ERR_BASE+0x1100)
#define IOT_UDP6_ERR_BASE                 (IOT_ERR_BASE+0x1200)
#define IOT_COAP_ERR_BASE                 (IOT_ERR_BASE+0x1300)
/* @} */

/**
 * @defgroup sdk_common_errors Common error codes
 * @brief Codes reserved as identification for common errors.
 * @{
 */
#define SDK_ERR_MODULE_NOT_INITIALZED      (SDK_COMMON_ERROR_BASE+0x0000)
#define SDK_ERR_MUTEX_INIT_FAILED          (SDK_COMMON_ERROR_BASE+0x0001)
#define SDK_ERR_MUTEX_LOCK_FAILED          (SDK_COMMON_ERROR_BASE+0x0002)
#define SDK_ERR_MUTEX_UNLOCK_FAILED        (SDK_COMMON_ERROR_BASE+0x0003)
#define SDK_ERR_MUTEX_COND_INIT_FAILED     (SDK_COMMON_ERROR_BASE+0x0004)
#define SDK_ERR_MODULE_ALREADY_INITIALZED  (SDK_COMMON_ERROR_BASE+0x0005)
#define SDK_ERR_API_NOT_IMPLEMENTED        (SDK_COMMON_ERROR_BASE+0x0010)
#define SDK_ERR_FEATURE_NOT_ENABLED        (SDK_COMMON_ERROR_BASE+0x0011)
#define SDK_ERR_RX_PKT_TRUNCATED           (SDK_COMMON_ERROR_BASE+0x0012) 
/* @} */

/**
 * @defgroup dm_specific_errors Device Manager codes
 * @brief Error and status codes specific to the Device Manager.
 * @{
 */
#define DM_NO_APP_CONTEXT                (DEVICE_MANAGER_ERR_BASE+0x0040)
#define DM_SERVICE_CONTEXT_NOT_APPLIED   (DEVICE_MANAGER_ERR_BASE+0x0041)
#define DM_CONTEXT_INFO_LOST             (DEVICE_MANAGER_ERR_BASE+0x0042)
#define DM_DEVICE_CONTEXT_FULL           (DEVICE_MANAGER_ERR_BASE+0x0043)
/* @} */

/**
 * @defgroup ble_hps_specific_errors BLE HPS codes
 * @brief Error and status codes specific to BLE HPS.
 * @{
 */
#define BLE_HPS_CLIENT_INSTANCE_EXISTS    (BLE_HPS_ERR_BASE+0x0040)
#define BLE_HPS_CLIENT_NO_FREE_INSTANCE   (BLE_HPS_ERR_BASE+0x0041)
#define BLE_HPS_INVALID_CLIENT_HANDLE     (BLE_HPS_ERR_BASE+0x0042)
#define BLE_HPS_SERVER_INSTANCE_EXISTS    (BLE_HPS_ERR_BASE+0x0043)
#define BLE_HPS_SERVER_NO_FREE_INSTANCE   (BLE_HPS_ERR_BASE+0x0044)
#define BLE_HPS_INVALID_SERVER_HANDLE     (BLE_HPS_ERR_BASE+0x0045)
#define BLE_HPS_SERVICE_NOT_FOUND         (BLE_HPS_ERR_BASE+0x0046)
#define BLE_HPS_CHAR_NOT_FOUND            (BLE_HPS_ERR_BASE+0x0047)
#define BLE_HPS_DESC_NOT_FOUND            (BLE_HPS_ERR_BASE+0x0048)
#define BLE_HPS_GATT_PROCEDURE_ERROR      (BLE_HPS_ERR_BASE+0x0049)
/* @} */


/**
 * @defgroup ble_ipsp_errors IPSP codes
 * @brief Error and status codes specific to IPSP.
 * @{
 */
#define BLE_IPSP_RX_PKT_TRUNCATED         (BLE_IPSP_ERR_BASE+0x0040)
/* @} */


/**
 * @defgroup ble_6lowpan_errors 6LoWPAN codes
 * @brief Error and status codes specific to 6LoWPAN.
 * @{
 */
#define BLE_6LOWPAN_CID_NOT_FOUND         (BLE_6LOWPAN_ERR_BASE+0x0040)
#define BLE_6LOWPAN_TX_FIFO_FULL          (BLE_6LOWPAN_ERR_BASE+0x0041)
/* @} */

#define IOT_IPV6_ERR_ADDR_IF_MISMATCH      (IOT_IPV6_ERR_BASE+0x0040)

/**
 * @defgroup ble_sdk_udp_errors UDP codes
 * @brief Error and status codes specific to UDP.
 * @{
 */
#define UDP_PORT_IN_USE                   (IOT_UDP6_ERR_BASE+0x0040)
#define UDP_BAD_CHECKSUM                  (IOT_UDP6_ERR_BASE+0x0041)
#define UDP_TRUNCATED_PACKET              (IOT_UDP6_ERR_BASE+0x0042)
#define UDP_MALFORMED_PACKET              (IOT_UDP6_ERR_BASE+0x0043)
#define UDP_INTERFACE_NOT_READY           (IOT_UDP6_ERR_BASE+0x0044)
/* @} */


/**
 * @defgroup ble_sdk_icmp6_errors ICMP codes
 * @brief Error and status codes specific to ICMP.
 * @{
 */
#define ICMP6_UNHANDLED_PACKET_TYPE       (IOT_ICMP6_ERR_BASE+0x0040)
#define ICMP6_BAD_CHECKSUM                (IOT_ICMP6_ERR_BASE+0x0041)
#define ICMP6_MALFORMED_PACKET            (IOT_ICMP6_ERR_BASE+0x0042)
#define ICMP6_INVALID_PACKET_DATA         (IOT_ICMP6_ERR_BASE+0x0043)
/* @} */

/**
 * @defgroup ble_sdk_coap_errros CoAP codes
 * @brief Error and status codes specific to CoAP.
 * @{
 */
#define COAP_MESSAGE_ERROR_NULL           (IOT_COAP_ERR_BASE+0x0040)
#define COAP_MESSAGE_ERROR_INVALID_CONF   (IOT_COAP_ERR_BASE+0x0041)
#define COAP_MESSAGE_INVALID_CONTENT      (IOT_COAP_ERR_BASE+0x0042)
/* @} */

/**
 * @brief API Result.
 *
 * @details Indicates success or failure of an API procedure. In case of failure, a comprehensive
 *          error code indicating the cause or reason for the failure is provided.
 *
 *          Though called an API result, it could be used in asynchronous notifications callback along
 *          with asynchronous callback as event result. This mechanism is employed when an event
 *          marks the end of a procedure initiated using the API. API result, in this case, will only 
 *          indicate whether the procedure has been requested successfully.
 */
typedef uint32_t api_result_t;
/** @} */
/** @} */

#endif // SDK_ERRORS_H__
