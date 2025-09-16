#include "ChessPiece/Elephant.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"
#include <vector>

std::vector<Position> Elephant::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;

    for (auto pos : basic_move_offsets) {
        ret.push_back({pos_.x + pos.x, pos_.y + pos.y});
    }

    return ret;
}

bool Elephant::basic_check_move(Position target) const {
    for (auto pos : basic_move_offsets) {
        if (target.x == pos.x + pos_.x && target.y == pos.y + pos_.y)
            return true;
    }
    return false;
}

bool Elephant::special_check_move(Position target, const ChessBoard &board) const {
    if (board.is_across_river(side_tag_, target))
        return false;

    Position center = {(pos_.x + target.x) / 2, (pos_.y + target.y) / 2};
    if (nullptr != board.get_piece(center))
        return false;

    return true;
}