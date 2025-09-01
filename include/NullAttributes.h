#ifndef CHINESECHESS_NULLATTRIBUTES_H
#define CHINESECHESS_NULLATTRIBUTES_H

#include "CoreType.h"
#include "PieceAttributes.h"
#include <optional>

class NullAttributes : public PieceAttributes {
  public:
    std::optional<int> get_attribute(AttributeType type) const override { return std::nullopt; }
    bool modify_attribute(AttriOpType op, AttributeType attri_type, int value) override { return false; }
    void remove_attribute(AttributeType type) override {}
};

#endif // CHINESECHESS_NULLATTRIBUTES_H