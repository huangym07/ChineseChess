#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "Common/CoreType.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

void ChessBoard::calculate_range() {
    assert(width_ >= 3 && height_ >= 2 && "棋盘过小不允许存在九宫和楚河汉界");

    // 楚河汉界
    red_river_ = (height_ - 1) / 2;
    black_river_ = height_ % 2 ? red_river_ : red_river_ + 1;

    // 九宫的 (x, y) 坐标
    // 九宫 x 范围占据棋盘的 1/3
    // 棋盘 x 范围可被 3 整除时，九宫、九宫两侧三等分
    // 棋盘 x 范围被 3 除余 1 时，九宫左侧 x 范围 = 九宫 x 范围 = 九宫右侧 x 范围 - 1
    // 棋盘 x 范围被 3 除余 2 时，九宫左侧 x 范围 - 1 = 九宫 x 范围 = 九宫右侧 x 范围 - 1
    // 如 (棋盘 x 范围 -> 九宫 x 范围) [0, 8] -> [3, 5], [0, 9] -> [3, 5], [0, 10] -> [4, 6]
    // 九宫 y 范围占据阵营 y (红方->[0, red_rive], 黑方->[black_river_, black_river_]) 的 1/2
    // 阵营 y 不能被 2 整除时，九宫 y 范围占据更多一格的那一半
    // 如 (阵营 y -> 九宫 y) [0, 4] -> [0, 2], [0, 5] -> [0, 2], [0, 6] -> [0, 3]

    // nine palace x range
    int x_range = width_ / 3;
    // nine palace y range
    // red_river_ - 0 + 1 是阵营长度
    // (red_river_ - 0 + 1) + (2 - 1) 是为了利用整数除法自动向上取整
    // 最终 (red_river_ + 2) / 2
    int y_range = (red_river_ + 2) / 2;

    // nine palace left x
    int lx = width_ % 3 == 2 ? x_range + 1 : x_range;
    // nine palace right x
    int rx = lx + x_range - 1;

    red_nine_palace_ = std::make_pair(Position{lx, 0}, Position{rx, y_range - 1});
    black_nine_palace_ =
        std::make_pair(Position{lx, height_ - 1 - y_range + 1}, Position{rx, height_ - 1});
}

ChessBoard::ChessBoard(int width, int height,
                       const std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>> &pieces)
    : width_(width), height_(height), board_(height, std::vector<ChessPiece *>(width, nullptr)) {

    if (!width || !height) {
        std::cerr << "棋盘宽或者高不能为零，游戏终止，请修正棋盘宽高后重启游戏\n";
        std::exit(EXIT_FAILURE);
    }

    // 当棋盘 [x, y] 分别不小于 [2, 3] 时，九宫和楚河汉界才允许存在
    if (height_ >= 2 && width_ >= 3)
        calculate_range();

    for (const auto &side_pieces : pieces) {
        for (const auto &uptr : side_pieces.second) {
            assert(nullptr != uptr && "棋盘构造时，不应传入空的棋子指针");

            Position pos = uptr->pos();
            if (is_out_of_board(pos)) {
                assert(false && "标准棋盘构造时有超出棋盘的棋子");

                std::cerr << "自定义的棋子位置超出自定义棋盘，游戏终止！请修正后重新打开游戏。\n";
                std::exit(EXIT_FAILURE);
            }

            board_[pos.y][pos.x] = uptr.get();
        }
    }
}

bool ChessBoard::set_piece(Position pos, ChessPiece *piece) {
    if (is_out_of_board(pos))
        return false;

    board_[pos.y][pos.x] = piece;

    return true;
}

ChessPiece *ChessBoard::get_piece(Position pos) const {
    return is_out_of_board(pos) ? nullptr : board_[pos.y][pos.x];
}

bool ChessBoard::is_out_of_nine_palace(SideTag side_tag, Position pos) const {
    switch (side_tag) {
    case SideTag::RED: {
        return pos.x > red_nine_palace_.second.x || pos.x < red_nine_palace_.first.x ||
               pos.y < red_nine_palace_.first.y || pos.y > red_nine_palace_.second.y;
    }
    case SideTag::BLACK: {
        return pos.x > black_nine_palace_.second.x || pos.x < black_nine_palace_.first.x ||
               pos.y < black_nine_palace_.first.y || pos.y > black_nine_palace_.second.y;
    }
    default:
        assert(false && "传入未初始化的未知阵营枚举值");
    }
}
bool ChessBoard::is_across_river(SideTag side_tag, Position pos) const {
    switch (side_tag) {
    case SideTag::RED: {
        return pos.y > red_river_;
    }
    case SideTag::BLACK: {
        return pos.y < black_river_;
    }
    default:
        assert(false && "传入未初始化的未知阵营枚举值");
    }
}

void ChessBoard::show_board() const {
    std::cout << '\n';

    // 打印 x 轴
    std::cout << "  ";
    for (int j = 0; j < width_; ++j) {
        std::cout << " " << j << "  ";
    }
    std::cout << '\n';

    for (int i = 0; i < height_; ++i) {
        // 打印 y 轴
        std::cout << i << " ";

        for (int j = 0; j < width_; ++j) {
            std::cout << (nullptr == board_[i][j] ? AnsiColor::colored_text(AnsiColor::RED, "  ")
                                                  : board_[i][j]->display_info())
                      << "  ";
        }
        std::cout << "\n\n";
        if ((height_ - 1) / 2 == i) {
            // （(2 * width_ - 1) * 2 - 8) / 2 是楚河汉界居中且两侧空格数均等时，其左侧的空格数
            std::cout << std::string(((2 * width_ - 1) * 2 - 8) / 2, ' ') << "楚河汉界\n\n";
        }
    }
    std::cout << '\n' << std::endl;
}

int ChessBoard::count_straight_obstacles_between(Position start, Position end) const {
#ifndef NDEBUG
    if (start.x != end.x && start.y != end.y) 
        std::cerr << __PRETTY_FUNCTION__ << ": " << start << " -> " << end << std::endl;
#endif
    assert((start.x == end.x || start.y == end.y) && "检测直线上两点间（不含两点本身）的障碍物个数，传入参数应确保在一条直线上");

    int count = 0;

    if (start.x == end.x) {
        int y_start = std::min(start.y, end.y);
        int y_end = std::max(start.y, end.y);
        for (int y_current = y_start + 1; y_current < y_end; ++y_current) {
            count += nullptr != get_piece({start.x, y_current});
        }
    } else {
        int x_start = std::min(start.x, end.x);
        int x_end = std::max(start.x, end.x);
        for (int x_current = x_start + 1; x_current < x_end; ++x_current) {
            count += nullptr != get_piece({x_current, start.y});
        }
    }

    return count;
}