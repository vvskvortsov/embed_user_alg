#ifndef HEXHANDLER_H
#define HEXHANDLER_H

#include <cstdint>
#include <string>


/*!
 @~russian
 * @brief Класс для работы с хекс файлом путем стандартных операций.
 */
class HexHandler
{
public:
    HexHandler();
    static const uint32_t SIZE_OFFSET {1}; //начала поля размер
    static const uint32_t SIZE_LENGTH {2};   //длина поля размер
    static const uint32_t DATA_OFFSET {9}; //начала поля данных
    static const uint32_t CMD_OFFSET {7}; //начала поля команда
    static const uint32_t CMD_LENGTH {2}; //длина поля команда
    static const uint32_t ADDR_OFFSET {3}; //начала поля адрес
    static const uint32_t ADDR_LENGTH {4};   //длина поля адрес
    static const uint32_t EXT_ADDR_OFFSET {9}; //начала поля расширенный адрес
    static const uint32_t EXT_ADDR_LENGTH {4};   //длина поля расширенный адрес


    /*!
     @~russian
     * @brief Возвращает номер команды, полученный из строки hex файла.
     * @param   line  Hex строка.
     * @return           Номер команды.
    */
    uint32_t ParseCmdFromLine(std::string &line);

    /*!
     @~russian
     * @brief Возвращает данные из строки hex файла и конвертирует в инт формат.
     * @param   line  Hex строка.
     * @return           Данные в инт формате.
    */
    uint32_t ParseDataFromLine(std::string &&line);

    /*!
     @~russian
     * @brief Возвращает данные из строки hex файла и конвертирует в инт формат.
     * @param   line  Hex строка.
     * @return           Данные в инт формате.
    */
    uint32_t ParseDataFromLine(std::string &line);


    /*!
     @~russian
     * @brief Возвращает смещение адреса (для команд 2, 4), полученный из строки hex файла.
     * @param   line  Hex строка.
     * @return           смещение адреса.
    */
    uint32_t ParseExtAddrFromLine(std::string &line);


        /*!
     @~russian
     * @brief Возвращает размер строки, полученный из строки hex файла.
     * @param   line  Hex строка.
     * @return           Размер строки.
    */
    uint32_t ParseSizeFromLine(std::string &line);


        /*!
     @~russian
     * @brief Возвращает адрес, полученный из строки hex файла.
     * @param   line  Hex строка.
     * @return           Адрес.
    */
    uint32_t ParseAddrFromLine(std::string &line);


    /*!
     @~russian
     * @brief Преобразует номер колонки данных хекс строки в номер колонки в хекс файле.
     * @param   dataCol  номер колонки данных хекс строки.
     * @return           номер колонки в хекс файле.
    */
    uint32_t ConvertDataColToHexCol(uint32_t dataCol);

    void FillLineWithFFToSize(std::string &line, uint32_t size);

    void CalcAndWriteHexCRCforLine(std::string &line);

    ///< Команды hex формата
    enum hex_commands {
        CMD_DATA              = 0x00, ///< Запись данных
        CMD_EOF               = 0x01, ///< Конец файла
        CMD_EXT_SEG_ADDR      = 0x02, ///< Расширенный адрес сегмента
        CMD_START_SEG_ADDR    = 0x03, ///< Адрес сегмента
        CMD_EXT_LINEAR_ADDR   = 0x04, ///< Запись расширенного адреса
        CMD_START_LINEAR_ADDR = 0x05, ///< Начало записи расширенного адреса
    };
private:

    /*!
     @~russian
     * @brief Преобразует хекс данные в виде строки в инт.
     * @param   input  строка
     * @return           инт.
    */
    uint32_t ConvertHexStringToInt(std::string &input);
    uint32_t ConvertHexStringToInt(const std::string &&input);
};

#endif // HEXHANDLER_H
