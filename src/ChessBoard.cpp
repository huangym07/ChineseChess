#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "Common/CoreType.h"
#include <cassert>
#include <iostream>

ChessBoard::ChessBoard(int width, int height,
                       const std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>> &pieces)
    : width_(width), height_(height), board_(height, std::vector<ChessPiece *>(width, nullptr)) {
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

void ChessBoard::show_board() const {
    for (int i = 0; i < height_; ++i) {
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
}