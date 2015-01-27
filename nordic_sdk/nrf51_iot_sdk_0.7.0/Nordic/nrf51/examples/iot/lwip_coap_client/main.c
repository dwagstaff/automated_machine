/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
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

/** @file
 *
 * @defgroup ble_sdk_app_template_main main.c
 * @{
 * @ingroup ble_sdk_app_template
 * @brief Template project main file.
 */

#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "nordic_common.h"
#include "softdevice_handler.h"
#include "app_trace.h"
#include "app_timer.h"
#include "app_button.h"
#include "app_gpiote.h"
#include "ble_advdata.h"
#include "ble_ipsp.h"
#include "ble_6lowpan.h"
#include "mem_manager.h"
#include "app_trace.h"
#include "lwip/init.h"
#include "lwip/inet6.h"
#include "lwip/ip6.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"
#include "lwip/timers.h"
#include "nrf_platform_port.h"
#include "coap_api.h"
#include "coap_config.h"
#include "app_util_platform.h"

#define DEVICE_NAME                     "LwIPCOAPClient"                                      /**< Device name used in BLE undirected advertisement. */

/** Modify SERVER_IPV6_ADDRESS according to your setup.
 *  The address provided below is a place holder.  */
#define SERVER_IPV6_ADDRESS             0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
                                        0x02, 0xAA, 0xAA, 0xFF, 0xFE, 0xAA, 0xAA, 0xAA        /**< IPv6 address of the server node. */
// The CoAP default port number 5683 MUST be supported by a server. 
#define SERVER_PORT_NUM                 5683                                                  /**< CoAP default port number. */

#define COAP_MESSAGE_TYPE               COAP_TYPE_NON                                         /**< Message type for all outgoing CoAP requests. */

#define LED_ONE                         BSP_LED_0_MASK
#define LED_TWO                         BSP_LED_1_MASK
#define LED_THREE                       BSP_LED_2_MASK
#define LED_FOUR                        BSP_LED_3_MASK

#define BUTTON_ONE                      BSP_BUTTON_0
#define BUTTON_TWO                      BSP_BUTTON_1

#define COMMAND_TOGGLE                  0x32

#define APP_ADV_INTERVAL                64                                                    /**< The advertising interval (in units of 0.625 ms. This value corresponds to 40 ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS      0                                                     /**< The advertising timeout (in units of seconds). */

#define APP_TIMER_PRESCALER             NRF51_DRIVER_TIMER_PRESCALER                          /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_MAX_TIMERS            3                                                     /**< Maximum number of simultaneously created timers. */
#define APP_TIMER_OP_QUEUE_SIZE         4                                                     /**< Size of timer operation queues. */

#define APP_GPIOTE_MAX_USERS            1                                                     /**< Maximum number of users of the GPIOTE handler. */

#define APP_ADV_TIMEOUT                 0                                                     /**< Time for which the device must be advertising in non-connectable mode (in seconds). 0 disables timeout. */
#define APP_ADV_ADV_INTERVAL            MSEC_TO_UNITS(333, UNIT_0_625_MS)                     /**< The advertising interval. This value can vary between 100ms to 10.24s). */
#define LWIP_SYS_TIMER_INTERVAL         APP_TIMER_TICKS(2000, APP_TIMER_PRESCALER)            /**< Interval for timer used as trigger to send. */
#define LED_BLINK_INTERVAL              APP_TIMER_TICKS(250, APP_TIMER_PRESCALER)             /**< LED blinking interval. */
#define BUTTON_DETECTION_DELAY          APP_TIMER_TICKS(50, APP_TIMER_PRESCALER)

#define APP_RTR_SOLICITATION_DELAY      500                                                   /**< Time before host sends an initial solicitation in ms. */

#define DEAD_BEEF                       0xDEADBEEF                                            /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */
#define MAX_LENGTH_FILENAME             128                                                   /**< Max length of filename to copy for the debug error handler. */

#define APP_DISABLE_LOGS                0                                                     /**< Disable debug trace in the application. */

#if (APP_DISABLE_LOGS == 0)

#define APPL_LOG  app_trace_log
#define APPL_DUMP app_trace_dump

#else // APP_DISABLE_LOGS

#define APPL_LOG(...)
#define APPL_DUMP(...)

#endif // APP_DISABLE_LOGS

