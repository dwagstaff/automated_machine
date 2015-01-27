#include <string.h>

#include "coap_resource.h"
#include "coap_api.h"
#include "sdk_config.h"

static coap_resource_t * mp_root_resource = NULL;

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);                                               \
    }

uint32_t coap_resource_init(void)
{
    mp_root_resource = NULL;
    return NRF_SUCCESS;
}    
    
uint32_t coap_resource_create(coap_resource_t * p_resource, const char * name)
{
    NULL_PARAM_CHECK(p_resource);
    NULL_PARAM_CHECK(name);
    
    if (strlen(name) > COAP_RESOURCE_MAX_NAME_LEN)
    {
        return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
    }
    
    memcpy(p_resource->name, name, strlen(name));
    
    if (mp_root_resource == NULL)
    {
        mp_root_resource = p_resource;
    }
    
    return NRF_SUCCESS;
}

uint32_t coap_resource_child_add(coap_resource_t * p_parent, coap_resource_t * p_child)
{
    NULL_PARAM_CHECK(p_parent);
    NULL_PARAM_CHECK(p_child);
    
    if (p_parent->child_count == 0)
    {
        p_parent->p_front = p_child;
        p_parent->p_tail = p_child;
    }
    else 
    {
        coap_resource_t * p_last_sibling = p_parent->p_tail;
        p_last_sibling->p_sibling = p_child;
        p_parent->p_tail = p_child;
    }
    
    p_parent->child_count++;
    
    return NRF_SUCCESS;
}

static uint32_t generate_path(coap_resource_t * p_current_resource, char * parent_path, uint8_t * string, uint16_t * length)
{
    uint32_t err_code = NRF_SUCCESS;
    
    if (parent_path == NULL)
    {
        uint8_t subpath[2] = {0,};
        subpath[0] = '<';
        
        (void)subpath;
        
        if (p_current_resource->p_front != NULL)
        {
            coap_resource_t * next_child = p_current_resource->p_front;
            do
            {
                err_code = generate_path(next_child, (char *)subpath, string, length);
                if (err_code != NRF_SUCCESS)
                {
                    return err_code;
                }
                next_child = next_child->p_sibling;
            } while (next_child != NULL);
        }
    }
    else
    {   
        uint16_t size = strlen(parent_path) + strlen(p_current_resource->name) + 4;
        uint8_t subpath[size];
        memset(subpath, 0, size);
        
        strcpy((char *)&subpath[0], parent_path);
        subpath[strlen(parent_path)] = '/';
        strcpy((char *)&subpath[strlen(parent_path)+1], p_current_resource->name);

        
        (void)subpath;
        
        if (p_current_resource->p_front != NULL)
        {
            coap_resource_t * next_child = p_current_resource->p_front;
            do
            {
                err_code = generate_path(next_child, (char *)subpath, string, length);
                if (err_code != NRF_SUCCESS)
                {
                    return err_code;
                }
                next_child = next_child->p_sibling;
            } while (next_child != NULL);
        }

        subpath[strlen((char *)subpath)] = '>';
        subpath[strlen((char *)subpath)] = ',';
        
        if (strlen((char *)subpath) <= (*length))
        {
            *length -= strlen((char *)subpath);
            memcpy(&string[strlen((char *)string)], (uint8_t *)subpath, strlen((char *)subpath));
        }
        else
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }    
    }
    
    return err_code;
}

uint32_t coap_resource_well_known_generate(uint8_t * string, uint16_t * length)
{
    NULL_PARAM_CHECK(string);
    NULL_PARAM_CHECK(length);

    if (mp_root_resource == NULL)
    {
        return (NRF_ERROR_INVALID_STATE | IOT_COAP_ERR_BASE);
    }
  
    memset(string, 0, *length);
    
    uint32_t err_code = generate_path(mp_root_resource, NULL, string, length);
    
    string[strlen((char *)string) - 1] = '\0'; // remove the last comma
    
    return err_code;
}

static coap_resource_t * coap_resource_child_resolve(coap_resource_t * p_parent, 
                                                     char *            path)
{
    coap_resource_t * result = NULL;
    if (p_parent->p_front != NULL)
    {
        coap_resource_t * sibling_in_question = p_parent->p_front;

        do {
            // Check if the sibling name match.
            size_t size = strlen(sibling_in_question->name);
            if (strncmp(sibling_in_question->name, path, size) == 0)
            {
                return sibling_in_question;
            }
            else 
            {
                sibling_in_question = sibling_in_question->p_sibling;
            }
        } while (sibling_in_question != NULL);
    }
    return result;
}

uint32_t coap_resource_get(coap_resource_t ** p_resource, uint8_t * uri_pointers[], uint8_t num_of_uris)
{
    if (mp_root_resource == NULL)
    {
        // Make sure pointer is set to NULL before returning.
        *p_resource = NULL;
        return (NRF_ERROR_INVALID_STATE | IOT_COAP_ERR_BASE);
    }
    
    coap_resource_t * p_current_resource = mp_root_resource;
    
    // Every node should start at root. 
    for (uint8_t i = 0; i < num_of_uris; i++)
    {   
        p_current_resource = coap_resource_child_resolve(p_current_resource, (char *)uri_pointers[i]);
        
        if (p_current_resource == NULL)
        {
            // Stop looping as this direction will not give anything more.
            break;
        }
    }
    
    if (p_current_resource != NULL)
    {
        *p_resource = p_current_resource;
        return NRF_SUCCESS;
    }
    
    // If nothing has been found.
    *p_resource = NULL;
    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}

uint32_t coap_resource_process_request(coap_resource_t * p_resource, coap_message_t * p_request, coap_message_t * p_response);
