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

bool Horse::special_check_move(Position target, const ChessBoard &board) const {
    Position obstacle;
    if (2 == std::abs(pos_.x - target.x)) {
        obstacle.x = (pos_.x + target.x) / 2;
        obstacle.y = pos_.y;
    } else {
        obstacle.y = (pos_.y + target.y) / 2;
        obstacle.x = pos_.x;
    }
    return nullptr == board.get_piece(obstacle);
}