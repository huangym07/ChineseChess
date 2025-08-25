#include "GameModeFactory.h"
#include "StandardPveMode.h"

const std::map<GameOption, std::function<std::unique_ptr<GameMode>()>> GameModeFactory::creators_{
    {GameOption::STANDARD_PvE, []() { return std::make_unique<StandardPveMode>(); }},
};

std::unique_ptr<GameMode> GameModeFactory::create_mode(GameOption op) {
    auto creator = creators_.find(op);

    if (creators_.end() == creator) {
        return nullptr;
    }

    return creator->second();
}