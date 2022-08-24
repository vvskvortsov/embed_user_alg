/*
 * mk_crc.h
 *
 *  Created on: Mar 2, 2020
 *      Author: skvortsov
 */

#ifndef SOURCES_LIBS_LIBOS_ARCH_INC_MK_CRC_H_
#define SOURCES_LIBS_LIBOS_ARCH_INC_MK_CRC_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stddef.h>
/*******************************************************************************
 * Description
 ******************************************************************************/
/*!******************************************************************************
 * @~russian
 * @file mk_flash.h
 * @authors skvortsov v.
 ******************************************************************************
 * @brief Интерфейс для доступа к аппаратному блоку вычисления контрольных сумм CRC

 * @~russian
 * @details
 *
 * Драйвер предоставляет API для вычисления контрольных сумм CRC.
 *
 * @attention Если аппаратный блок не поддерживает контрольную сумму, которая нужна, то в функции  mk_crc_calc делается вызов на конкретную
 *   программную реализацию драйвера crc. Поэтому в некоторых случаях при включенном LIBS_CRC_USE_HARDWARE, могут быть включены некоторые программные реализации.
 *
 * */


/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*!
* @~russian
* @brief Считает контрольную сумму для данных с помощью аппаратного блока.
* @attention Если аппаратный блок не поддерживает контрольную сумму, которая нужна, то в функции  делается вызов на конкретную
*   программную реализацию драйвера crc. Поэтому в некоторых случаях при включенном LIBS_CRC_USE_HARDWARE, могут быть включены некоторые программные реализации.
* @param data		Указатель на данные.
* @param data_length	Длина данных в байтах.
* @param crc_type	Вид контрольной суммы.
* @return                  		 	Посчитанная контрольная сумма.
*/
uint32_t mk_crc_calc(const uint8_t *data, size_t data_length);

#endif /* SOURCES_LIBS_LIBOS_ARCH_INC_MK_CRC_H_ */
