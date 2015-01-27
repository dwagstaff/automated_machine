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


#include <stdbool.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf51.h"
#include "coap_api.h"
#include "coap_queue.h"
#include "coap_transport.h"
#include "app_trace.h"
#include "sdk_common.h"
#include "ble_ipsp.h"
#include "mem_manager.h"
#include "iot_defines.h"
#include "coap_resource.h"

/**
 * @defgroup iot_coap_log Module's Log Macros
 * @details Macros used for creating module logs which can be useful in understanding handling
 *          of events or actions on API requests. These are intended for debugging purposes and
 *          can be disabled by defining the COAP_DISABLE_LOGS to 1.
 * @note That if ENABLE_DEBUG_LOG_SUPPORT is disabled, having COAP_DISABLE_LOGS has no effect.
 * @{
 */
#if (COAP_DISABLE_LOGS == 0)

#define COAP_TRC  app_trace_log                                                          /**< Used for getting trace of execution in the module. */
#define COAP_DUMP app_trace_dump                                                         /**< Used for dumping octet information to get details of bond information etc. */
#define COAP_ERR  app_trace_log                                                          /**< Used for logging errors in the module. */

#else // COAP_DISABLE_LOGS

#define COAP_TRC(...)                                                                    /**< Diasbles traces. */
#define COAP_DUMP(...)                                                                   /**< Diasbles dumping of octet streams. */
#define COAP_ERR(...)                                                                    /**< Diasbles error logs. */

#endif // COAP_DISABLE_LOGS

#define COAP_REQUEST_ENTITY_MAX_SIZE (BLE_IPSP_RX_BUFFER_SIZE - (IPV6_IP_HEADER_SIZE + \
                                                                 UDP_HEADER_SIZE))       /** Maximum request entity size. */

/**
 * @defgroup iot_coap_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case the need to use an alternative architecture arises.
 * @{
 */
#define COAP_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_coap_mutex)                                 /**< Lock module using mutex */
#define COAP_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_coap_mutex)                               /**< Unlock module using mutex */
/** @} */

SDK_MUTEX_DEFINE(m_coap_mutex)                                                           /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */

static uint32_t m_token_seed;                                                            /**< Token seed provided by application to be used for generating token numbers. */
static uint32_t m_message_id_counter;                                                    /**< Message ID counter, used to generate unique message IDs. */

/** Table of ports used for CoAP server and/or client endpoints. */
static const coap_port_t m_coap_port[COAP_PORT_COUNT] =
{
    {COAP_SERVER_PORT},
    {COAP_CLIENT_PORT}
};

static inline bool is_ping(coap_message_t * p_message)
{
    return (p_message->header.code == COAP_CODE_EMPTY_MESSAGE) &&
           (p_message->header.type == COAP_TYPE_CON);
    
}

static inline bool is_request(coap_message_t * p_message)
{
    return (p_message->header.code >= 1) && (p_message->header.code < 32);
}

static inline bool is_response(coap_message_t * p_message)
{
    return (p_message->header.code >= 64) && (p_message->header.code < 192);
}

uint32_t coap_init(uint32_t token_rand_seed)
{
    COAP_TRC("[COAP]: >> coap_init %lu.\r\n", token_rand_seed);

    uint32_t err_code;

    SDK_MUTEX_INIT(m_coap_mutex);

    COAP_MUTEX_LOCK();

    m_token_seed = token_rand_seed;
    (void)m_token_seed;
    
    m_message_id_counter = 1;
    
    const coap_transport_init_t transport_param =
    {
       COAP_PORT_COUNT,
       (coap_port_t *)m_coap_port
    };

    err_code = coap_transport_init(&transport_param);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = coap_queue_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = coap_resource_init();

    COAP_MUTEX_UNLOCK();

    COAP_TRC("[COAP]: << coap_init\r\n");

    return err_code;

}

