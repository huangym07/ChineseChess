#ifndef CHINESECHESS_PIECEATTRIBUTES_H
#define CHINESECHESS_PIECEATTRIBUTES_H

#include "Common/CoreType.h"
#include <map>
#include <optional>

class PieceAttributes {
  private:
    std::map<AttributeType, int> attributes_;

  public:
    PieceAttributes(std::map<AttributeType, int> attributes);
    std::optional<int> get_attribute(AttributeType type) const;
    bool modify_attribute(AttriOpType op, AttributeType attri_type, int value);
    void remove_attribute(AttributeType type);

    ~PieceAttributes() = default;
};

#endif // CHINESECHESS_PIECEATTRIBUTES_H