#define APPL_ADDR(addr) APPL_LOG("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x\r\n", \
                                (addr).u8[0],(addr).u8[1],(addr).u8[2],(addr).u8[3],                            \
                                (addr).u8[4],(addr).u8[5],(addr).u8[6],(addr).u8[7],                            \
                                (addr).u8[8],(addr).u8[9],(addr).u8[10],(addr).u8[11],                          \
                                (addr).u8[12],(addr).u8[13],(addr).u8[14],(addr).u8[15])

typedef enum 
{
    LEDS_INACTIVE = 0,
    LEDS_BLE_ADVERTISING,
    LEDS_IPV6_IF_DOWN,
    LEDS_IPV6_IF_UP,
} display_state_t;

eui64_t                            eui64_local_iid;                                            /**< Local EUI64 value that is used as the IID for SLAAC. */
static ble_gap_addr_t              m_local_ble_addr;                                           /**< Local BLE address. */
static ble_gap_adv_params_t        m_adv_params;                                               /**< Parameters to be passed to the stack when starting advertising. */
static bool                        m_is_interface_up;
static app_timer_id_t              m_trigger_timer_id;                                         /**< Timer used to trigger data send events. */
static app_timer_id_t              m_led_blink_timer;                                          /**< Timer instance used for controlling board LEDs. */
static uint8_t                     well_known_core[100];
static display_state_t             m_display_state = LEDS_INACTIVE;                            /**< Board LED display state. */
static const char                  m_uri_part_lights[] = "lights";
static const char                  m_uri_part_led3[]   = "led3";
static const char                  m_uri_part_led4[]   = "led4";
static int                         m_temperature       = 21;


/**@brief Function for error handling, which is called when an error has occurred.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of error.
 *
 * @param[in] error_code  Error code supplied to the handler.
 * @param[in] line_num    Line number where the handler is called.
 * @param[in] p_file_name Pointer to the file name.
 */
void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    LEDS_ON((LED_ONE | LED_TWO | LED_THREE | LED_FOUR));
    APPL_LOG("[** ASSERT **]: Error 0x%08lX, Line %ld, File %s\r\n", error_code, line_num, p_file_name);

    // Variables used to retain function parameter values when debugging. 
    static volatile uint8_t  s_file_name[MAX_LENGTH_FILENAME];
    static volatile uint16_t s_line_num;
    static volatile uint32_t s_error_code;

    strncpy((char *)s_file_name, (const char *)p_file_name, MAX_LENGTH_FILENAME - 1);
    s_file_name[MAX_LENGTH_FILENAME - 1] = '\0';
    s_line_num                           = line_num;
    s_error_code                         = error_code;
    UNUSED_VARIABLE(s_file_name);
    UNUSED_VARIABLE(s_line_num);
    UNUSED_VARIABLE(s_error_code);

    // This call can be used for debug purposes during application development.
    // @note CAUTION: Activating this code will write the stack to flash on an error.
    //                This function should NOT be used in a final product.
    //                It is intended STRICTLY for development/debugging purposes.
    //                The flash write will happen EVEN if the radio is active, thus interrupting
    //                any communication.
    //                Use with care. Un-comment the line below to use.
    // ble_debug_assert_handler(error_code, line_num, p_file_name);

    // On assert, the system can only recover on reset.
    //NVIC_SystemReset();

    for(;;)
    {      
        // Infinite loop.
    }
}


/**@brief Callback function for asserts in the SoftDevice.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in]   line_num   Line number of the failing ASSERT call.
 * @param[in]   file_name  File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}


/**@brief Function for the LEDs initialization.
 *
 * @details Initializes all LEDs used by this application.
 */
static void leds_init(void)
{
    // Configure leds.
    LEDS_CONFIGURE((LED_ONE | LED_TWO | LED_THREE | LED_FOUR));
    
    // Turn leds off.
    LEDS_OFF((LED_ONE | LED_TWO | LED_THREE | LED_FOUR));
}


/**@brief Timer callback used for controlling board LEDs to represent application state.
 *
 * @param[in]   p_context   Pointer used for passing context. No context used in this application.
 */
