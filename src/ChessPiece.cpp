#include "ChessPiece.h"
#include "CoreType.h"

ChessPiece::ChessPiece(const PieceType &type, const SideTag &side_tag, const Position &pos, const std::string &display_info)
    : piece_type_(type), side_tag_(side_tag), pos_(pos), display_info_(display_info) {}