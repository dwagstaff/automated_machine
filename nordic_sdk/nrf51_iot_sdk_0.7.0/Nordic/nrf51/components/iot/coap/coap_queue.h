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

/** @file coap_queue.h
 *
 * @defgroup iot_sdk_coap_queue CoAP Message Queue
 * @ingroup iot_sdk_coap
 * @{
 * @brief TODO.
 */

#ifndef COAP_QUEUE_H__
#define COAP_QUEUE_H__

#include <stdint.h>

#include "coap_transport.h"
#include "coap_message.h"

typedef struct 
{
    uint16_t      mid;
    uint8_t       token[8];
    uint16_t      token_len;
    uint8_t *     p_buffer;
    coap_remote_t remote;
    uint16_t      age;
    coap_response_callback_t callback;
} coap_queue_item_t;

uint32_t coap_queue_init(void);

uint32_t coap_queue_add(coap_queue_item_t * item);

uint32_t coap_queue_remove(coap_queue_item_t * item);

uint32_t coap_queue_item_by_token_get(uint8_t * token, coap_queue_item_t ** pp_item);


/*
uint32_t coap_queue_index_by_token(uint8_t * token, uint8_t * index);

uint32_t coap_queue_index_by_mid(uint16_t message_id, uint8_t * index);

uint32_t coap_queue_callback_by_index(uint8_t index, coap_response_callback_t callback);
*/
#endif

/** @} */
