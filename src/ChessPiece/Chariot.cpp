#include "ChessPiece/Chariot.h"
#include "ChessBoard.h"

// TODO
// Chariot::basic_moves_gen
// Chariot::basic_check_move
// 分别与 Cannon 对应函数完全相同
// 以后可以把基本移动规则类和特殊移动规则类抽象出来，
// 组合到 ChessPiece 中，用组合代替继承来得到各种棋子
// 暂时先冗余着
std::vector<Position> Chariot::basic_moves_gen(const ChessBoard &board) const {
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

bool Chariot::basic_check_move(Position target) const {
    if (target.x == pos_.x && target.y == pos_.y)
        return false;

    if (target.x != pos_.x && target.y != pos_.y)
        return false;

    return true;
}

// 自占判断在 special_move_check 之前
// 因此目标坐标要么为空，要么是敌方棋子，不会是己方其他棋子
// basic_move_check 在 special_move_check 之前
// 因此目标坐标与源坐标（当前位置）不重合且在同一条直线上
bool Chariot::special_check_move(Position target, const ChessBoard &board) const {
    int count = board.count_straight_obstacles_between(pos_, target);
    return 0 == count;
}