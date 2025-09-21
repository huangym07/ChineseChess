#ifndef CHINESECHESS_COMMAND_COMMAND_H
#define CHINESECHESS_COMMAND_COMMAND_H

// interface
class Command {
  public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

#endif // CHINESECHESS_COMMAND_COMMAND_H