static uint32_t message_send(coap_message_t * p_message)
{
    COAP_TRC("[COAP]: >> message_send\r\n");

    // Fetch the expected length of the packet serialized by passing length of 0.
    uint16_t expected_length = 0;
    uint32_t err_code = coap_message_encode(p_message, NULL, &expected_length);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Allocate a buffer to serialize the message into.
    uint8_t * p_buffer;
    uint32_t request_length = expected_length;
    err_code = nrf51_sdk_mem_alloc(&p_buffer, &request_length);
    if (err_code != NRF_SUCCESS)
    {
        COAP_TRC("[COAP]: p_buffer alloc error = 0x%08lX!\r\n", err_code);
        return err_code;
    }
    memset(p_buffer, 0, request_length);
    COAP_TRC("[COAP]: Alloc mem, p_buffer = %p\r\n", (uint8_t *)p_buffer);

    // Serialize the message.
    uint16_t buffer_length = (uint16_t)request_length;
    err_code = coap_message_encode(p_message, p_buffer, &buffer_length);
    if (err_code != NRF_SUCCESS)
    {
        COAP_TRC("[COAP]: Encode error!\r\n");
        COAP_TRC("[COAP]: Free mem, p_buffer = %p\r\n", p_buffer);
        UNUSED_VARIABLE(nrf51_sdk_mem_free(p_buffer));

        return err_code;
    }

    err_code = coap_transport_write(&p_message->port, &p_message->remote, p_buffer, buffer_length);

    if (is_request(p_message))
    {
        coap_queue_item_t item;
        item.mid      = p_message->header.id;
        item.callback = p_message->response_callback;
        item.p_buffer = p_buffer;
        item.age      = 60; // Default 60 seconds.
        item.token_len = p_message->header.token_len;
        memcpy(&item.remote, &p_message->remote, sizeof(coap_remote_t));
        memcpy(item.token, p_message->token, p_message->header.token_len);
        err_code = coap_queue_add(&item);
        if (err_code != NRF_SUCCESS)
        {
            COAP_TRC("[COAP]: Message queue error = 0x%08lX!\r\n", err_code);
            return err_code;
        }
    }
    else
    {
        COAP_TRC("[COAP]: Free mem, p_buffer = %p\r\n", p_buffer);
        UNUSED_VARIABLE(nrf51_sdk_mem_free(p_buffer));
    }

    COAP_TRC("[COAP]: << message_send\r\n");

    return err_code;
}

static uint32_t create_response(coap_message_t ** pp_response, coap_message_t * p_request, uint16_t data_size)
{
    uint32_t err_code;
    
    // Allocate space for a new message.
    uint32_t size = sizeof(coap_message_t);
    err_code = nrf51_sdk_mem_alloc((uint8_t **)pp_response, &size);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    coap_message_t * p_response = (*pp_response);
    
    memset(p_response, 0, sizeof(coap_message_t));
    COAP_TRC("[COAP]: Alloc mem, p_response = %p\r\n", (uint8_t *)p_response);

    if (data_size > 0)
    {
        // Allocate a scratch buffer for payload and options.
        size = data_size;
        err_code = nrf51_sdk_mem_alloc(&(p_response->p_data), &size);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        memset(p_response->p_data, 0, size);
        p_response->data_len = size;
        COAP_TRC("[COAP]: Alloc mem, p_response->p_data = %p\r\n", p_response->p_data);
    }
    
    coap_message_conf_t config;
    memset (&config, 0, sizeof(coap_message_conf_t));
    config.token_len = p_request->header.token_len;
    config.id        = p_request->header.id;
    config.code      = COAP_CODE_404_NOT_FOUND;
    config.port.port_number = COAP_SERVER_PORT;
    memcpy(config.token, p_request->token, p_request->header.token_len);
    
    if ((coap_msg_type_t)p_request->header.type == COAP_TYPE_CON)
    {
        config.type = COAP_TYPE_ACK; 
    }
    else
    {
        config.type = (coap_msg_type_t)p_request->header.type; 
    }
    
    err_code = coap_message_create(p_response, &config);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // TODO: Swap this out with message_remote_set function...
    memcpy(&p_response->remote, &p_request->remote, sizeof(coap_remote_t));

    
    return NRF_SUCCESS;
}