static void blink_timeout_handler(void * p_context)
{
    uint32_t err_code;
    switch (m_display_state)
    {
        case LEDS_INACTIVE:
        {
            LEDS_OFF((LED_ONE | LED_TWO));
            LEDS_OFF((LED_THREE | LED_FOUR));
            break;
        }
        case LEDS_BLE_ADVERTISING:
        {
            LEDS_INVERT(LED_ONE);
            LEDS_OFF(LED_TWO);
            LEDS_OFF((LED_THREE | LED_FOUR));
            err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case LEDS_IPV6_IF_DOWN:
        {
            LEDS_ON(LED_ONE);
            LEDS_INVERT(LED_TWO);
            LEDS_OFF((LED_THREE | LED_FOUR));
            err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case LEDS_IPV6_IF_UP:
        {
            LEDS_OFF(LED_ONE);
            LEDS_ON(LED_TWO);
            LEDS_OFF((LED_THREE | LED_FOUR));
            break;
        }
        default:
        {
            break;
        }
    }
}


/**@brief Function for handling the timer used to trigger TCP actions.
 *
 * @details This function is used to trigger TCP connection request and to send data on the TCP port.
 *
 * @param[in]   p_context   Pointer used for passing context. No context used in this application.
 */
static void trigger_timer_callback(void * p_context)
{
    sys_check_timeouts();
}


/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
static void timers_init(void)
{
    uint32_t err_code;

    // Initialize timer module, making it use the scheduler
    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_MAX_TIMERS, APP_TIMER_OP_QUEUE_SIZE, false);

    // Create timer used to trigger data send events.
    err_code = app_timer_create(&m_trigger_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                trigger_timer_callback);
    APP_ERROR_CHECK(err_code);

    // Create timer used to control board LEDs.
    err_code = app_timer_create(&m_led_blink_timer, APP_TIMER_MODE_SINGLE_SHOT, \
                                blink_timeout_handler);
    APP_ERROR_CHECK(err_code);
}


static void coap_response_handler(coap_message_t * p_response)
{
    uint32_t err_code;

    APPL_LOG("[APPL]: Response Code : %d\r\n", p_response->header.code);
    if (p_response->header.code == COAP_CODE_204_CHANGED)
    {
        LEDS_ON(LED_THREE);
        err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
        APP_ERROR_CHECK(err_code);
    }
    else
    {
        LEDS_ON(LED_FOUR);
        err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
        APP_ERROR_CHECK(err_code);
    }
}


/**@brief Function for handling button events.
 *
 * @param[in]   pin_no         The pin number of the button pressed.
 * @param[in]   button_action  The action performed on button.
 */
static void button_event_handler(uint8_t pin_no, uint8_t button_action)
{
    if (m_is_interface_up == false)
    {
        return;
    }
    uint32_t err_code;
    if (button_action == APP_BUTTON_PUSH)
    {
        coap_message_t      * p_request;
        coap_message_conf_t   message_conf;
        coap_remote_t         remote_device;
        message_conf.type = COAP_MESSAGE_TYPE;
        message_conf.code = COAP_CODE_PUT;
        message_conf.id = 45;
        message_conf.token[0]  = 0x3;
        message_conf.token[1]  = 0x4;
        message_conf.token_len = 2;
        message_conf.response_callback = coap_response_handler;
        err_code = coap_request_create(&p_request, &message_conf);
        APP_ERROR_CHECK(err_code);
        memcpy(&remote_device.addr[0], (uint8_t []){SERVER_IPV6_ADDRESS}, IPV6_ADDR_SIZE);
        remote_device.port_number = SERVER_PORT_NUM;
        err_code = coap_message_remote_addr_set(p_request, &remote_device);
        APP_ERROR_CHECK(err_code);
        switch (pin_no)
        {
            case BUTTON_ONE:
            {
                APPL_LOG("[APPL]: Button One\r\n");

                memcpy(&p_request->remote.addr[0], (uint8_t []){SERVER_IPV6_ADDRESS}, IPV6_ADDR_SIZE);
                //coap_message_remote_addr_set
                p_request->remote.port_number = 5683;

                err_code = coap_message_opt_str_add(p_request, COAP_OPT_URI_PATH, (uint8_t *)m_uri_part_lights, strlen(m_uri_part_lights));
                APP_ERROR_CHECK(err_code);

                err_code = coap_message_opt_str_add(p_request, COAP_OPT_URI_PATH, (uint8_t *)m_uri_part_led3, strlen(m_uri_part_led3));
                APP_ERROR_CHECK(err_code);

                uint8_t payload[] = {COMMAND_TOGGLE};
                err_code = coap_message_payload_set(p_request, payload, sizeof(payload));
                APP_ERROR_CHECK(err_code);

                err_code = coap_request_send(p_request);
                if (err_code != NRF_SUCCESS)
                {
                    APPL_LOG("[APPL]: CoAP Message skipped, error code = 0x%08lX.\r\n", err_code);
                }
                err_code = coap_request_delete(p_request);
                APP_ERROR_CHECK(err_code);

                break;
            }
            case BUTTON_TWO:
            {
                APPL_LOG("[APPL]: Button Two\r\n");

                memcpy(&p_request->remote.addr[0], (uint8_t []){SERVER_IPV6_ADDRESS}, IPV6_ADDR_SIZE);
                p_request->remote.port_number = 5683;

                err_code = coap_message_opt_str_add(p_request, COAP_OPT_URI_PATH, (uint8_t *)"lights", 6);
                APP_ERROR_CHECK(err_code);

                err_code = coap_message_opt_str_add(p_request, COAP_OPT_URI_PATH, (uint8_t *)m_uri_part_led4, strlen(m_uri_part_led4));
                APP_ERROR_CHECK(err_code);

                uint8_t payload[] = {COMMAND_TOGGLE};
                err_code = coap_message_payload_set(p_request, payload, sizeof(payload));
                APP_ERROR_CHECK(err_code);

                err_code = coap_request_send(p_request);
                if (err_code != NRF_SUCCESS)
                {
                    APPL_LOG("[APPL]: CoAP Message skipped, error code = 0x%08lX.\r\n", err_code);
                }
                err_code = coap_request_delete(p_request);
                APP_ERROR_CHECK(err_code);

                break;
            }
            default:
                break;
        }
    }
}


/**@brief Function for the Button initialization.
 *
 * @details Initializes all Buttons used by this application.
 */
static void buttons_init(void)
{
    uint32_t err_code;

    static app_button_cfg_t buttons[] =
    {
        {BUTTON_ONE, false, BUTTON_PULL, button_event_handler},
        {BUTTON_TWO, false, BUTTON_PULL, button_event_handler}
    };

    APP_BUTTON_INIT(buttons, sizeof(buttons) / sizeof(buttons[0]), BUTTON_DETECTION_DELAY, false);

    err_code = app_button_enable();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing the Advertising functionality.
 *
 * @details Encodes the required advertising data and passes it to the stack.
 *          Also builds a structure to be passed to the stack when starting advertising.
 */
static void advertising_init(void)
{
    uint32_t                err_code;
    ble_advdata_t           advdata;
    uint8_t                 flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *)DEVICE_NAME,
                                          strlen(DEVICE_NAME));
    APP_ERROR_CHECK(err_code);

    err_code = sd_ble_gap_address_get(&m_local_ble_addr);
    APP_ERROR_CHECK(err_code);

    m_local_ble_addr.addr_type = BLE_GAP_ADDR_TYPE_PUBLIC;
    m_local_ble_addr.addr[5]   = 0x00;

    err_code = sd_ble_gap_address_set(&m_local_ble_addr);
    APP_ERROR_CHECK(err_code);

    IPV6_EUI64_CREATE_FROM_EUI48 (eui64_local_iid.identifier,
                                  m_local_ble_addr.addr,
                                  m_local_ble_addr.addr_type);
    ble_uuid_t adv_uuids[] =
    {
        {BLE_UUID_IPSP_SERVICE, BLE_UUID_TYPE_BLE}
    };

    //Build and set advertising data.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.flags.size              = sizeof(flags);
    advdata.flags.p_data            = &flags;
    advdata.uuids_complete.uuid_cnt = sizeof(adv_uuids) / sizeof(adv_uuids[0]);
    advdata.uuids_complete.p_uuids  = adv_uuids;

    err_code = ble_advdata_set(&advdata, NULL);
    APP_ERROR_CHECK(err_code);

    // Initialize advertising parameters (used when starting advertising).
    memset(&m_adv_params, 0, sizeof(m_adv_params));

    m_adv_params.type        = BLE_GAP_ADV_TYPE_ADV_IND;
    m_adv_params.p_peer_addr = NULL;                             // Undirected advertisement.
    m_adv_params.fp          = BLE_GAP_ADV_FP_ANY;
    m_adv_params.interval    = APP_ADV_ADV_INTERVAL;
    m_adv_params.timeout     = APP_ADV_TIMEOUT;
}


