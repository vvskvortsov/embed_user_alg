/*
 * mk_watchdog.h
 *
 *  Created on: 05 февр. 2019 г.
 *      Author: kulikovs
 */

#ifndef SOURCE_OS_LIBOS_ARCH_INC_MK_WATCHDOG_H_
#define SOURCE_OS_LIBOS_ARCH_INC_MK_WATCHDOG_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

// Возможные причины перезапуска контроллера
enum RESET_REASON {
	RESET_NORMAL = 1,
	RESET_WATCHDOG = 2,
};


/*
 * Получить текущее число перезапусков
 */
uint16_t mk_watchdog_get_reset_count();


/*
 * Получить причину перезапуска
 */
uint8_t mk_watchdog_get_reset_reason();


/*
 * Сбрость счетчик перезапусков
 */
void mk_watchdog_clean_reset_count();


int8_t mk_watchdog_get_reset_reason_buff(); //использование буферизируемых регистров для получения значения


void mk_watchdog_clean_reset_reason_buff();
/*
 * Инициализация сторожевого таймена и установка времени срабатывания
 */
int mk_watchdog_init(uint32_t time_ms);


/*
 * Сброс значения счетчика сторожевого таймера.
 * Если после инициализации сторожевого таймера долго не вызывать эту функции,
 * то контроллер будет перезапущен.
 *
 *
 * !!!!!!!! на сброс требуется 2-3 цикла тактирования. Watchdog работает на частоте 1 кГц,
 * следовательно нельзя его обновлять чаще, чем 3 мс.
 */
void mk_watchdog_refresh();
int mk_watchdog_check_init();


//запретить обновление wdog
void mk_watchdog_make_mk_reset();

#ifdef __cplusplus
}
#endif

#endif /* SOURCE_OS_LIBOS_ARCH_INC_MK_WATCHDOG_H_ */
