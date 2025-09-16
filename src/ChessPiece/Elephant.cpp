#include "ChessPiece/Elephant.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"
#include <vector>

std::vector<Position> Elephant::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;

    for (auto offset : basic_move_offsets) {
        ret.push_back({pos_ + offset});
    }

    return ret;
}

bool Elephant::basic_check_move(Position target) const {
    for (auto offset : basic_move_offsets) {
        if (target == pos_ + offset)
            return true;
    }
    return false;
}

bool Elephant::special_check_move(Position target, const ChessBoard &board) const {
    if (board.is_across_river(side_tag_, target))
        return false;

    Position center = (pos_ + target) / 2;
    if (nullptr != board.get_piece(center))
        return false;

    return true;
}