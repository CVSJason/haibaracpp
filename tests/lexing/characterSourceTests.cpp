#include <cstddef>
#include <string>

#include <gtest/gtest.h>

#include "haibara/lexing/characterSource.h"

TEST(CharacterSource, ASCIICharacters) {
    std::string content = "Hello, world!";

    Haibara::FileCharacterSource source(
        "test", content
    );

    for (size_t i = 0, size = content.size(); i != size; i++) {
        EXPECT_EQ(source.read(), content[i]) << "content differs at offset " << i;
    }

    EXPECT_EQ(source.read(), char32_t(0)) << "eof not match";
}  

TEST(CharacterSource, UnicodeCharacters) {
    // 你好
    const unsigned char cContent[] = { 0xe4, 0xbd, 0xa0, 0xe5, 0xa5, 0xbd, 0 };
    std::string content((const char *)cContent);

    char32_t result[] = { 20320, 22909 };

    Haibara::FileCharacterSource source(
        "test", content
    );

    for (size_t i = 0; i != 2; i++) {
        EXPECT_EQ(source.read(), result[i]) << "content differs at offset " << i;
    }

    EXPECT_EQ(source.read(), char32_t(0)) << "eof not match";
}  