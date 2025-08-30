#ifndef CHINESECHESS_PIECEATTRIBUTES_H
#define CHINESECHESS_PIECEATTRIBUTES_H

#include "CoreType.h"
#include <optional>

class PieceAttributes {
  public:
    virtual std::optional<int> get_attribute(const AttributeType &type) const = 0;
    virtual bool modify_attribute(const AttriOpType &op, const AttributeType &attri_type, int value) = 0;
    virtual void remove_attribute(const AttributeType &type) = 0;

    virtual ~PieceAttributes() = default;
};

#endif // CHINESECHESS_PIECEATTRIBUTES_H