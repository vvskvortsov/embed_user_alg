#ifndef FIRMWAREFILEHANDLER_H
#define FIRMWAREFILEHANDLER_H

#include <string>
#include "HexHandler.h"

/*!
 @~russian
 * @brief Класс для работы с файлами нашей прошивки и подсчета контрольных сумм.
 */
class FirmwareFileHandler {
public:
    FirmwareFileHandler();



    /*!
     @~russian
     * @brief  Исправляет хедер прошивки (зануляет контрольные суммы) и парсит его.
     * @param   inputfilePath  Имя входящего файла.
     * @param   outputfilePath Имя исправленного файла.
    */
    //@warning Работает только если длина строк хедера постоянна.
    int
    ParseHeader(std::string inputfilePath, std::string outputfilePath);

    /*!
     @~russian
     * @brief  Заполняет пробелы в данных hex файла для того, чтобы контрольная сумма на контроллере высчитывалась верно и не было пробелов во флеше с мусором.
     * @param   inputfilePath  Имя входящего файла.
     * @param   outputfilePath Имя исправленного файла.
    */
    int
    FillHexWithFF(std::string inputfilePath, std::string outputfilePath);

    /*!
     @~russian
     * @brief  Высчитывает контрольную сумму для данных hex файла (то, что отправляет во флеш контроллера).
     * @param   inputfilePath  Имя входящего файла.
     * @return   Контрольная сумма.
    */
    uint32_t
    CalcRawCrc(std::string inputfilePath);
    /*!
     @~russian
     * @brief  Записывает контрольную сумму в файл.
     * @param   crc             Контрольная сумма.
     * @param   type            Тип контрольной суммы.
     * @param   inputfilePath  Имя входящего файла.
     * @param   outputfilePath Имя исправленного файла.
    */
    void
    WriteCrcToFile(uint32_t crc, uint32_t type, std::string inputfilePath,
                   std::string outputfilePath);

    /*!
     @~russian
     * @brief  Высчитывает контрольную сумму для всего файла.
     * @param   inputfilePath  Имя входящего файла.
     * @return   Контрольная сумма.
    */
    uint32_t
    CalcHexCrc(std::string inputfilePath);

    /// Тип контрольной суммы.
    enum CrcType {
        CRC_RAW    = 0,  ///< контрольная сумма для сырых данных, записываемых во флеш контроллера
        CRC_HEX      = 1, ///< контрольная сумма на весь hex файл
    };

private:
    const int32_t HEADER_LENGTH {256};              ///< Длина хедера ОС.
    const int32_t HEADER_CRC_START_BYTE {20};       ///< Номер байта старта контрольной суммы сырых данных в хедере ОС.
    const int32_t HEADER_HEX_CRC_START_BYTE {24};   ///< Номер байта старта контрольной суммы файла в хедере ОС.
    const int32_t HEADER_OS_START_START_BYTE {28};  ///< Номер байта старта адреса старта ОС в хедере ОС.
    const int32_t HEADER_OS_END_START_BYTE {32};    ///< Номер байта старта адреса конца ОС в хедере ОС.


    /// Тип данных информации из хедера ОС.
    struct DataInHeader {
        uint32_t data;                      ///< Значение.
        uint32_t lineNum;                   ///< Номер строки в файле, где значение хранится.
        uint32_t colInLine;                 ///< Номер столбца в строке, где значение хранится.
        uint32_t dataLength {4};            ///< Размер значения в байтах.
    };

    /// Информация из хедера ОС.
    struct HeaderInfo {
        DataInHeader OsStartAddress;        ///< Адрес начала ОС.
        DataInHeader OsEndAddress;          ///< Адрес конца ОС.
        DataInHeader RawCrc;                ///< Информация о контрольной сумме данных хекс файла.
        DataInHeader HexCrc;                ///< Информация о контрольной сумме файла..
        uint32_t dataLinelength {16};       ///< Длина одной строки данных хекс файла.
    };

    HeaderInfo m_header;
    HexHandler m_hexHandler;

    /*!
     @~russian
     * @brief Дополняет строку HEX файла значениями 0xFF для обеспечения отсутствия пробелов при записи во флеш.
     * @param   lastLine  Предыдущая строка, которая дополняется на основе данных новой строки.
     * @param   newLine Новая строка.
     * @param   newLineOffset Смещение адреса новой строки, если оно было отмечено при чтении команды номер 2.
     * @param   lastLineOffset  Смещение адреса старой строки, если оно было отмечено при чтении команды номер 2.
    */
    void
    FillLastLineWithFF(std::string& lastLine,
                       std::string& newLine,
                       uint32_t newLineOffset, uint32_t lastLineOffset);

    /*!
     @~russian
     * @brief Делает один шаг расчета контрольной суммы CRC32 для тех данных, что попадут во флеш, с учетом адреса конца прошивки.
     * @param   rawCrc  Предыдущее значение контрольной суммы.
     * @param   line Предыдущая строка, для которой считается контрольная сумма.
     * @param   lineOffset  Смещение адреса, если оно было отмечено при чтении хекс команды номер 2.
    */
    void
    CalcRawCrcForLine(uint32_t& rawCrc, std::string& line, uint32_t lineOffset);

    /*!
     @~russian
     * @brief Преобразует адрес в hex-строку длиной 4 символа.
     * @param   addr  Адрес.
     * @return   Адрес в виде hex-строки.
    */
    std::string
    AddrToHexString(uint32_t addr, uint32_t offset);
};

#endif // FIRMWAREFILEHANDLER_H
