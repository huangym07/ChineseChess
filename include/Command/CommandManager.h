#ifndef CHINESECHESS_COMMAND_COMMANDMANAGER_H
#define CHINESECHESS_COMMAND_COMMANDMANAGER_H

#include "Command/Command.h"
#include <memory>
#include <vector>

class CommandManager {
  private:
    std::vector<std::unique_ptr<Command>> history_;

  public:
    void execute(std::unique_ptr<Command> &&command);
    void undo(int number);
};

#endif // CHINESECHESS_COMMAND_COMMANDMANAGER_H