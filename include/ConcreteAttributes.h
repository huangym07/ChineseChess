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
    std::optional<int> get_attribute(const AttributeType &type) const;
    bool modify_attribute(const AttriOpType &op, const AttributeType &attri_type, int value);
    void remove_attribute(const AttributeType &type);
};

#endif // CHINESECHESS_CONCRETEATTRIBUTES_H