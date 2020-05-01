#ifndef MCTS_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "MCTSPlayer.hpp"

namespace mcts
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(mcts_bind)

{
#define __MCTS_BIND__(name_prefix, MCTSPlayer, AbstractGame)                               \
                                                                                           \
    class_<MCTSPlayer>(name_prefix "_MCTSPlayer")                                          \
        .constructor<AbstractGame *const &, const MCTSConstraints &>(allow_raw_pointers()) \
        .function("bestMove", &MCTSPlayer::bestMove)                                       \
        .function("updateTree", &MCTSPlayer::updateTree)

    typedef MCTSPlayer<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn> penguin_mcts_player_t;
    typedef game::AbstractGame<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn> penguin_game_t;
    __MCTS_BIND__("penguin", penguin_mcts_player_t, penguin_game_t);
}
} // namespace mcts

#endif
#endif