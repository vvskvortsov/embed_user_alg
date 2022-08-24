/*
 * mk_flash.c
 *
 *  Created on: Jan 16, 2019
 *      Author: skvortsov
 */

/******************************************
 *           Includes
 ******************************************/

/*
 * LIBOS definitions.
 * LIBOS определения.
 * */
#include "mk_flash.h"
/*
 * NXP drivers.
 * NXP драйверы.
 * */
#include "fsl_flash.h"

uint32_t mk_flash_read(uint32_t address)
{
	return *(volatile uint32_t *) address;
}
