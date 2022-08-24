/*
 * mk_crc.c
 *
 *  Created on: Mar 2, 2020
 *      Author: skvortsov
 */

#include <fsl_crc.h>
#include "mk_crc.h"
uint32_t mk_crc_calc(const uint8_t *data, size_t dataSize) {

	crc_config_t config;
	config.crcBits = kCrcBits32;
	config.crcResult = kCrcFinalChecksum;
	config.complementChecksum = true;
	config.reflectIn = true;
	config.reflectOut = true;
	config.seed = 0xFFFFFFFF;
	config.polynomial = 0x04C11DB7;

//	switch (crc_type) {
//	case CRC_MODBUS:
//		default:
//		config.crcBits = kCrcBits16;
//		config.crcResult = kCrcFinalChecksum;
//		config.complementChecksum = false;
//		config.reflectIn = true;
//		config.reflectOut = true;
//		config.seed = 0xFFFF;
//		config.polynomial = 0x8005;
//		break;
//	case CRC_32:
//		config.crcBits = kCrcBits32;
//		config.crcResult = kCrcFinalChecksum;
//		config.complementChecksum = true;
//		config.reflectIn = true;
//		config.reflectOut = true;
//		config.seed = 0xFFFFFFFF;
//		config.polynomial = 0x04C11DB7;
//		break;
//	case CRC_8:
//		return crc8_calc(data, dataSize, crc_type);
//		break;
//	}

	CRC_Init(CRC0, &config);

	CRC_WriteData(CRC0, (uint8_t*) data, dataSize);

	uint32_t crc;

//	switch (crc_type) {
//	case CRC_MODBUS:
//	default:
//		crc = CRC_Get16bitResult(CRC0);
//		break;
//	case CRC_32:
//		crc = CRC_Get32bitResult(CRC0);
//		break;
//	}
	crc = CRC_Get32bitResult(CRC0);
	return crc;
}

