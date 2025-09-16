#include "ChessPiece/General.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"

std::vector<Position> General::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;
    for (auto offset : basic_move_offsets) {
        ret.push_back(pos_ + offset);
    }
    return ret;
}

bool General::basic_check_move(Position target) const {
    // 曼哈顿距离为 1 -> 帅只能上下左右走一格（符合基本移动规则）
    return 1 == std::abs(pos_.x - target.x) + std::abs(pos_.y - target.y);
}

bool General::special_check_move(Position target, const ChessBoard &board) const {
    return !board.is_out_of_nine_palace(side_tag_, target);
}