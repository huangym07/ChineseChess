#ifndef CHINESECHESS_CONCRETEATTRIBUTES_H
#define CHINESECHESS_CONCRETEATTRIBUTES_H

#include "CoreType.h"
#include "PieceAttributes.h"
#include <map>

class ConcreteAttributes : public PieceAttributes {
  private:
    std::map<AttributeType, int> attributes_;
  public:
    ConcreteAttributes(std::map<AttributeType, int> &&attributes);
    std::optional<int> get_attribute(AttributeType type) const override;
    bool modify_attribute(AttriOpType op, AttributeType attri_type, int value) override;
    void remove_attribute(AttributeType type) override;
};

#endif // CHINESECHESS_CONCRETEATTRIBUTES_H