#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include <Windows.h>
#include <iostream>
#include <map>

class ChessPiece;

void test_palace_river() {
    std::cout << __PRETTY_FUNCTION__ << " start" << std::endl;

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
                if (chess_board.is_out_of_nine_palace(SideTag::RED, Position{j, i})) {
                    std::cerr << "(" << j << ", " << i << ") 应在红方九宫内\n";
                    std::exit(-1);
                }
            } else if (18 == ans[i][j]) {
                if (chess_board.is_out_of_nine_palace(SideTag::BLACK, Position{j, i})) {
                    std::cerr << "(" << j << ", " << i << ") 应在黑方九宫内\n";
                    std::exit(-1);
                }
            } else {
                if (!chess_board.is_out_of_nine_palace(SideTag::RED, Position{j, i}) ||
                    !chess_board.is_out_of_nine_palace(SideTag::BLACK, Position{j, i})) {
                        std::cerr << "(" << j << ", " << i << ") 不应在九宫内\n";
                        std::exit(-1);
                }
            }
        }
    }

    for (int j = 0; j < width; ++j) {
        for (int i = 0; i < height; ++i) {
            if (chess_board.is_across_river(i <= 4 ? SideTag::RED : SideTag::BLACK, Position{j, i})) {
                std::cerr << "(" << j << ", " << i << ") 不应跨过" << (i <= 4 ? "红" : "黑") << "方楚河汉界\n";
                std::exit(-1);
            }
        }
    }

    std::cout << __PRETTY_FUNCTION__ << " passed." << std::endl;
}

int main() {
    // Windows API, 设置控制台为 UTF-8 模式
    SetConsoleOutputCP(CP_UTF8);

    std::cout << __FILE__ << std::endl;

    test_palace_river();

    return 0;
}