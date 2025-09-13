#include "ChessPiece/Cannon.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"
#include <cassert>
#include <cstddef>

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
bool Cannon::special_check_move(Position target, const ChessBoard &board) const {
    auto piece = board.get_piece(target);

    int index_change = target[0] == pos_[0] ? 1 : 0;
    int index_same = (1 + index_change) % 2;

    int start = std::min(pos_[index_change], target[index_change]) + 1;
    int end = std::max(pos_[index_change], target[index_change]) - 1;

    Position pos_tmp;
    pos_tmp[index_same] = pos_[index_same];
    if (nullptr == piece) {
        for (int t = start; t <= end; ++t) {
            pos_tmp[index_change] = t;
            if (nullptr != board.get_piece(pos_tmp))
                return false;
        }
    } else {
        int count = 0;
        for (int t = start; t <= end; ++t) {
            pos_tmp[index_change] = t;
            count += nullptr != board.get_piece(pos_tmp);
        }

        if (1 != count)
            return false;
    }

    return true;
}