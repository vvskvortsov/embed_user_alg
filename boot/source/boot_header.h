/*
 * boot_header.h
 *
 *  Created on: 18 авг. 2022 г.
 *      Author: skvortsov
 */

#ifndef BOOT_HEADER_H_
#define BOOT_HEADER_H_

#include <stdint.h>

struct boot_header {
	uint8_t type[14]; /*!< Module type*/
	uint16_t revision; /*!< Revision. */
	uint8_t version[16];/*!< OS version*/
	uint8_t unused[224];
} __attribute__((packed, aligned(4)));

#endif /* BOOT_HEADER_H_ */
