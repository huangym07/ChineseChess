#include "ChessPiece/Cannon.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"
#include <cassert>

std::vector<Position> Cannon::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;

    auto [width, height] = board.board_size();

    for (int x = 0; x < width; ++x) {
        if (pos_.x == x)
            continue;
        ret.push_back({x, pos_.y});
    }
    for (int y = 0; y < height; ++y) {
        if (pos_.y == y)
            continue;
        ret.push_back({pos_.x, y});
    }

    return ret;
}

bool Cannon::basic_check_move(Position target) const {
    if (target == pos_)
        return false;

    if (target.x != pos_.x && target.y != pos_.y)
        return false;

    return true;
}

// 自占判断在 special_move_check 之前
// 因此目标坐标要么为空，要么是敌方棋子，不会是己方其他棋子
// basic_move_check 在 special_move_check 之前
// 因此目标坐标与源坐标（当前位置）不重合且在同一条直线上
bool Cannon::special_check_move(Position target, const ChessBoard &board) const {
    int count = board.count_straight_obstacles_between(pos_, target);
    return nullptr == board.get_piece(target) ? (0 == count) : (1 == count);
}