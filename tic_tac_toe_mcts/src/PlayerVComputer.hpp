#ifndef PLAYER_V_COMPUTER_HPP_
#define PLAYER_V_COMPUTER_HPP_

#include <iostream>
#include "TicTacToe.hpp"
#include "HumanPlayer.hpp"
#include "MCTSPlayer.hpp"

// #include <emscripten/bind.h>

namespace game
{
/**
 * @brief Player vs Computer modelisation, player1 is the player and player 2 the MCTS player
 * 
 */
class PlayerVComputer : public TicTacToe
{
public:
    explicit PlayerVComputer();
    ~PlayerVComputer();

    bool playPlayer1(const Position &pos);
};
} // namespace game

// EMSCRIPTEN_BINDINGS(module_playervcomputer)
// {
//     emscripten::class_<game::PlayerVComputer>("PlayerVComputer")
//         .constructor<game::JSPlayer::action_callback>()
//         .function("playGame", &game::PlayerVComputer::playGame)
//         .function("isFinished", &game::PlayerVComputer::isFinished);
// }

#endif