#ifndef CHINESECHESS_CHESSBOARD_H
#define CHINESECHESS_CHESSBOARD_H

#include "Common/CoreType.h"
#include <map>
#include <memory>
#include <vector>

class ChessPiece;

class ChessBoard {
  private:
    int width_, height_;
    std::vector<std::vector<ChessPiece *>> board_;

  public:
    ChessBoard(int width, int height, const std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>> &pieces);

    // 返回棋盘的宽高
    std::pair<int, int> size() const { return std::make_pair(width_, height_); }

    bool set_piece(Position pos, ChessPiece *piece);
    ChessPiece *get_piece(Position pos) const;

    bool is_out_of_board(Position pos) const {
        return pos.x < 0 || pos.x >= width_ || pos.y < 0 || pos.y >= height_;
    }

    void show_board() const;
};

#endif // CHINESECHESS_CHESSBOARD_H