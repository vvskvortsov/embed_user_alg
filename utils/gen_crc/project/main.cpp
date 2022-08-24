#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

#include <algorithm>
#include <cctype>

#include "crc.h"
#include "utils.h"



#include "FirmwareFileHandler.h"

using namespace std;

#define FILE_NAME "Basic_6kB_DIO_PDO.hex"
#define FILE_KBEG "Basic_4kB_EG.hex"
#define FILE_KBEG_CDS "codesys_4kb_eg.hex"
#define min(a,b) (a < b ? a : b)

//для отладки
#define MAKE_RENAME 1


enum crc_type {
    CRC_RAW    = 0,  ///< контрольная сумма для сырых данных, записываемых во флеш контроллера
    CRC_HEX      = 1, ///< контрольная сумма на весь hex файл
};

/*!
 * @~russian
 * @brief Утилита считает контрольные суммы файла ОС в соответствии с принятым заголовком и записывает их в файл.
 * Первым этапом происходит заполнение пустых участков между строк внутри файла символами 0xFF. Линкер может генерировать строки
 * с пробелами в адресах, мы должны исключить их, чтобы у нас точно сходилась то, что в файле с тем, что мы записываем во флеш.
 * Последняя строка также должна быть кратна 4 или мы ее дополняем, иначе также не сойдется запись по последнему адресу.
 * Вторым этапом считает контрольная сумма с учетом того, что попадет во флеш. То есть игнорируются символы hex файла такие как адрес,
 * команда и т.д. Контрольная сумма записывается в заголовок в файле в соответствии с принятым форматом (см. libos, bootloader драйвер).
 * Эта сумма проверяется бутлоадером во время запуска ОС.
 * Третьм этапом считается контрольная сумма на весь файл и записывается в заголовок в файле в соответствии с принятым форматом (см. libos,
 * bootloader драйвер). Эта сумма используется для проверки целостности файла.
 *
 * На входе первым аргументом принимаем файл для обработки, если его нет, используем определенное название.
 */
int main(int argc, char** argv)
{

    std::cout << "HEX crc utility started" << std::endl;

    std::string fileName;
    if (argc > 1) {
        fileName = std::string(argv[1]);
    }
    else {
        fileName = std::string(FILE_NAME); //для отладки
    }

    FirmwareFileHandler handler;
    handler.ParseHeader(fileName, "tmpFileWithEditedHeader.hex");
    handler.FillHexWithFF("tmpFileWithEditedHeader.hex", "tmpFileWithFF.hex");
    uint32_t rawCrc = handler.CalcRawCrc("tmpFileWithFF.hex");
    handler.WriteCrcToFile(rawCrc, FirmwareFileHandler::CRC_RAW, "tmpFileWithFF.hex", "tmpFileWithRawCrc.hex");
    uint32_t hexCrc = handler.CalcHexCrc("tmpFileWithRawCrc.hex");
    handler.WriteCrcToFile(hexCrc, FirmwareFileHandler::CRC_HEX, "tmpFileWithRawCrc.hex", "tmpFileFinal.hex");


    std::cout << "CRC of data(OS section without header): " << std::hex << rawCrc
              << std::endl;
    std::cout << "CRC of hex (whole .hex file          ): " << std::hex << hexCrc
              << std::endl;


    //если нужно удаляем все вспопогательные файлы и заменяем исходный файл
    //прошивки
    if (MAKE_RENAME) {
        const char* fn = fileName.c_str();
        std::remove(fn);
        std::remove("tmpFileWithEditedHeader.hex");
        std::remove("tmpFileWithFF.hex");
        std::remove("tmpFileWithRawCrc.hex");
        std::rename("tmpFileFinal.hex", fn);
    }

    cout << "Edited Hex is ready!" << endl;
    return 0;
}