uint32_t coap_transport_read(const coap_port_t    * p_port,
                             const coap_remote_t  * p_remote,
                             uint32_t               result,
                             const uint8_t        * p_data,
                             uint16_t               datalen)
{
    COAP_TRC("[COAP]: >> coap_transport_read\r\n");

    COAP_MUTEX_LOCK();
    
    // Discard all packets if not success or truncated. 
    if (!(result == NRF_SUCCESS || result == UDP_TRUNCATED_PACKET))  
    {
        return NRF_SUCCESS;
    }
    
    uint32_t err_code;
    coap_message_t * p_message;

    // Allocate space for a new message.
    uint32_t size = sizeof(coap_message_t);
    err_code = nrf51_sdk_mem_alloc((uint8_t **)&p_message, &size);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    memset(p_message, 0, sizeof(coap_message_t));
    COAP_TRC("[COAP]: Alloc mem, p_message = %p\r\n", (uint8_t *)p_message);
    
    err_code = coap_message_decode(p_message, p_data, datalen, p_remote);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    if (result == UDP_TRUNCATED_PACKET)
    {
        coap_message_t * p_response;
        
        // create a response message.
        err_code = create_response(&p_response, p_message, 4); // 1 option, 1 byte ext delta, potential 2 byte integer for size1.
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        
        (void)coap_message_opt_uint_add(p_response, COAP_OPT_SIZE1, COAP_REQUEST_ENTITY_MAX_SIZE);
        
        p_response->header.token_len = 0;
        p_response->payload_len      = 0;
        
        // Override 404 code.
        p_response->header.code = COAP_CODE_413_REQUEST_ENTITY_TOO_LARGE;
        p_response->header.type = COAP_TYPE_RST;

        err_code = message_send(p_response);
        
        COAP_TRC("[COAP]: Free mem, p_response->p_data = %p\r\n", p_response->p_data);
        UNUSED_VARIABLE(nrf51_sdk_mem_free(p_response->p_data));
        
        COAP_TRC("[COAP]: Free mem, p_response = %p\r\n", (uint8_t *)p_response);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_response));

        COAP_TRC("[COAP]: Free mem, p_message = %p\r\n", (uint8_t *)p_message);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_message));
    }
    else if (is_ping(p_message))
    {
        coap_message_t * p_response;
        
        // create a response message.
        err_code = create_response(&p_response, p_message, 0);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        
        // Override 404 code.
        p_response->header.code = COAP_CODE_EMPTY_MESSAGE;
        
        if (0 != p_message->header.token_len  ||
            0 != p_message->options_count     ||
            0 != p_message->payload_len)
        {
            p_response->header.token_len = 0;
            p_response->options_count    = 0;
            p_response->payload_len      = 0;
            
            p_response->header.type = COAP_TYPE_RST;
        }
        
        err_code = message_send(p_response);
        
        COAP_TRC("[COAP]: Free mem, p_response = %p\r\n", (uint8_t *)p_response);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_response));

        COAP_TRC("[COAP]: Free mem, p_message = %p\r\n", (uint8_t *)p_message);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_message));
    }
    else if (is_response(p_message))
    {
        COAP_TRC("[COAP]: CoAP message type: RESPONSE\r\n");

        coap_queue_item_t * p_item;
        err_code = coap_queue_item_by_token_get(p_message->token, &p_item);
        if (err_code != NRF_SUCCESS)
        {
            UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_message));
            return err_code;
        }

        if (p_item->callback != NULL)
        {
            COAP_TRC("[COAP]: >> application callback\r\n");

            p_item->callback(p_message);

            COAP_TRC("[COAP]: << application callback\r\n");
        }

        COAP_TRC("[COAP]: Free mem, p_item->p_buffer = %p\r\n", p_item->p_buffer);
        UNUSED_VARIABLE(nrf51_sdk_mem_free(p_item->p_buffer));

        err_code = coap_queue_remove(p_item);

        COAP_TRC("[COAP]: Free mem, p_message = %p\r\n", (uint8_t *)p_message);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_message));
    }
    else if (is_request(p_message))
    {
        COAP_TRC("[COAP]: CoAP message type: REQUEST\r\n");

        uint8_t * uri_pointers[COAP_RESOURCE_MAX_DEPTH] = {0, };

        uint8_t uri_path_count = 0;
        uint16_t index;

        for (index = 0; index < p_message->options_count; index++)
        {
            if (p_message->options[index].number == COAP_OPT_URI_PATH)
            {
                uri_pointers[uri_path_count++] = p_message->options[index].p_data;
            }
        }
        
        coap_resource_t * found_resource;
        UNUSED_VARIABLE(coap_resource_get(&found_resource, uri_pointers, uri_path_count));
        
        
        coap_message_t * p_response;
        
        // create a response message.
        err_code = create_response(&p_response, p_message, COAP_MESSAGE_DATA_MAX_SIZE);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        // If resource was located.
        if (found_resource != NULL)
        {
            if (found_resource->callback != NULL)
            {
                if ((found_resource->permission == COAP_PERM_ALL) ||                              // Has full permission.
                    (((found_resource->permission) & (1 << ((p_message->header.code) - 1))) > 0)) // Has permission for the requested CoAP method.
                {
                    // Call resource handler
                    found_resource->callback(p_message, p_response);                    
                }
                else
                {
                    p_response->header.code = COAP_CODE_405_METHOD_NOT_ALLOWED;
                }
            }
            else
            {
                // Not allowed.
            }
        }
        else
        {
            // Reply with NOT FOUND.
            p_response->header.code = COAP_CODE_404_NOT_FOUND;

        }

        err_code = message_send(p_response);

        COAP_TRC("[COAP]: Free mem, p_response->p_data = %p\r\n", p_response->p_data);
        UNUSED_VARIABLE(nrf51_sdk_mem_free(p_response->p_data));

        COAP_TRC("[COAP]: Free mem, p_response = %p\r\n", (uint8_t *)p_response);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_response));

        COAP_TRC("[COAP]: Free mem, p_message = %p\r\n", (uint8_t *)p_message);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_message));

    }
    else
    {
        COAP_TRC("[COAP]: CoAP message type: UNKNOWN\r\n");

        COAP_TRC("[COAP]: Free mem, p_message = %p\r\n", (uint8_t *)p_message);
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_message));
    }

    COAP_MUTEX_UNLOCK();

    COAP_TRC("[COAP]: << coap_transport_read\r\n");
    return err_code;
}


