#include "FirmwareFileHandler.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "utils.h"
#include "crc.h"
FirmwareFileHandler::FirmwareFileHandler()
{

}

int FirmwareFileHandler::ParseHeader(std::string inputfilePath, std::string outputfilePath)
{
    std::fstream inputFile;
    inputFile.open(inputfilePath);

    std::ofstream outputFile(outputfilePath);

    std::string line;
    uint32_t lineNum = 0;

    uint32_t headerStartLineNum {0};
    uint32_t headerEndLineNum {0};
    bool headerFound = false;

    while (std::getline(inputFile, line)) {
        uint32_t hexCmd = m_hexHandler.ParseCmdFromLine(line);

        if (HexHandler::CMD_DATA == hexCmd) {

            if (!headerFound) {
                headerStartLineNum = lineNum;
                headerFound = true;
                // ищем в какой строке со старта заголовка лежит необходимая информация
                uint64_t lineHexLength = m_hexHandler.ParseSizeFromLine(
                                             line); // длина данных в хекс строке
                m_header.dataLinelength = static_cast<uint32_t>(lineHexLength);

                if (HEADER_LENGTH % lineHexLength != 0) {
                    headerEndLineNum = HEADER_LENGTH / lineHexLength + 1 + headerStartLineNum;
                }
                else {
                    headerEndLineNum = HEADER_LENGTH / lineHexLength + headerStartLineNum;
                }

                headerEndLineNum--; //счет строк ведем с 0

                m_header.RawCrc.lineNum = HEADER_CRC_START_BYTE / lineHexLength +
                                          headerStartLineNum;
                m_header.RawCrc.colInLine = m_hexHandler.ConvertDataColToHexCol(
                                                HEADER_CRC_START_BYTE % lineHexLength);
                m_header.HexCrc.lineNum = HEADER_HEX_CRC_START_BYTE / lineHexLength +
                                          headerStartLineNum;
                m_header.HexCrc.colInLine = m_hexHandler.ConvertDataColToHexCol(
                                                HEADER_HEX_CRC_START_BYTE % lineHexLength);
                m_header.OsStartAddress.lineNum = HEADER_OS_START_START_BYTE / lineHexLength +
                                                  headerStartLineNum;
                m_header.OsStartAddress.colInLine = m_hexHandler.ConvertDataColToHexCol(
                                                        HEADER_OS_START_START_BYTE % lineHexLength);
                m_header.OsEndAddress.lineNum = HEADER_OS_END_START_BYTE / lineHexLength +
                                                headerStartLineNum;
                m_header.OsEndAddress.colInLine = m_hexHandler.ConvertDataColToHexCol(
                                                      HEADER_OS_END_START_BYTE % lineHexLength);

            }

            struct DataInHeader* ptrToData = nullptr;

            ptrToData = &m_header.OsStartAddress;

            if (ptrToData->lineNum == lineNum) {
                ptrToData->data = m_hexHandler.ParseDataFromLine(line.substr(
                                      ptrToData->colInLine, ptrToData->dataLength * 2));
            }

            ptrToData = &m_header.OsEndAddress;

            if (ptrToData->lineNum == lineNum) {
                ptrToData->data = m_hexHandler.ParseDataFromLine(line.substr(
                                      ptrToData->colInLine, ptrToData->dataLength * 2));
            }

            ptrToData = &m_header.RawCrc;
            if (lineNum == ptrToData->lineNum) {
                std::string crcStr = decToUpperHexString(0);
                swapHexString(crcStr, ptrToData->dataLength * 2);
                line.replace(ptrToData->colInLine, ptrToData->dataLength * 2, crcStr);
                m_hexHandler.FillLineWithFFToSize(line, m_hexHandler.ParseSizeFromLine(line));
            }
            ptrToData = &m_header.HexCrc;
            if (lineNum == ptrToData->lineNum) {
                std::string crcStr = decToUpperHexString(0);
                swapHexString(crcStr, ptrToData->dataLength * 2);
                line.replace(ptrToData->colInLine, ptrToData->dataLength * 2, crcStr);
                m_hexHandler.FillLineWithFFToSize(line, m_hexHandler.ParseSizeFromLine(line));
            }
        }

        lineNum++;
        outputFile << line << std::endl;
    };

    inputFile.close();
    outputFile.close();

    return 0;
}

