#include "ChessPiece/Advisor.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"

std::vector<Position> Advisor::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;

    for (auto offset : basic_move_offsets) {
        ret.push_back(Position{pos_.x + offset.x, pos_.y + offset.y});
    }

    return ret;
}

bool Advisor::basic_check_move(Position target) const {
    for (auto offset : basic_move_offsets) {
        if (target.x == pos_.x + offset.x && target.y == pos_.y + offset.y)
            return true;
    }

    return false;
}

bool Advisor::special_check_move(Position target, const ChessBoard &board) const {
    return !board.is_out_of_nine_palace(side_tag_, target);
}