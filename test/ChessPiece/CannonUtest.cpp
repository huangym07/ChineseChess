#include "ChessBoard.h"
#include "ChessPiece/Cannon.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "TestFramework.h"

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

TEST_CASE(basic_moves_gen) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Cannon cannon{SideTag::RED, Position{1, 2}};

    auto moves = cannon.basic_moves_gen(board);

    ASSERT_EQ(moves.size(), 10 - 1 + 9 - 1, "炮的符合基本移动规则的目标坐标应有 17 个");

    int x_same_count = 0, y_same_count = 0;
    auto pos = cannon.pos();
    for (auto move : moves) {
        ASSERT_FALSE(move.x == pos.x && move.y == pos.y,
                     "炮符合基本移动规则的目标坐标不应与自身所在位置重合");
        ASSERT_TRUE(move.x == pos.x || move.y == pos.y,
                    "炮符合基本移动规则的目标坐标应与自身所在位置在同一条直线上");
        x_same_count += move.x == pos.x;
        y_same_count += move.y == pos.y;
    }

    ASSERT_EQ(x_same_count, 10 - 1, "炮符合基本移动规则的目标坐标在竖直直线上应有 9 个");
    ASSERT_EQ(y_same_count, 9 - 1, "炮符合基本移动规则的目标坐标在水平直线上应有 8 个");
}

TEST_CASE(basic_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Cannon cannon{SideTag::RED, Position{1, 2}};

    ASSERT_TRUE(cannon.basic_check_move({5, 2}), "(1, 2) -> (5, 2) 符合基本移动规则");
    ASSERT_TRUE(cannon.basic_check_move({1, 5}), "(1, 2) -> (1, 5) 符合基本移动规则");

    ASSERT_FALSE(cannon.basic_check_move({1, 2}), "(1, 2) -> (1, 2) 不符合基本移动规则");
    ASSERT_FALSE(cannon.basic_check_move({2, 3}), "(1, 2) -> (2, 3) 不符合基本移动规则");
}

TEST_CASE(special_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Cannon cannon{SideTag::RED, Position{1, 2}};

    // 不吃子
    ASSERT_TRUE(cannon.special_check_move({1, 8}, board),
                "(1, 2) -> (1, 8)，在 (1, 8) 处无棋子时，路径中间没有棋子，符合特殊移动规则");

    Cannon obstacle{SideTag::BLACK, {1, 7}};
    board.set_piece(obstacle.pos(), &obstacle);
    ASSERT_FALSE(cannon.special_check_move({1, 8}, board),
                 "(1, 2) -> (1, 8)，在 (1, 8) 处无棋子时，路径中间有棋子，不符合特殊移动规则");

    // 吃子
    Cannon target{SideTag::BLACK, {1, 8}};
    board.set_piece(target.pos(), &target);

    ASSERT_TRUE(
        cannon.special_check_move(target.pos(), board),
        "(1, 2) -> (1, 8)，在 (1, 8) 处有敌方棋子时，路径中间有且仅有一个棋子，符合特殊移动规则");

    board.set_piece(obstacle.pos(), nullptr);
    ASSERT_FALSE(cannon.special_check_move(target.pos(), board),
                 "(1, 2) -> (1, 8)，在 (1, 8) "
                 "处有敌方棋子时，路径中间并非有且仅有一个棋子，不符合特殊移动规则");
}

TEST_MAIN(RUN_TEST(basic_moves_gen); RUN_TEST(basic_check_move); RUN_TEST(special_check_move);)