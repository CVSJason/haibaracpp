#include "haibara/lexing/characterSource.h"

#include <iostream>

namespace Haibara {

char32_t FileCharacterSource::peek(size_t nth) {
    size_t targetPosition = currentByte;

    char32_t result = advance(targetPosition);

    for (int i = 0; i != nth; i++) {
        result = advance(targetPosition);
    }

    return result;
}

char32_t FileCharacterSource::read(size_t count) {
    char32_t result = char32_t(-1);

    for (int i = 0; i != count; i++) {
        result = advance(currentByte);

        if (result == '\n') {
            currentLine++;
            currentColumn = 0;
        } else {
            currentColumn++;
        }
    }

    return result;
}

SourcePosition FileCharacterSource::getPosition() {
    return SourcePosition(
        fileName,
        currentByte,   currentByte,
        currentLine,   currentLine,
        currentColumn, currentColumn
    );  
}

const char utf8MultiByteMask = 0b10000000;

char32_t FileCharacterSource::advance(size_t &position) {
    // 如果已经到了末尾...
    if (position == endByte) return char32_t(0);

    // 如果是单字节字符...
    if (!((u_char)fileContent[position] & utf8MultiByteMask)) {
        return (u_char)fileContent[position++];
    }

    // 有 2 个字节时...
    if (((u_char)fileContent[position] & 0b11100000) == 0b11000000 && position + 1 < endByte) {
        u_char firstByte  = (u_char)fileContent[position++];
        u_char secondByte = (u_char)fileContent[position++];

        return (char32_t(firstByte  & 0b00011111) << 6) | 
               (char32_t(secondByte & 0b00111111));
    }

    // 有 3 个字节时...
    if (((u_char)fileContent[position] & 0b11110000) == 0b11100000 && position + 2 < endByte) {
        u_char firstByte  = (u_char)fileContent[position++];
        u_char secondByte = (u_char)fileContent[position++];
        u_char thirdByte  = (u_char)fileContent[position++];

        return (char32_t(firstByte  & 0b00001111) << 12) | 
               (char32_t(secondByte & 0b00111111) << 6 ) |
               (char32_t(thirdByte  & 0b00111111) << 0 );
    }

    // 有 4 个字节时...
    if (((u_char)fileContent[position] & 0b11111000) == 0b11110000 && position + 3 < endByte) {
        u_char firstByte  = (u_char)fileContent[position++];
        u_char secondByte = (u_char)fileContent[position++];
        u_char thirdByte  = (u_char)fileContent[position++];
        u_char fourthByte = (u_char)fileContent[position++];

        return (char32_t(firstByte  & 0b00000111) << 18) | 
               (char32_t(secondByte & 0b00111111) << 12) |
               (char32_t(thirdByte  & 0b00111111) << 6 ) |
               (char32_t(fourthByte & 0b00111111) << 0 );
    }

    // 否则肯定有问题！
    position++;
    return char32_t(-1);
}

}