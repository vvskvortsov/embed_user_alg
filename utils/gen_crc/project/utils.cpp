
#include "utils.h"

#include <sstream>
#include <iostream>

#include <algorithm>
uint8_t reverse(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

uint32_t reverse(uint32_t b) {
    uint8_t x1 = reverse (uint8_t(b & 0x000000FF));
    uint8_t x2 = reverse (uint8_t((b & 0x0000FF00)>>8));
    uint8_t x3 = reverse (uint8_t((b & 0x00FF0000)>>16));
    uint8_t x4 = reverse (uint8_t((b & 0xFF000000)>>24));
    return uint32_t(x1 << 24 | x2 << 16 | x3 << 8 | x4);
}


uint32_t  parseValueFromHexString(std::string input) {
    std::stringstream strStream;
    uint32_t output = 0;
    strStream << input;
    strStream >> std::hex >> output;
    return output;
}


std::string decToUpperHexString(int dec)
{
    std::stringstream ss;
    ss << std::hex << dec;
    std::string xx = ss.str();

    std::transform(xx.begin(), xx.end(), xx.begin(),
                   [](unsigned char c){ return std::toupper(c); });;
    return xx;
}


int swapHexString(std::string &xx, uint32_t size) {
    if (size < 2 || size % 2 != 0)
        return 1;
    uint8_t add_chars = size - uint8_t(xx.length());
    xx = std::string( add_chars, '0').append(xx);
    for(int i = 0; i < size/2; i+=2) {
        std::swap(xx[i],xx[size - 2 - i]);
        std::swap(xx[i+1],xx[size -1 - i]);
    }
    return 0;
}
