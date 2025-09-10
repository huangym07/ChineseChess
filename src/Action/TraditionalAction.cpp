#include "Action/TraditionalAction.h"
#include "GameContext.h"

void TraditionalAction::run_game(GameContext &context) const {
    int index = 0;
    while (true) {
        context.board->show_board();
        // TODO    
        assert(false && "run game");
    }
}

// std::vector<std::pair<Position, Position>> TraditionalAction::generate_all_valid_moves(GameContext &context, const Player *current_player) const {
//     const auto &pieces = context.get_pieces(current_player->side_tag());

//     for (const auto &uptr : pieces) {
//         // TODO
//     }
// }
