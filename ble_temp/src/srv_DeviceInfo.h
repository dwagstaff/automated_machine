/*
 * srv_DeviceInfo.h
 *
 *  Created on: Jan 25, 2015
 *      Author: dwagstaff
 */

#ifndef SRV_DEVICEINFO_H_
#define SRV_DEVICEINFO_H_


#define MANUFACTURER_NAME                "Wagstaff, Inc."                          /**< Manufacturer. Will be passed to Device Information Service. */
#define MODEL_NUM                        "NS-HTS-EXAMPLE"                           /**< Model number. Will be passed to Device Information Service. */
#define MANUFACTURER_ID                  0x1122334455                               /**< Manufacturer ID, part of System ID. Will be passed to Device Information Service. */
#define ORG_UNIQUE_ID                    0x667788                                   /**< Organizational Unique ID, part of System ID. Will be passed to Device Information Service. */
#define FIRMWARE_REVISION				"FW 1.0"				// Firmware Revision
#define HARDWARE_REVISION				"HW 1.0"				// Hardware Revision
#define SOFTWARE_REVISION				"SW 1.0"				// Software Revision


#define PNP_ID_VENDOR_ID_SOURCE          0x02                                           /**< Vendor ID Source. */
#define PNP_ID_VENDOR_ID                 0x1915                                         /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID                0xEEEE                                         /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION           0x0001



extern void dis_init(void);

#endif /* SRV_DEVICEINFO_H_ */
