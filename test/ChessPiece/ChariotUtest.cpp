#include "ChessBoard.h"
#include "ChessPiece/Chariot.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "TestFramework.h"

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

TEST_CASE(basic_moves_gen) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Chariot chariot{SideTag::RED, Position{0, 1}};

    auto moves = chariot.basic_moves_gen(board);

    ASSERT_EQ(moves.size(), 10 - 1 + 9 - 1, "车的符合基本移动规则的目标坐标应有 17 个");

    int x_same_count = 0, y_same_count = 0;
    auto pos = chariot.pos();
    for (auto move : moves) {
        ASSERT_FALSE(move == pos,
                     "车符合基本移动规则的目标坐标不应与自身所在位置重合");
        ASSERT_TRUE(move.x == pos.x || move.y == pos.y,
                    "车符合基本移动规则的目标坐标应与自身所在位置在同一条直线上");
        x_same_count += move.x == pos.x;
        y_same_count += move.y == pos.y;
    }

    ASSERT_EQ(x_same_count, 10 - 1, "车符合基本移动规则的目标坐标在竖直直线上应有 9 个");
    ASSERT_EQ(y_same_count, 9 - 1, "车符合基本移动规则的目标坐标在水平直线上应有 8 个");
}

TEST_CASE(basic_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Chariot chariot{SideTag::RED, Position{0, 1}};

    ASSERT_TRUE(chariot.basic_check_move({0, 6}), "(0, 1) -> (0, 6) 符合基本移动规则");
    ASSERT_TRUE(chariot.basic_check_move({8, 1}), "(0, 1) -> (8, 1) 符合基本移动规则");

    ASSERT_FALSE(chariot.basic_check_move({0, 1}), "(0, 1) -> (0, 1) 不符合基本移动规则");
    ASSERT_FALSE(chariot.basic_check_move({2, 3}), "(0, 1) -> (2, 3) 不符合基本移动规则");
}

TEST_CASE(special_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Chariot chariot{SideTag::RED, Position{0, 1}};

    ASSERT_TRUE(chariot.special_check_move({0, 6}, board),
                "(0, 1) -> (0, 6)，路径中间没有棋子，符合特殊移动规则");

    Chariot obstacle{SideTag::BLACK, {0, 5}};
    board.set_piece(obstacle.pos(), &obstacle);
    ASSERT_FALSE(chariot.special_check_move({0, 6}, board),
                 "(0, 1) -> (0, 6)，路径中间有棋子，不符合特殊移动规则");
}

TEST_MAIN(RUN_TEST(basic_moves_gen); RUN_TEST(basic_check_move); RUN_TEST(special_check_move);)