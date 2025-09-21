#include "Command/SingleCommand.h"

void SingleCommand::execute() {
    piece_snaps_ = attacker_piece_->move_attack(*context_.board, target_pos_);
}

void SingleCommand::undo() {
    attacker_piece_->undo_attack_move(*context_.board, piece_snaps_);
}