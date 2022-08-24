/*
 * boot_header.c
 *
 *  Created on: 18 авг. 2022 г.
 *      Author: skvortsov
 */
#include "boot_header.h"

volatile struct boot_header __attribute__((section(".boot_wrap_header"))) boot_header = {
	{"VV_Module"},
	100,
	{"v. 1.0.0.0"},
	{0},
};
