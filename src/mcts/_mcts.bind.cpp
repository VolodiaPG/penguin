#ifndef MCTS_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "Tree.hpp"
#include "MCTSPlayer.hpp"

namespace mcts
{
    using namespace emscripten;

    // Binding code
    EMSCRIPTEN_BINDINGS(mcts_bind)

    {
        value_object<MCTSConstraints>("MCTSConstraints")
            .field("time", &MCTSConstraints::time);

#define __MCTS_BIND__(name_prefix, MCTSPlayer, AbstractGame, Result)                       \
                                                                                           \
    class_<MCTSPlayer>(name_prefix "_MCTSPlayer")                                          \
        .constructor<AbstractGame *const &, const MCTSConstraints &>(allow_raw_pointers()) \
        .function("bestMove", &MCTSPlayer::bestMove)                                       \
        .function("updateTree", &MCTSPlayer::updateTree)                                   \
        .function("getResult", &MCTSPlayer::getResult);                              \
                                                                                           \
    value_object<Result>(name_prefix "_Result")                                            \
        .field("best_move", &Result::best_move)                                            \
        .field("score", &Result::score)                                                    \
        .field("visits", &Result::visits)

        typedef MCTSPlayer<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn> penguin_mcts_player_t;
        typedef game::AbstractGame<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn> penguin_game_t;
        typedef Result<game::penguin::BoardCell, game::penguin::PenguinPawn> result_t;

        __MCTS_BIND__("penguin", penguin_mcts_player_t, penguin_game_t, result_t);
    }
} // namespace mcts

#endif
#endif