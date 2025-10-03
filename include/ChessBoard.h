#ifndef CHINESECHESS_CHESSBOARD_H
#define CHINESECHESS_CHESSBOARD_H

#include "Common/CoreType.h"
#include <map>
#include <memory>
#include <vector>

class ChessPiece;

class ChessBoard {
  private:
    int width_, height_; // 棋盘宽高
    int red_river_, black_river_; // 楚河汉界位置
    std::pair<Position, Position> red_nine_palace_, black_nine_palace_; // 九宫位置，[左上角, 右下角]
    std::vector<std::vector<ChessPiece *>> board_; // 棋盘数据

  private:
    /*
        辅助函数，自适应楚河汉界、九宫位置
        功能：根据棋盘宽高计算楚河汉界、九宫的位置
    */
    void calculate_range();

  public:
    ChessBoard(int width, int height, const std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>> &pieces);

    /*
        获取棋盘大小
        功能：获取棋盘宽高
    */
    std::pair<int, int> board_size() const { return std::make_pair(width_, height_); }

    /*
        设置棋子指针
        功能：在指定位置 pos 处设置棋子指针
    */
    bool set_piece(Position pos, ChessPiece *piece);
    /*
        获取棋子指针
        功能：获取指定位置 pos 处的棋子指针
    */
    ChessPiece *get_piece(Position pos) const;

    /*
        棋盘出界检测
        功能：判断指定位置 pos 是否出界
        返回值：true 出界，false 未出界
    */
    bool is_out_of_board(Position pos) const {
        return pos.x < 0 || pos.x >= width_ || pos.y < 0 || pos.y >= height_;
    }
    /*
        九宫出界检测
        功能：检测指定位置 pos 是否在指定阵营 side_tag 的九宫外
        返回值：true 出九宫，false 未出九宫
    */
    bool is_out_of_nine_palace(SideTag side_tag, Position pos) const;
    /*
        楚河汉界出界检测
        功能：检测指定位置 pos 是否跨越指定阵营 side_tag 一侧的楚河汉界
        返回值：true 跨过河界，false 未跨过河界
    */
    bool is_across_river(SideTag side_tag, Position pos) const;

    /*
        （水平/竖直）线段上的障碍物计数
        功能：统计指定两个位置连成的（水平/竖直）线段上的障碍物个数（不含线段两个端点）
        参数约束：start，end 应确保在水平/竖直直线上
    */
    int count_straight_obstacles_between(Position start, Position end) const;

    /*
        展示棋盘（以及在棋盘上的棋子）
        功能：向标准输出流打印棋盘（以及棋盘上的棋子）
    */
    void show_board() const;
};

#endif // CHINESECHESS_CHESSBOARD_H