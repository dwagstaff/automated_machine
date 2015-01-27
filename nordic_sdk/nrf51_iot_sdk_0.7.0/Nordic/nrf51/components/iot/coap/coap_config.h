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

/** @file coap_config.h
 *
 * @defgroup iot_sdk_coap_config CoAP Configuration variables
 * @ingroup iot_sdk_coap
 * @{
 * @brief TODO.
 */

#define COAP_VERSION                     1 

#define COAP_CONF_DEFAULT_PORT           5683



/*
#define COAP_CONF_ACK_TIMEOUT            2.0
#define COAP_CONF_ACK_RANDOM_FACTOR      1.5
#define COAP_CONF_MAX_RETRANSMIT         4
#define COAP_CONF_NSTART                 1
#define COAP_CONF_MAX_TRANSMIT_SPAN      COAP_CONF_ACK_TIMEOUT * \
                                         (2 ^ COAP_CONF_MAX_RETRANSMIT - 1) * \
                                         COAP_CONF_ACK_RANDOM_FACTOR
#define COAP_CONF_MAX_TRANSMIT_WAIT      COAP_CONF_ACK_TIMEOUT * 
                                         (2 ^ (COAP_CONF_MAX_RETRANSMIT + 1) - 1) * \
                                         COAP_CONF_ACK_RANDOM_FACTOR
#define COAP_CONF_MAX_LATENCY            100.0
#define COAP_CONF_PROCESSING_DELAY       COAP_CONF_ACK_TIMEOUT
#define COAP_CONF_MAX_RTT                2 * COAP_CONF_MAX_LATENCY + \
                                         COAP_CONF_PROCESSING_DELAY
#define COAP_CONF_EXCHANGE_LIFETIME      COAP_CONF_MAX_TRANSMIT_SPAN + \
                                         COAP_CONF_MAX_RTT
#define COAP_CONF_DEFAULT_BLOCK_SIZE_EXP 6
#define COAP_CONF_EMPTY_ACK_DELAY        0.1
#define COAP_CONF_REQUEST_TIMEOUT        COAP_CONF_MAX_TRANSMIT_WAIT
#define COAP_CONF_DEFAULT_LEISURE        5

*/

/** @} */