int FirmwareFileHandler::FillHexWithFF(std::string inputfilePath,
                                       std::string outputfilePath)
{
    std::fstream inputFile;
    inputFile.open(inputfilePath);
    std::ofstream outputFile(outputfilePath);



    uint32_t addressOffset {0}; //смещение для определения адреса (в хексе адреса относительные у строк)

    std::ostringstream
    intermediateLines; //линии с командами, отлиными от 0, которые встречаются в файле и их необходимо просто перезаписать в файл далее
    //есть другие команды
    std::string newLine; //новая строка hex файла
    std::string lastLine; //предыдущая строка hex файла
    uint32_t newLineOffset =
        0; // смещение адреса в новой строке hex файла
    uint32_t lastLineOffset =
        0; // смещение адреса в старой строке hex файла

    for (std::string line; getline(inputFile, line);) {
        uint32_t hexCmd = m_hexHandler.ParseCmdFromLine(line);

        if (hexCmd == HexHandler::CMD_DATA) {
            newLine = line;
            newLineOffset = addressOffset;


            if (!lastLine.empty()) {
                FillLastLineWithFF(lastLine, newLine, newLineOffset,
                                   lastLineOffset);


                outputFile << lastLine << std::endl;

                //Учитываем возможные пустые строки между last_line и new_line
                uint32_t newLineAddr = m_hexHandler.ParseAddrFromLine(newLine) + newLineOffset;
                uint32_t lastLineAddr = m_hexHandler.ParseAddrFromLine(lastLine) +
                                        lastLineOffset;
                uint32_t lastLineSize = m_hexHandler.ParseSizeFromLine(
                                            lastLine);  //последнюю линию мы уже дополнили до максимального размера в функции FillLastLineWithFF


                //дополняем строки, если есть пробелы - между секциями мы ничего не добавляем, только в рамках ОС адресов
                if (lastLineAddr >= m_header.OsStartAddress.data
                    && lastLineAddr + lastLineSize <= m_header.OsEndAddress.data) {
                    uint32_t targetAddress = std::min(newLineAddr, m_header.OsEndAddress.data);
                    uint32_t lossBytesCount = targetAddress - (lastLineAddr + lastLineSize);


                    uint32_t intremediateAddress = lastLineAddr + lastLineSize;

                    while (lossBytesCount) {
                        uint32_t bytesToWrite = std::min(lossBytesCount,
                                                         m_header.dataLinelength); // в 1 строку
                        lossBytesCount -= bytesToWrite;
                        std::string newInterLine = ":";

                        std::string sizeStr = decToUpperHexString(bytesToWrite);
                        swapHexString(sizeStr, 2);

                        newInterLine.append(sizeStr);
                        newInterLine.append(AddrToHexString(intremediateAddress, addressOffset));
                        intremediateAddress += bytesToWrite;
                        newInterLine.append(2, '0');
                        newInterLine.append(static_cast<size_t>(bytesToWrite * 2 + 2), 'F'); //with crc
                        m_hexHandler.FillLineWithFFToSize(newInterLine, bytesToWrite);
                        outputFile << newInterLine << std::endl;
                    }
                }
            }

            if (!(intermediateLines.str().empty())) {
                outputFile << intermediateLines.str();
                intermediateLines.str(std::string());
            }

            lastLine = line;
            lastLineOffset = newLineOffset;

        }
        else if ( hexCmd == HexHandler::CMD_EXT_SEG_ADDR ) {
            int offset = m_hexHandler.ParseExtAddrFromLine(line);
            addressOffset = offset * 16;
            intermediateLines << line << std::endl;
        }
        else if (hexCmd == HexHandler::CMD_EXT_LINEAR_ADDR) {
            int offset = m_hexHandler.ParseExtAddrFromLine(line);
            addressOffset = (offset << 16);
            intermediateLines << line << std::endl;
        }
        else if (hexCmd == HexHandler::CMD_START_SEG_ADDR
                 || hexCmd == HexHandler::CMD_EOF
                 || hexCmd == HexHandler::CMD_START_LINEAR_ADDR) {
            intermediateLines << line << std::endl;
        }
    }

    //теперь дописываем последнюю строку и сбрасываем inremediate строки
    newLine = "";
    FillLastLineWithFF(lastLine, newLine, newLineOffset,
                       lastLineOffset);
    outputFile << lastLine << std::endl;

    //записываем команды, отличнгые от нуля, которые были зафиксированы в цикле, но не записаны в новый файл
    if (!(intermediateLines.str().empty())) {
        outputFile << intermediateLines.str();
        intermediateLines.str(std::string());
    }

    inputFile.close();
    outputFile.close();
    return 0;
}


