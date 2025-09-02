#ifndef CHINESECHESS_PIECEATTRIBUTES_PIECEATTRIBUTES_H
#define CHINESECHESS_PIECEATTRIBUTES_PIECEATTRIBUTES_H

#include "Common/CoreType.h"
#include <optional>

class PieceAttributes {
  public:
    virtual std::optional<int> get_attribute(AttributeType type) const = 0;
    virtual bool modify_attribute(AttriOpType op, AttributeType attri_type, int value) = 0;
    virtual void remove_attribute(AttributeType type) = 0;

    virtual ~PieceAttributes() = default;
};

#endif // CHINESECHESS_PIECEATTRIBUTES_PIECEATTRIBUTES_H