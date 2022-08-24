#include "HexHandler.h"
#include <sstream>
#include "utils.h"
HexHandler::HexHandler()
{

}

uint32_t HexHandler::ParseCmdFromLine(std::string &line)
{
    return ConvertHexStringToInt(line.substr(CMD_OFFSET,CMD_LENGTH));
}

uint32_t HexHandler::ParseSizeFromLine(std::string &line)
{
    return ConvertHexStringToInt(line.substr(SIZE_OFFSET,SIZE_LENGTH));
}

uint32_t HexHandler::ParseAddrFromLine(std::string &line)
{
    return ConvertHexStringToInt(line.substr(ADDR_OFFSET, ADDR_LENGTH));
}

uint32_t HexHandler::ParseExtAddrFromLine(std::string &line)
{
    return ConvertHexStringToInt(line.substr(EXT_ADDR_OFFSET, EXT_ADDR_LENGTH));
}

uint32_t HexHandler::ParseDataFromLine(std::string &&line)
{
    std::string inputString = line;
    return ParseDataFromLine(inputString);
}

uint32_t HexHandler::ParseDataFromLine(std::string &line)
{
    swapHexString(line, line.length());
    return ConvertHexStringToInt(line);
}


uint32_t HexHandler::ConvertHexStringToInt(const std::string &&input) {
    std::string inputString = input;
    return ConvertHexStringToInt(inputString);
}

uint32_t HexHandler::ConvertHexStringToInt(std::string &input) {
    std::stringstream strStream;
    uint32_t output = 0;
    strStream << input;
    strStream >> std::hex >> output;
    return output;
}


uint32_t HexHandler::ConvertDataColToHexCol(uint32_t dataCol) {
    return DATA_OFFSET + dataCol * 2;
}


void HexHandler::FillLineWithFFToSize(std::string &line, uint32_t size)
{
    uint32_t lineSize = ParseSizeFromLine(line);

    uint32_t diffSize = size - lineSize;

    std::string sizeStr = decToUpperHexString(size);
    swapHexString(sizeStr, 2);
    line.replace(SIZE_OFFSET, SIZE_LENGTH, sizeStr);


    uint8_t carriageOffset = 0; // проверяем наличие знака каретки в строке
    if(line[line.size() > 0 ? line.size() - 1 : 0] == '\r')
        carriageOffset = 1;

    line.replace(line.size()- 2 - carriageOffset, 2 + carriageOffset, ""); //удаляем старую crc hex

    for (int i = 0; i < diffSize; i++)
        line.append("FF"); // дополняем строку FF на сколько нужно

    line.append("XX"); // добавляем новую hex crc
    CalcAndWriteHexCRCforLine(line); //пересчитываем hex crc
}




void HexHandler::CalcAndWriteHexCRCforLine(std::string &line)
{
    int size = ParseSizeFromLine(line);

    int sum = 0;
    for(int i= 1; i < 8 + size * 2; i+=2) { //: игнорируется при подсчете контрольной суммы
        std::string l = line.substr (i, 2);
        int k = ParseDataFromLine(l);
        sum += k;
    }
    sum = sum & 0xFF;
    uint8_t crc = uint8_t(sum);
    crc *= -1;

    std::string crcStr = decToUpperHexString(int(crc));

    if (crcStr.size() == 1)
        crcStr = "0" + crcStr;

    line.replace(DATA_OFFSET + 2 * size, 2, crcStr);
}


