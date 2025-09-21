#ifndef CHINESECHESS_COMMAND_SINGLECOMMAND_H
#define CHINESECHESS_COMMAND_SINGLECOMMAND_H

#include "Command/Command.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include <vector>

class ChessPiece;
class SingleCommand : Command {
  private:
    ChessPiece *attacker_piece_;
    Position target_pos_;
    GameContext &context_;
    std::vector<PieceSnapshot> piece_snaps_;
  public:
    SingleCommand(ChessPiece *attacker_piece, Position target_pos, GameContext &context) : attacker_piece_(attacker_piece), target_pos_(target_pos), context_(context) {}

    void execute() override;
    void undo() override;
};

#endif // CHINESECHESS_COMMAND_SINGLECOMMAND_H