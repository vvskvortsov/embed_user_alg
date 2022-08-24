/*
 * os_header.h
 *
 *  Created on: 19 авг. 2022 г.
 *      Author: skvortsov
 */

#ifndef OS_HEADER_H_
#define OS_HEADER_H_

#include <stdint.h>

struct os_header {
	uint8_t type[14];
	uint16_t revision;
	uint8_t magic[4];
	uint32_t crc;
	uint32_t hex_crc;
	uint32_t os_start;
	uint32_t os_end;
	uint8_t version[16];
	uint8_t unused[204];
} __attribute__((packed, aligned(4)));


#endif /* OS_HEADER_H_ */
