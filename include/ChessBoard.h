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
    int red_river, black_river;
    std::pair<Position, Position> red_nine_palace, black_nine_palace; // [左上角, 右下角]
    std::vector<std::vector<ChessPiece *>> board_;

  private:
    void calculate_range();

  public:
    ChessBoard(int width, int height, const std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>> &pieces);

    // 返回棋盘的宽高
    std::pair<int, int> board_size() const { return std::make_pair(width_, height_); }

    bool set_piece(Position pos, ChessPiece *piece);
    ChessPiece *get_piece(Position pos) const;

    bool is_out_of_board(Position pos) const {
        return pos.x < 0 || pos.x >= width_ || pos.y < 0 || pos.y >= height_;
    }
    bool is_out_of_nine_palace(SideTag side_tag, Position pos) const;
    bool is_across_river(SideTag side_tag, Position pos) const;

    // 检测一条直线上的两点间（不含两点）的障碍物个数，
    // 应确保传入的两点在一条直线上
    int count_straight_obstacles_between(Position start, Position end) const;

    void show_board() const;
};

#endif // CHINESECHESS_CHESSBOARD_H