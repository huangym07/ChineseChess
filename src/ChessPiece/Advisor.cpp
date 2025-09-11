#include "ChessPiece/Advisor.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"

std::vector<Position> Advisor::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;

    for (int x = -1; x <= 1; x += 2) {
        for (int y = -1; y <= 1; y += 2) {
            ret.push_back(Position{pos_.x + x, pos_.y + y});
        }
    }

    return ret;
}

bool Advisor::basic_check_move(Position target) const {
    for (int x = -1; x <= 1; x += 2) {
        for (int y = -1; y <= 1; y += 2) {
            if (target.x == pos_.x + x && target.y == pos_.y + y) return true;
        }
    }

    return false;
}

bool Advisor::special_check_move(Position target, const ChessBoard &board) const {
    return !board.is_out_of_nine_palace(side_tag_, target);
}