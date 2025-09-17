#include "ChessPiece/Soldier.h"
#include "Common/CoreType.h"
#include "ChessBoard.h"

std::vector<Position> Soldier::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;

    // 棋盘红上黑下
    ret.push_back({pos_.x, pos_.y + (SideTag::RED == side_tag_ ? +1 : -1)});
    ret.push_back(pos_ + Position{-1, 0});
    ret.push_back(pos_ + Position{+1, 0});

    return ret;
}

bool Soldier::basic_check_move(Position target) const {
    int x_abs = std::abs(pos_.x - target.x);
    int y_diff = target.y - pos_.y;

    // 棋盘红上黑下
    return (1 == x_abs && 0 == y_diff) || (0 == x_abs && (SideTag::RED == side_tag_ ? 1 == y_diff : -1 == y_diff));
}

// 在 special_check_move 前，进行了自占判断以及 basic_check_move，
// 当 x 坐标的绝对差为 0 时，一定是前进；不为 0 时，一定为 1，一定是左右移动一格
bool Soldier::special_check_move(Position target, const ChessBoard &board) const {
    int x_abs = std::abs(pos_.x - target.x);
    return 0 == x_abs || board.is_across_river(side_tag_, pos_);
}