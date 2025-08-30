#ifndef CHINESECHESS_NULLATTRIBUTES_H
#define CHINESECHESS_NULLATTRIBUTES_H

#include "CoreType.h"
#include "PieceAttributes.h"
#include <optional>

class NullAttributes : public PieceAttributes {
  public:
    std::optional<int> get_attribute(const AttributeType &type) const { return std::nullopt; }
    bool modify_attribute(const AttriOpType &op, const AttributeType &attri_type, int value) { return false; }
    void remove_attribute(const AttributeType &type) {}
};

#endif // CHINESECHESS_NULLATTRIBUTES_H