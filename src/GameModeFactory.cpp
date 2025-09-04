#include "GameMode/GameModeFactory.h"
#include "GameMode/StandardPveMode.h"

const std::map<GameOption, GameModeFactory::CreatorFunc> GameModeFactory::creators_{
    {GameOption::STANDARD_PvE, []() { return std::make_unique<StandardPveMode>(); }},
};

std::unique_ptr<GameMode> GameModeFactory::create_mode(GameOption op) {
    auto it = creators_.find(op);

    // 游戏模式工厂预期行为：传入非 EXIT 的游戏模式选项，成功创建实例，不应返回 nullptr
    // 不合法的枚举值：枚举值 EXIT、未初始化的随机枚举值、map 中漏写的映射逻辑
    // 程序预期行为是，用户选择 EXIT，直接退出游戏，不应该将枚举值 EXIT 传入该函数
    // 因此上述不合法的枚举值属于开发阶段的问题，使用 assert
    assert(it != creators_.end() &&
           "GameModeFactory:create_mode: 传入非法枚举值，如 "
           "EXIT、未初始化的随机枚举值。或者漏写某些游戏模式类型的创建逻辑");

    return it->second();
}