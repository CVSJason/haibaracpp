#include "haibara/source/sourcePosition.h"

namespace Haibara {

SourcePosition SourcePosition::range(SourcePosition &start, SourcePosition &end) {
    return SourcePosition(
        start.fileName,
        start.startByte,   end.endByte,
        start.startLine,   end.endLine,
        start.startColumn, end.endColumn
    );
}

bool SourcePosition::operator==(SourcePosition &other) {
    return fileName == other.fileName && startByte == other.startByte && endByte == other.endByte;
}

}