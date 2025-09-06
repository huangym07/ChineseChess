#include "GameContext.h"

const std::vector<std::unique_ptr<ChessPiece>> &GameContext::get_pieces(SideTag side_tag) const {
    assert(pieces.find(side_tag) != pieces.end() &&
           "向 GameContext 获取棋子时，不应传入未初始化的随机阵营枚举值");
    return pieces.find(side_tag)->second;
}