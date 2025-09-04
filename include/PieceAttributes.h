#ifndef CHINESECHESS_PIECEATTRIBUTES_H
#define CHINESECHESS_PIECEATTRIBUTES_H

#include "Common/CoreType.h"
#include <map>
#include <memory>
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

    static std::unique_ptr<PieceAttributes> create_default_instance() {
        return std::make_unique<PieceAttributes>(
            std::map<AttributeType, int>{{AttributeType::HP, 1},
                                         {AttributeType::PHYSICAL_ATK, 1},
                                         {AttributeType::PHYSICAL_DEF, 0},
                                         {AttributeType::MAGIC_ATK, 0},
                                         {AttributeType::MAGIC_DEF, 0},
                                         {AttributeType::SPEED, 1}});
    }
};

#endif // CHINESECHESS_PIECEATTRIBUTES_H