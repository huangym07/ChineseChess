#include "ChessPiece/Horse.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"

std::vector<Position> Horse::basic_moves_gen(const ChessBoard &board) const {
    std::vector<Position> ret;

    for (auto offset : basic_move_offsets) {
        ret.push_back(Position{pos_ + offset});
    }

    return ret;
}

bool Horse::basic_check_move(Position target) const {
    int x_abs = std::abs(pos_.x - target.x);
    int y_abs = std::abs(pos_.y - target.y);
    return (2 == x_abs && 1 == y_abs) || (2 == y_abs && 1 == x_abs);
}

// 目标坐标相对于源坐标，在轴 1 上距离变化 1 格，在轴 2 上变化 2 格，
// 蹩马腿坐标相对于源坐标，在轴 1 和轴 2 上分别对应变化 0 格，1 格，
// 因此将目标坐标和源坐标相加，除以 2，就可以得到蹩马腿坐标。
// 例如 (x1, y1) -> (x1 - 2, y1 + 1)，蹩马腿坐标 (x1 - 1, y1)，
// 而 (x1 + x1 - 2) / 2 = x1 - 1，(y1 + y1 + 1) / 2 = y1（向下取整）
bool Horse::special_check_move(Position target, const ChessBoard &board) const {
    Position obstacle = (pos_ + target) / 2;
    return nullptr == board.get_piece(obstacle);
}