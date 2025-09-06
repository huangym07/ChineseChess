#include "Action/TraditionalAction.h"
#include "GameContext.h"

void TraditionalAction::run_game(GameContext &context) const {
    int index = 0;
    while (true) {
        context.board->show_board();
        // TODO    
    }
}