#pragma once

#include "haibara/source/sourcePosition.h"

namespace Haibara {
/// 虚拟的字符来源。
class CharacterSource {
public:
    /// @brief 查看接下来的第 n 个字符，但是不更改读取位置。
    /// @param nth 要读取的字符的相对位置。
    /// @return 第 n 个字符的 Unicode 码点。EOF 用 0 表示。
    virtual char32_t peek(size_t nth = 0) = 0;
    
    /// @brief 读取若干个字符。
    /// @param count 读取字符的数量。
    /// @return 最后读取的字符。EOF 用 0 表示。
    virtual char32_t read(size_t count = 1) = 0;

    /// @brief 获取当前在源代码中的位置。
    /// @return 当前在源代码中的位置。
    virtual SourcePosition getPosition() = 0;
};

class FileCharacterSource: public CharacterSource {
    h_shared<std::string> fileName;
    std::string fileContent;

    size_t currentByte = 0,
           currentLine = 0,
           currentColumn = 0;

    /// @brief 内容字符串的长度。
    const size_t endByte;

public:
    FileCharacterSource(
        const std::string &fileName, 
        const std::string &fileContent
    ):
        fileName(std::make_shared<std::string>(fileName)),
        fileContent(fileContent),
        endByte(fileContent.size())
    { }

    char32_t peek(size_t nth = 0) override;
    char32_t read(size_t count = 1) override;
    SourcePosition getPosition() override;

private:
    /// @brief 尝试将 position 处的 utf-8 字符转换为 unicode 码点并移动 position。
    ///        失败时返回 char32_t(-1).
    /// @param position 内容字符串中的位置。
    /// @return 转换的 unicode 码点。失败时返回 char32_t(-1).
    char32_t advance(size_t &position);
};
}