void FirmwareFileHandler::FillLastLineWithFF(std::string& lastLine,
        std::string& newLine,
        uint32_t newLineOffset, uint32_t lastLineOffset)
{

    uint32_t lastLineSize = m_hexHandler.ParseSizeFromLine(lastLine);

    //если в последней строке не кратное 4м размер, то необходимо дополнить до него, иначе по последнему адресу во флеше будут расхождения с файлом
    //если строка последняя то проверяем последнюю строку. дополняем и выходим
    if (newLine.empty()) {
        if (lastLineSize % 4 != 0) {
            uint32_t newSize = lastLineSize / 4 * 4 + 4;
            m_hexHandler.FillLineWithFFToSize(lastLine, newSize);
            return;
        }
        else {
            return;
        }
    }

    uint32_t newLineAddr = m_hexHandler.ParseAddrFromLine(newLine) + newLineOffset;
    uint32_t lastLineAddr = m_hexHandler.ParseAddrFromLine(lastLine) +
                            lastLineOffset;

    //если строка не полная, значит будут пробелы при записи во флеш, необходимо дополнить строку
    if (lastLineAddr + lastLineSize <
        newLineAddr) { //если не полная строка

        uint32_t newSize = newLineAddr - lastLineAddr;

        if (newSize >
            m_header.dataLinelength) { //какой то большой пробел в связи с новой
            //секцией линкера (имеется в виду между ос и алгоримом) Проблем не вызовет, так как crc не будет считаться для других секций
            newSize = m_header.dataLinelength;
        }

        m_hexHandler.FillLineWithFFToSize(lastLine, newSize);
    }
}


uint32_t FirmwareFileHandler::CalcRawCrc(std::string inputfilePath)
{
    std::fstream inputFile;
    inputFile.open(inputfilePath);


    uint32_t rawCrc {0xFFFFFFFF};// crc только для прошивки, что будет записано во флеш
    uint32_t addressOffset {0}; //смещение для определения адреса (в хексе адреса относительные у строк)

    for (std::string line; getline(inputFile, line);) {
        uint32_t hexCmd = m_hexHandler.ParseCmdFromLine(line);

        if (hexCmd == HexHandler::CMD_DATA) {
            uint32_t lineAddr = m_hexHandler.ParseAddrFromLine(line) + addressOffset;
            uint32_t lineLength = m_hexHandler.ParseSizeFromLine(line);
            if (lineAddr + lineLength > m_header.OsStartAddress.data && lineAddr <= m_header.OsEndAddress.data) {
                CalcRawCrcForLine(rawCrc, line, addressOffset);
                uint32_t test = reverse(rawCrc);
                test = test ^ 0xFFFFFFFF;
                int x = 0;
            }
        }
        else if ( hexCmd == HexHandler::CMD_EXT_SEG_ADDR ) {
            int offset = m_hexHandler.ParseExtAddrFromLine(line);
            addressOffset = offset * 16;
        }
        else if (hexCmd == HexHandler::CMD_EXT_LINEAR_ADDR) {
            int offset = m_hexHandler.ParseExtAddrFromLine(line);
            addressOffset = (offset << 16);
        }
    }
    //считаем crc и закрываем файлы
    rawCrc = reverse(rawCrc);
    rawCrc = rawCrc ^ 0xFFFFFFFF;
    inputFile.close();
    return rawCrc;
}

