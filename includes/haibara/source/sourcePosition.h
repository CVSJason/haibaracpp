#pragma once

#include "haibara/common.h"

#include <string>

namespace Haibara {
/// @brief 表示源文件中的一个位置。
class SourcePosition {
    h_shared<std::string> fileName;

    size_t startByte,   endByte,
           startLine,   endLine,
           startColumn, endColumn;

public:
    /// @brief 使用数据直接构建 SourcePosition.
    SourcePosition(
        h_shared<std::string> fileName,
        size_t startByte,
        size_t endByte,
        size_t startLine,
        size_t endLine,
        size_t startColumn,
        size_t endColumn
    ): 
        fileName(fileName),
        startByte(startByte),
        endByte(endByte),
        startLine(startLine),
        endLine(endLine),
        startColumn(startColumn),
        endColumn(endColumn) 
    { }

    /// @brief 使用两个 SourcePosition 构建一个新的区间。不会检查文件名是否相同。
    /// @param start 区间的起始点。
    /// @param end   区间的结束点。
    static SourcePosition range(SourcePosition &start, SourcePosition &end);

    bool operator==(SourcePosition &other);
};

}