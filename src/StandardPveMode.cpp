#include "StandardPveMode.h"
#include "GameContext.h"
#include "InputHandler.h"
#include <iostream>
#include <cassert>

void StandardPveMode::start(GameContext &context) const {
    std::cout << "选择阵营: 1. 红方 2. 黑方 3. 随机分配\n";

    int op = InputHandler::read_int_range(1, 3);

    assert(false && "TODONEXT");
    if (3 == op) {
    }
}