/**@brief Function for starting advertising.
 */
static void advertising_start(void)
{
    uint32_t err_code;

    err_code = sd_ble_gap_adv_start(&m_adv_params);
    APP_ERROR_CHECK(err_code);

    APPL_LOG("[APPL]: Advertising.\r\n");

    m_display_state = LEDS_BLE_ADVERTISING;
    err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 */
static void on_ble_evt(ble_evt_t * p_ble_evt)
{
    uint32_t err_code;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            APPL_LOG ("[APPL]: Connected.\r\n");
            m_display_state = LEDS_IPV6_IF_DOWN;
            err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
            APP_ERROR_CHECK(err_code);
            break;
        case BLE_GAP_EVT_DISCONNECTED:
            APPL_LOG ("[APPL]: Disconnected.\r\n");
            advertising_start();
            break;
        default:
            break;
    }
}


/**@brief Function for dispatching a BLE stack event to all modules with a BLE stack event handler.
 *
 * @details This function is called from the scheduler in the main loop after a BLE stack
 *          event has been received.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
    ble_ipsp_evt_handler(p_ble_evt);
    on_ble_evt(p_ble_evt);
}


/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
static void ble_stack_init(void)
{
    uint32_t err_code;

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, false);

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    APP_ERROR_CHECK(err_code);
}


void well_known_core_callback(coap_message_t * p_request, coap_message_t * p_response)
{
    uint32_t err_code;

    err_code = coap_message_opt_uint_add(p_response, COAP_OPT_CONTENT_FORMAT, COAP_CT_APP_LINK_FORMAT);
    APP_ERROR_CHECK(err_code);

    err_code = coap_message_payload_set(p_response, well_known_core, strlen((char *)well_known_core));
    APP_ERROR_CHECK(err_code);
}


static void sensors_callback(coap_message_t * p_request, coap_message_t * p_response)
{
    //
}


static void thermometer_callback(coap_message_t * p_request, coap_message_t * p_response)
{
    uint32_t err_code;

    switch (p_request->header.code)
    {
        case COAP_CODE_GET:
        {
            p_response->header.code = COAP_CODE_203_VALID;
            break;
        }
        case COAP_CODE_PUT:
        {
            // Input value cannot be more than 4 characters (1 sign + 3 digits).
            if ((p_request->payload_len == 0) || (p_request->payload_len > 4)) 
            {
                p_response->header.code = COAP_CODE_400_BAD_REQUEST;
                return;
            }
            uint8_t i;
            for (i=0;i<p_request->payload_len;++i)
            {
                if (i == 0)
                {
                    // The first digit of the input value must be the ASCII code of a decimal number or a minus sign or a plus sign.
                    if ((((p_request->p_payload[i] < 0x30) && (p_request->p_payload[i] != 0x2B)) && \
                        ((p_request->p_payload[i] < 0x30) && (p_request->p_payload[i] != 0x2D))) || \
                        (p_request->p_payload[i] > 0x39))
                    {
                        p_response->header.code = COAP_CODE_400_BAD_REQUEST;
                        return;
                    }
                }
                else
                {
                    // The remaining digits of the input value must be ASCII codes of decimal numbers.
                    if ((p_request->p_payload[i] < 0x30) || (p_request->p_payload[i] > 0x39))
                    {
                        p_response->header.code = COAP_CODE_400_BAD_REQUEST;
                        return;
                    }
                }
            }

            char input_str[5];
            memset(input_str, '\0', sizeof(input_str));
            memcpy(input_str, p_request->p_payload, p_request->payload_len);

            if ((atoi(input_str) < -100) || (atoi(input_str) > 100))    // Input value must be in valid range.
            {
                p_response->header.code = COAP_CODE_400_BAD_REQUEST;
                return;
            }
           
            m_temperature = atoi(input_str);
            
            p_response->header.code = COAP_CODE_204_CHANGED;
            break;
        }
        default:
        {
            p_response->header.code = COAP_CODE_405_METHOD_NOT_ALLOWED;
            return;
        }
    }
    // Set response payload to actual thermometer value.
    char response_str[5];
    memset(response_str, '\0', sizeof(response_str));
    sprintf(response_str, "%d", m_temperature);
    err_code = coap_message_payload_set(p_response, response_str, strlen(response_str));
    APP_ERROR_CHECK(err_code);
}


static void coap_endpoints_init(void)
{
    uint32_t err_code;

    static coap_resource_t root;
    err_code = coap_resource_create(&root, "/");
    APP_ERROR_CHECK(err_code);

    static coap_resource_t well_known;
    err_code = coap_resource_create(&well_known, ".well-known");
    APP_ERROR_CHECK(err_code);
    err_code = coap_resource_child_add(&root, &well_known);
    APP_ERROR_CHECK(err_code);

    static coap_resource_t core;
    err_code = coap_resource_create(&core, "core");
    APP_ERROR_CHECK(err_code);

    core.callback = well_known_core_callback;
    err_code = coap_resource_child_add(&well_known, &core);
    APP_ERROR_CHECK(err_code);

    static coap_resource_t sensors;
    err_code = coap_resource_create(&sensors, "sensors");
    APP_ERROR_CHECK(err_code);

    sensors.callback = sensors_callback;
    err_code = coap_resource_child_add(&root, &sensors);
    APP_ERROR_CHECK(err_code);

    static coap_resource_t thermometer;
    err_code = coap_resource_create(&thermometer, "thermometer");
    APP_ERROR_CHECK(err_code);

    thermometer.permission = (COAP_PERM_GET | COAP_PERM_PUT);
    thermometer.callback = thermometer_callback;
    err_code = coap_resource_child_add(&sensors, &thermometer);
    APP_ERROR_CHECK(err_code);

    uint16_t size = sizeof(well_known_core);
    err_code = coap_resource_well_known_generate(well_known_core, &size);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function to handle interface up event. */
