#ifndef CHINESECHESS_PIECEFACTORY_H
#define CHINESECHESS_PIECEFACTORY_H

#include "Common/CoreType.h"
#include <functional>
#include <map>
#include <memory>

class ChessPiece;

class PieceFactory {
  private:
    using CreatorFunc = std::function<std::unique_ptr<ChessPiece>(SideTag, Position)>;

    static const std::map<PieceType, CreatorFunc> creators_;

  public:
    static std::unique_ptr<ChessPiece> create_piece(const PieceConfig &config);
};

#endif // CHINESECHESS_PIECEFACTORY_H