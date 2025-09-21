#include "Action/TraditionalAction.h"
#include "Common/CoreType.h"
#include "GameContext.h"

bool TraditionalAction::is_checked(const GameContext &context, SideTag side_tag) const {
    const auto &pieces = context.get_pieces(side_tag);
    const auto &enemy_pieces = context.get_pieces(SideTag::RED == side_tag ? SideTag::BLACK : SideTag::RED);

    const ChessPiece *general_piece = nullptr;
    for (const auto &piece : pieces) {
        if (PieceType::GENERAL == piece->piece_type()) {
            general_piece = piece.get();
            break;
        }
    }

    assert(nullptr != general_piece && "GameContext 中不应没有将/帅棋子");

    for (const auto &enemy_piece : enemy_pieces) {
        if (enemy_piece->get_attribute(AttributeType::HP) > 0 && enemy_piece->can_capture(*context.board, general_piece)) return true;
    }

    return false;
}

void TraditionalAction::run_game(GameContext &context) const {
    int index = 0;
    while (true) {
        context.board->show_board();
        // TODO    
        assert(false && "run game");
        std::exit(1);
    }
}

// std::vector<std::pair<Position, Position>> TraditionalAction::generate_all_valid_moves(GameContext &context, const Player *current_player) const {
//     const auto &pieces = context.get_pieces(current_player->side_tag());

//     for (const auto &uptr : pieces) {
//         // TODO
//     }
// }
