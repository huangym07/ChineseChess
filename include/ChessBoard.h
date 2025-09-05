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
    std::map<SideTag, std::vector<ChessPiece *>> pieces_;
    std::vector<std::vector<ChessPiece *>> board_;

  public:
    ChessBoard(int width, int height, const std::vector<std::unique_ptr<ChessPiece>> &pieces);

    // TODO

    bool set_piece(Position pos, ChessPiece *piece);
    bool is_out_of_board(Position pos) const {
        return pos.x < 0 || pos.x >= width_ || pos.y < 0 || pos.y >= height_;
    }
};

#endif // CHINESECHESS_CHESSBOARD_H