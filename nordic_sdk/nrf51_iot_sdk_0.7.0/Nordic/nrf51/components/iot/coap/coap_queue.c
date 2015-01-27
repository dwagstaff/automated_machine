#include "string.h"
#include "coap_queue.h"
#include "sdk_config.h"

#if (COAP_DISABLE_API_PARAM_CHECK == 0)

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);                                               \
    }
#else 
    
#define NULL_PARAM_CHECK(PARAM)

#endif // COAP_DISABLE_API_PARAM_CHECK 

static coap_queue_item_t m_queue[COAP_MESSAGE_QUEUE_SIZE];
static uint8_t           m_message_queue_count = 0;

uint32_t coap_queue_init(void)
{
    for (uint8_t i = 0; i < COAP_MESSAGE_QUEUE_SIZE; i++)
    {
        memset(&m_queue[i], 0, sizeof(coap_queue_item_t));
    }
    m_message_queue_count = 0;
    
    return NRF_SUCCESS;
}

uint32_t coap_queue_add(coap_queue_item_t * item)
{
    NULL_PARAM_CHECK(item);
    
    if (m_message_queue_count >= COAP_MESSAGE_QUEUE_SIZE)
    {
       return (NRF_ERROR_NO_MEM | IOT_COAP_ERR_BASE);
    }
    else 
    {
        for (uint8_t i = 0; i < COAP_MESSAGE_QUEUE_SIZE; i++)
        {
            if (m_queue[i].p_buffer == NULL)
            {
                // Free spot in message queue. Add message here...
                m_queue[i].mid       = item->mid;
                m_queue[i].p_buffer  = item->p_buffer;
                m_queue[i].callback  = item->callback;
                m_queue[i].token_len = item->token_len;
                memcpy(m_queue[i].token, item->token, item->token_len);
                
                m_message_queue_count++;

                return NRF_SUCCESS;
            }
        }
        
    }
    return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
}

uint32_t coap_queue_remove(coap_queue_item_t * p_item)
{
    for (uint8_t i = 0; i < COAP_MESSAGE_QUEUE_SIZE; i++)
    {
        if (p_item == (coap_queue_item_t *)&m_queue[i])
        {
            memset(&m_queue[i], 0, sizeof(coap_queue_item_t));
            m_message_queue_count--;
            return NRF_SUCCESS;
        }
    }

    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}

uint32_t coap_queue_index_by_token(uint8_t * token, uint8_t * index)
{
    for (uint8_t i = 0; i < COAP_MESSAGE_QUEUE_SIZE; i++)
    {
        if (memcmp(m_queue[i].token, token, 8) == 0)
        {
            *index = i;
            return NRF_SUCCESS;
        }
    }
    
    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}

uint32_t coap_queue_index_by_mid(uint16_t message_id, uint8_t * index)
{
    return NRF_SUCCESS;
}

uint32_t coap_queue_callback_by_index(uint8_t index, coap_response_callback_t callback)
{
    return NRF_SUCCESS;
}

uint32_t coap_queue_item_by_token_get(uint8_t * token, coap_queue_item_t ** pp_item)
{
    for (uint8_t i = 0; i < COAP_MESSAGE_QUEUE_SIZE; i++)
    {
        if ((0 != m_queue[i].token_len) && 
            (memcmp(m_queue[i].token, token, m_queue[i].token_len) == 0))
        {
            *pp_item = &m_queue[i];
            return NRF_SUCCESS;
        }
    }
    
    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}
