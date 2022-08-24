/*
 * crc_check.c
 *
 *  Created on: 18 авг. 2022 г.
 *      Author: skvortsov
 */

#include "mk_watchdog.h"
#include "return_code.h"
#include "os_header.h"
#include "mk_flash.h"


extern char __boot_os_header_start; /*!< Адрес начала заголовка прошивки ОС. */
extern char __boot_os_start; /*!< Адрес начала прошивки ОС. */
extern char __boot_os_end; /*!< Адрес конца текущей прошивки ОС. */
extern char __boot_os_mem_end; /*!< Адрес конца прошивки ОС максимально допустимый. */
extern char __boot_header; /*!< Адрес начала заголовка загрузчика.*/


volatile struct os_header os_header;

static int8_t boot_init_os_header()
{
	uint32_t * ptr = (uint32_t *) &os_header;
	for (uint8_t i = 0; i < sizeof(os_header) / 4; i++) {
		*(ptr + i) = mk_flash_read((uint32_t) (&__boot_os_header_start + 4 * i));
	}
}

static int8_t check_os_crc() {

	boot_init_os_header();

	if (os_header.os_start % 4 != 0 || os_header.os_end % 4) //если в хедере записана ересь то бутлоадер упадет на некратных 4  адресах
		return RET_ERR;
	uint32_t calc_crc = boot_calc_os_crc();
	if (calc_crc == os_header.crc)
		return RET_OK;
	else
		return RET_ERR;
}


int check_start() {
	if (mk_watchdog_get_reset_reason() == RESET_NORMAL) { //если пришла команда на перезагрузку, пригнорировать и сьросить регистры watchdog
		mk_watchdog_clean_reset_count();
	} else {
		// Если слишком большое число перезапусков по сторожевому таймеру
		volatile uint16_t watchdog_reset_count = mk_watchdog_get_reset_count();
	}

	// Если CRC ОС не валидна
	uint8_t ret = check_os_crc();
	if (ret != RET_OK) {
	}
	return 0;
}





