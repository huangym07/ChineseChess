#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "Common/CoreType.h"
#include <cassert>
#include <iostream>

ChessBoard::ChessBoard(int width, int height,
                       const std::vector<std::unique_ptr<ChessPiece>> &pieces)
    : width_(width), height_(height), board_(height, std::vector<ChessPiece *>(width, nullptr)) {
    for (const auto &uptr : pieces) {
        assert(nullptr != uptr && "棋盘构造时，不应传入空的棋子指针");

        Position pos = uptr->pos();
        if (is_out_of_board(pos)) {
            assert(false && "标准棋盘构造时有超出棋盘的棋子");

            std::cerr << "自定义的棋子位置超出自定义棋盘，游戏终止！请修正后重新打开游戏。\n";
            std::exit(EXIT_FAILURE);
        }

        board_[pos.y][pos.x] = uptr.get();
        pieces_[uptr->side_tag()].push_back(uptr.get());
    }
}

bool ChessBoard::set_piece(Position pos, ChessPiece *piece) {
    if (is_out_of_board(pos))
        return false;

    board_[pos.y][pos.x] = piece;

    return true;
}