void FirmwareFileHandler::CalcRawCrcForLine(uint32_t& rawCrc, std::string& line, uint32_t lineOffset)
{
    // addr
    uint32_t lineAddr = m_hexHandler.ParseAddrFromLine(line);
    lineAddr += lineOffset;

    int size = m_hexHandler.ParseSizeFromLine(line);

    //если ОС начинается не с начала строки, то высчитываем стартовый байт
    int startByte = 0;
    if (lineAddr < m_header.OsStartAddress.data) {
        startByte = m_header.OsStartAddress.data - lineAddr;
    }

    if (lineAddr + size >
        m_header.OsEndAddress.data) { //если адрес в в сумме с размером болше конечного, то необходимо сделать пересчет
        size = m_header.OsEndAddress.data - lineAddr;
    }

    //учитываем если стартовый байт не равен нулю
    size -= startByte;

    std::string rawStr = line.substr(HexHandler::DATA_OFFSET + startByte * 2,
                                     size * 2); //вытаскиваем только то, что попадет во флеш

    std::vector<uint8_t> bytes;
    for (int i = 0; i < size; i++) {
        bytes.push_back(static_cast<uint8_t>(m_hexHandler.ParseDataFromLine(rawStr.substr( i * 2, 2))));
    }

    rawCrc = calc_CRC_step(bytes, size, rawCrc); //считаем crc
}

void FirmwareFileHandler::WriteCrcToFile(uint32_t crc, uint32_t type, std::string inputfilePath,
                                            std::string outputfilePath) {
    std::fstream inputFile;
    inputFile.open(inputfilePath);
    std::ofstream outputFile(outputfilePath);

    struct DataInHeader* ptrToData = nullptr;

    if (type == CRC_RAW) {
        ptrToData = &m_header.RawCrc;
    } else {
        ptrToData = &m_header.HexCrc;
    }

    uint32_t lineNum = 0;
    for (std::string line; getline(inputFile, line);) {
        if (lineNum == ptrToData->lineNum) {
            std::string crcStr = decToUpperHexString(crc);
            swapHexString(crcStr, ptrToData->dataLength * 2);
            line.replace(ptrToData->colInLine, ptrToData->dataLength * 2, crcStr);
            m_hexHandler.FillLineWithFFToSize(line, m_hexHandler.ParseSizeFromLine(line));
        }

        lineNum++;
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();
}


uint32_t FirmwareFileHandler::CalcHexCrc(std::string inputfilePath)
{
    uint32_t hexCrc = 0xFFFFFFFF; // crc всего файла
    std::ifstream inputFile(inputfilePath, std::ios::binary);
    int x = inputFile.get();

    while (x != EOF) {
        std::vector<uint8_t> y;
        y.push_back(static_cast<uint8_t>(x));
        hexCrc = calc_CRC_step(y, 1, hexCrc);
        x = inputFile.get();
    }

    inputFile.close();
    hexCrc = reverse(hexCrc);
    hexCrc = hexCrc ^ 0xFFFFFFFF;
    return hexCrc;
}

std::string FirmwareFileHandler::AddrToHexString(uint32_t addr, uint32_t offset)
{
    std::string addrString = decToUpperHexString(addr - offset);
    uint32_t deltaLen = HexHandler::ADDR_LENGTH - addrString.length();

    if (deltaLen > 0)
        addrString.insert(0, deltaLen, '0');

    return addrString;
}