void nrf51_driver_interface_up(void)
{
    uint32_t err_code;
    m_is_interface_up = true;
    
    APPL_LOG ("[APPL]: IPv6 interface up.\r\n");
            
    sys_check_timeouts();
    
    err_code = app_timer_start(m_trigger_timer_id, LWIP_SYS_TIMER_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
    
    m_display_state = LEDS_IPV6_IF_UP;
    err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function to handle interface down event. */
void nrf51_driver_interface_down(void)
{
    uint32_t err_code;
    m_is_interface_up = false;
    
    APPL_LOG ("[APPL]: IPv6 interface down.\r\n");
            
    err_code = app_timer_stop(m_trigger_timer_id);
    APP_ERROR_CHECK(err_code);
    
    m_display_state = LEDS_IPV6_IF_DOWN;
    err_code = app_timer_start(m_led_blink_timer, LED_BLINK_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing IP stack.
 *
 * @details Initialize the IP Stack and its driver.
 */
static void ip_stack_init(void)
{
    uint32_t err_code;

    //Initialize memory manager.
    err_code = nrf51_sdk_mem_init();
    APP_ERROR_CHECK(err_code);

    //Initialize lwip stack driver.
    err_code = nrf51_driver_init();
    APP_ERROR_CHECK(err_code);

    //Initialize lwip stack.
    lwip_init();  
}


/**@brief Function for initializing the transport of IPv6. */
static void ipv6_transport_init(void)
{
    ble_stack_init();
    advertising_init();
}


/**@brief Function for initializing the GPIOTE handler module.
 */
static void gpiote_init(void)
{
    APP_GPIOTE_INIT(APP_GPIOTE_MAX_USERS);
}


/**@brief Function for the Power manager.
 */
static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for application main entry.
 */
int main(void)
{
    // Initialize
    app_trace_init();
    leds_init();

    timers_init();
    gpiote_init();
    buttons_init();
    ipv6_transport_init();
    ip_stack_init();

    uint32_t err_code = coap_init(17);
    APP_ERROR_CHECK(err_code);

    coap_endpoints_init();

    APPL_LOG("\r\n");
    APPL_LOG("[APPL]: Init complete.\r\n");

    // Start execution
    advertising_start();

    // Enter main loop
    for (;;)
    {
        power_manage();
    }
}

/**
 * @}
 */
