#include "Command/CommandManager.h"
#include "Command/Command.h"
#include <cassert>
#include <iostream>

void CommandManager::execute(std::unique_ptr<Command> &&command) {
    command->execute();
    history_.push_back(std::move(command));
}

void CommandManager::undo(int number) {
    assert(number > 0 && "当用户选择悔棋时，命令管理器中传入的撤销命令个数应 > 0，代码逻辑出错");

    if (number > history_.size()) {
        std::cout << "已回到最初状态，无法继续悔棋" << std::endl;
        return;
    }

    while (number) {
        history_.back()->undo();
        history_.pop_back();
        --number;
    }
}