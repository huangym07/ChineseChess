#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "TestFramework.h"
#include <Windows.h>
#include <iostream>
#include <map>

class ChessPiece;

TEST_CASE(nine_palace) {
    int height = StandardChineseChessConfig::HEIGHT;
    int width = StandardChineseChessConfig::WIDTH;

    ChessBoard chess_board{width, height,
                           std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};

    std::vector<std::vector<int>> ans(height, std::vector<int>(width, 0));

    // 上面九宫
    for (int i = 0; i <= 2; ++i) {
        for (int j = 3; j <= 5; ++j) {
            ans[i][j] = 9;
        }
    }
    // 下面九宫
    for (int i = 9; i >= 7; --i) {
        for (int j = 3; j <= 5; ++j) {
            ans[i][j] = 18;
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (9 == ans[i][j]) {
                ASSERT_FALSE(chess_board.is_out_of_nine_palace(SideTag::RED, Position{j, i}), "(" << j << ", " << i << ") 应在红方九宫内");
            } else if (18 == ans[i][j]) {
                ASSERT_FALSE(chess_board.is_out_of_nine_palace(SideTag::BLACK, Position{j, i}), "(" << i << ", " << i << ") 应在黑方九宫内");
            } else {
                ASSERT_TRUE(chess_board.is_out_of_nine_palace(SideTag::RED, Position{j, i}) && chess_board.is_out_of_nine_palace(SideTag::BLACK, Position{j, i}), "(" << j << ", " << i << ") 不应在九宫里");
            }
        }
    }
}

TEST_CASE(across_river) {
    int height = StandardChineseChessConfig::HEIGHT;
    int width = StandardChineseChessConfig::WIDTH;

    ChessBoard chess_board{width, height,
                           std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};

    for (int j = 0; j < width; ++j) {
        for (int i = 0; i < height; ++i) {
            ASSERT_FALSE(chess_board.is_across_river(i <= 4 ? SideTag::RED : SideTag::BLACK, Position{j, i}), "(" << j << ", " << i << ") 不应跨过" << (i <= 4 ? "红" : "黑") << "方楚河汉界");
        }
    }
}

TEST_MAIN(
    RUN_TEST(nine_palace); 
    RUN_TEST(across_river);
)