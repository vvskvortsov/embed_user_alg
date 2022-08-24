/*
 * mk_flash.h
 *
 *  Created on: Jan 16, 2019
 *      Author: skvortsov
 */

#ifndef SOURCE_OS_LIBOS_ARCH_INC_MK_FLASH_H_
#define SOURCE_OS_LIBOS_ARCH_INC_MK_FLASH_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
/*******************************************************************************
 * Description
 ******************************************************************************/
/*!******************************************************************************
 * @~russian
 * @file mk_flash.h
 * @authors skvortsov v., kulikov s.
 ******************************************************************************
 * @brief Интерфейс для доступа к внутренней флеш контроллера

 * @~russian
 * @details
 *
 * Драйвер предоставляет API для чтения и записи во внутреннюю флеш микроконтроллера.
 * Функция записи производит запись только если данные изменены, т.е. обладает защитой от ненужной перезаписи.
 * Функции драйвера являются потокобезопасными.
 *
 * @attention
 * Для работы необходимо сделать инициализацю флеш через вызов фунции mk_flash_init().
 * */


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @~russian
 * @brief Флаги завершения функций.
 */
enum mk_flash_generic_status {
	MK_FLASH_RET_SUCCESS = 0,		/*!< @~russian Успех. */
	MK_FLASH_RET_FAIL = -1,			/*!< @~russian Неудача. */
	MK_FLASH_RET_NEED_WRITE = -2,		/*!< @~russian Нужна перезапись страницы. */
	MK_FLASH_NULL_PTR_BUF = -1,		/*! @todo добавить описание всех кодов возврата (используются в проекте weblinkerа)*/
	MK_FLASH_ERASE_ERR = -2,
	MK_FLASH_VERIFY_ERASE_ERR = -3,
	MK_FLASH_PROGRAM_ERR = -4,
	MK_FLASH_VERIFY_WRITE_ERR = -5,
	MK_FLASH_INIT_ERR = -6,
	MK_FLASH_SEC_STATE_ERR = -7,
};



/*!
 * @~russian
 * @brief Инициализирует драйвер для работы с внутренней flash памятью контроллера.
 * @return                  		 	Результат инициализации.
 * @retval MK_FLASH_RET_SUCCESS 			Успех.
 * @retval MK_FLASH_RET_FAIL   			Произошла ошибка.
 */
int8_t mk_flash_init(void);

/*
 * Запись масива во внутреннюю память контроллера
 */

/*!
 * @~russian
 * @brief Записывает массив данных по указанному адресу.
 * @attention Запись не будет осуществлена, если данные на запись совпадают с данными фо флеш.
 * В таком случае запись считается успешной.
 * @param address   	Адрес флеш на запись.
 * @param buff 		Указатель на буфер данных на запись.
 * @param length 	Количество слов на запись. (1 слово = 4 байта)
 * @return                  		 	Результат записи.
 * @retval MK_FLASH_RET_SUCCESS 			Успех.
 * @retval MK_FLASH_RET_FAIL   			Произошла ошибка.
 */
int8_t mk_flash_write(uint32_t address, uint32_t * buff, uint32_t length);

/*
 *
 */
/*!
 * @~russian
 * @brief Читает слово из внутренней памяти контроллера.
 * @param address   	Адрес флеш на чтение.
 * @return                  		 	Прочитанное слово.
 */
uint32_t mk_flash_read(uint32_t address);





/*
 * @~russian
 * @brief Стирает флеш память по указанному адресу
 * @param address     Адрес флеш на чтение
 * @param size        Размер стираемой памяти
 * @return                         Результат работы
 * @retval MK_FLASH_RET_SUCCESS    Успех
 * @retval MK_FLASH_RET_FAIL   	   Произошла ошибка
 */
int8_t mk_flash_erase(uint32_t address, uint32_t size);













#endif /* SOURCE_OS_LIBOS_ARCH_INC_MK_FLASH_H_ */












































