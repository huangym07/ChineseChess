#include "ConcreteAttributes.h"
#include "CoreType.h"
#include <cassert>
#include <iostream>

ConcreteAttributes::ConcreteAttributes(std::map<AttributeType, int> &&attributes)
    : attributes_(std::move(attributes)) {}

std::optional<int> ConcreteAttributes::get_attribute(AttributeType type) const {
    auto it = attributes_.find(type);

    if (it == attributes_.end())
        return std::nullopt;

    return it->second;
}

bool ConcreteAttributes::modify_attribute(AttriOpType op, AttributeType attri_type, int value) {
    switch (op) {
    case AttriOpType::SET: {
        attributes_[attri_type] = value;
        break;
    }
    case AttriOpType::ADD: {
        auto it = attributes_.find(attri_type);
        if (it != attributes_.end())
            return false;
        attributes_[attri_type] = value;
        break;
    }
    case AttriOpType::CHANGE: {
        auto it = attributes_.find(attri_type);
        if (it == attributes_.end())
            return false;
        it->second += value;
        break;
    }
    default: {
        assert(false && "对属性值的未知操作");
        std::cerr << "对属性值出现未知操作，请联系开发者";
        return false;
    }
    }

    return true;
}

void ConcreteAttributes::remove_attribute(AttributeType type) { attributes_.erase(type); }
