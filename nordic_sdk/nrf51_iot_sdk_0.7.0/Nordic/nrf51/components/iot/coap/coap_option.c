#include <stdlib.h>
#include <string.h>

#include "coap_option.h"

#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);                                               \
    }

uint32_t coap_opt_string_encode(uint8_t * p_encoded, uint16_t * p_length, uint8_t * p_string, uint16_t str_len)
{
    NULL_PARAM_CHECK(p_encoded);
    NULL_PARAM_CHECK(p_length);
    NULL_PARAM_CHECK(p_string);
    
    if (str_len > *p_length)
    {
        return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
    }
    
    memcpy(p_encoded, p_string, str_len);
    
    *p_length = str_len;
    
    return NRF_SUCCESS;
}

uint32_t coap_opt_string_decode(uint8_t * p_string, uint16_t * p_length, uint8_t * p_encoded)
{
    return NRF_SUCCESS;
}

uint32_t coap_opt_uint_encode(uint8_t * p_encoded, uint16_t * p_length, uint32_t data)
{
    NULL_PARAM_CHECK(p_encoded);
    NULL_PARAM_CHECK(p_length);
    
    uint16_t byte_index = 0;
    
    if (data <= UINT8_MAX)
    {
        if (*p_length < sizeof(uint8_t))
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }
        
        p_encoded[byte_index++] = (uint8_t)data;
    }
    else if (data <= UINT16_MAX)
    {
        if (*p_length < sizeof(uint16_t))
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }
        
        p_encoded[byte_index++] = (uint8_t)((data & 0xFF00) >> 8);
        p_encoded[byte_index++] = (uint8_t)(data & 0x00FF);
    }
    else
    {
        if (*p_length < sizeof(uint32_t))
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }
        
        p_encoded[byte_index++] = (uint8_t)((data & 0xFF000000) >> 24);
        p_encoded[byte_index++] = (uint8_t)((data & 0x00FF0000) >> 16);
        p_encoded[byte_index++] = (uint8_t)((data & 0x0000FF00) >> 8);
        p_encoded[byte_index++] = (uint8_t)(data & 0x000000FF);
    }
    
    
    
    *p_length = byte_index;
    
    return NRF_SUCCESS;
}

uint32_t coap_opt_uint_decode(uint32_t * p_data, uint16_t * p_length, uint8_t * p_encoded)
{
    return NRF_SUCCESS;
}
