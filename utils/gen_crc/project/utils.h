#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string>

/*!
 @~russian
 * @brief В файле собраны вспомогательные функции.
 */


/*!
 @~russian
 * @brief Зеркально отображает все биты в числе.
 * @param   input  Исходное число.
 * @return                   Число с инвертированными битами.
*/
uint8_t reverse(uint8_t input);
uint32_t reverse(uint32_t input);


/*!
 @~russian
 * @brief Преобразует строку в виде шестнадцатиричного числа в число.
 * @param   input  Исходная строка.
 * @return                   Число.
*/
uint32_t parseValueFromHexString(std::string input);


/*!
 @~russian
 * @brief Преобразует число в строку в шестнадцатиричном формате в верхнем регистре.
 * @param   value  Исходное число.
 * @return                   Строка.
*/
std::string decToUpperHexString(int value);


/*!
 @~russian
 * @brief Меняет местами байты в строке в виде шестнадцатиричного числа (little-endian and big-endian). Если размер строки не кратен 2, то дополняет строку нулями.
 * @param   input  Исходная строка.
 * @param   size  Размер строки в символах, в которой необходимо байты поменять местами.
 * @warning Размер передается в символах, при этом в шестнадцатиричной строке 2 символа представляют 1 байт числа.
 * @return                   Результат выполнения:
 *                           0 - успех;
 *                           1 - неудача.
*/
int swapHexString(std::string &input, uint32_t size);



#endif // UTILS_H
