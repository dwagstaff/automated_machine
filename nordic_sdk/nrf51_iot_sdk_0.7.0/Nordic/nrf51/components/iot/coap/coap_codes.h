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

/** @file coap_codes.h
 *
 * @defgroup iot_sdk_coap_codes CoAP Codes
 * @ingroup iot_sdk_coap
 * @{
 * @brief TODO.
 */

#ifndef COAP_CODES_H__
#define COAP_CODES_H__

#define COAP_CODE(c, dd) \
    (((c & 0x7) << 5) | (dd & 0x1F))

typedef enum
{
    // CoAP Empty Message
    COAP_CODE_EMPTY_MESSAGE                  = COAP_CODE(0,00),

    // CoAP Method Codes 
    COAP_CODE_GET                            = COAP_CODE(0,01),
    COAP_CODE_POST                           = COAP_CODE(0,02),
    COAP_CODE_PUT                            = COAP_CODE(0,03),
    COAP_CODE_DELETE                         = COAP_CODE(0,04),

    // CoAP Success Response Codes
    COAP_CODE_201_CREATED                    = COAP_CODE(2,01),
    COAP_CODE_202_DELETED                    = COAP_CODE(2,02),
    COAP_CODE_203_VALID                      = COAP_CODE(2,03),
    COAP_CODE_204_CHANGED                    = COAP_CODE(2,04),
    COAP_CODE_205_CONTENT                    = COAP_CODE(2,05),

    // CoAP Client Error Response Codes 
    COAP_CODE_400_BAD_REQUEST                = COAP_CODE(4,00),
    COAP_CODE_401_UNAUTHORIZED               = COAP_CODE(4,01),
    COAP_CODE_402_BAD_OPTION                 = COAP_CODE(4,02),
    COAP_CODE_403_FORBIDDEN                  = COAP_CODE(4,03),
    COAP_CODE_404_NOT_FOUND                  = COAP_CODE(4,04),
    COAP_CODE_405_METHOD_NOT_ALLOWED         = COAP_CODE(4,05),
    COAP_CODE_406_NOT_ACCEPTABLE             = COAP_CODE(4,06),
    COAP_CODE_412_PRECONDITION_FAILED        = COAP_CODE(4,12),
    COAP_CODE_413_REQUEST_ENTITY_TOO_LARGE   = COAP_CODE(4,13),
    COAP_CODE_415_UNSUPPORTED_CONTENT_FORMAT = COAP_CODE(4,15),

    // CoAP Server Error Response Codes
    COAP_CODE_500_INTERNAL_SERVER_ERROR      = COAP_CODE(5,00),
    COAP_CODE_501_NOT_IMPLEMENTED            = COAP_CODE(5,01),
    COAP_CODE_502_BAD_GATEWAY                = COAP_CODE(5,02),
    COAP_CODE_503_SERVICE_UNAVAILABLE        = COAP_CODE(5,03),
    COAP_CODE_504_GATEWAY_TIMEOUT            = COAP_CODE(5,04),
    COAP_CODE_505_PROXYING_NOT_SUPPORTED     = COAP_CODE(5,05)
} coap_msg_code_t;

#endif // COAP_CODES_H__

/** @} */