uint32_t coap_request_send(coap_message_t * p_message)
{
    COAP_TRC("[COAP]: >> coap_request_send\r\n");

    if (p_message == NULL)
    {
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);
    }

    COAP_MUTEX_LOCK();

    uint32_t err_code;

    err_code = message_send(p_message);

    COAP_MUTEX_UNLOCK();

    COAP_TRC("[COAP]: << coap_request_send\r\n");

    return err_code;
}


uint32_t coap_request_create(coap_message_t ** p_request, coap_message_conf_t * p_config)
{
    COAP_TRC("[COAP]: >> coap_request_create\r\n");

    COAP_MUTEX_LOCK();

    uint32_t err_code;

    // Allocate space for a new message.
    uint32_t size = sizeof(coap_message_t);
    err_code = nrf51_sdk_mem_alloc((uint8_t **)p_request, &size);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    memset(*p_request, 0, sizeof(coap_message_t));
    COAP_TRC("[COAP]: Alloc mem, *p_request = %p\r\n", (uint8_t *)(*p_request));


    // Allocate a scratch buffer for payload and options.
    size = COAP_MESSAGE_DATA_MAX_SIZE;
    err_code = nrf51_sdk_mem_alloc(&((*p_request)->p_data), &size);
    if (err_code != NRF_SUCCESS)
    {
        COAP_TRC("[COAP]: Allocation of message data buffer failed!\r\n");

        COAP_TRC("[COAP]: Free mem, *p_request = %p\r\n", (uint8_t *)(*p_request));
        UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)(*p_request)));
        return err_code;
    }
    
    memset((*p_request)->p_data, 0, size);
    (*p_request)->data_len = size;
    
    COAP_TRC("[COAP]: Alloc mem, (*p_request)->p_data = %p\r\n", (uint8_t *)((*p_request)->p_data));

    // Set client port and initialize the message.
    p_config->port.port_number = COAP_CLIENT_PORT;
    
    if (p_config->id == 0) // Message id is not set, generate one.
    {
        p_config->id = m_message_id_counter++;
    }
    
    err_code = coap_message_create(*p_request, p_config);

    COAP_MUTEX_UNLOCK();

    COAP_TRC("[COAP]: << coap_request_create, result = 0x%08lX\r\n", err_code);

    return err_code;
}


uint32_t coap_request_delete(coap_message_t * p_message)
{
    COAP_TRC("[COAP]: >> coap_request_delete\r\n");

    COAP_MUTEX_LOCK();

    //If this is a request free the coap_message_t and the data buffer.

    COAP_TRC("[COAP]: Free mem, p_message->p_data = %p\r\n", p_message->p_data);
    UNUSED_VARIABLE(nrf51_sdk_mem_free(p_message->p_data));

    COAP_TRC("[COAP]: Free mem, p_message = %p\r\n", (uint8_t *)p_message);
    UNUSED_VARIABLE(nrf51_sdk_mem_free((uint8_t *)p_message));


    COAP_MUTEX_UNLOCK();

    COAP_TRC("[COAP]: << coap_request_delete\r\n");

    return NRF_SUCCESS;
}
