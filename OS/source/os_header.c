/*
 * os_header.c
 *
 *  Created on: 19 авг. 2022 г.
 *      Author: skvortsov
 */

#include "os_header.h"


extern char __boot_os_header_start; /*!< Адрес начала заголовка прошивки ОС. */
extern char __boot_os_start; /*!< Адрес начала прошивки ОС. */
extern char __boot_os_end; /*!< Адрес конца текущей прошивки ОС. */
extern char __boot_os_mem_end; /*!< Адрес конца прошивки ОС максимально допустимый. */
extern char __boot_header; /*!< Адрес начала заголовка загрузчика.*/

volatile struct os_header __attribute__((section(".os_wrap_header"))) os_header = {
	{	"VV_Module"},
	100,
	{	0x5F,0x49,0x24,0x03},
	0,
	0,
	(const uint32_t)&__boot_os_start, //символ начала ос
	(const uint32_t)&__boot_os_end,//символ конца ос
	{"v. 1.0.0.0"},
	{0},
};
