#ifndef TIC_TAC_TOE_PLAYER_V_COMPUTER_HPP_
#define TIC_TAC_TOE_PLAYER_V_COMPUTER_HPP_

#include <iostream>
#include "TicTacToe.hpp"
#include "Player.hpp"
#include "../../mcts/Tree.hpp"

// #include <emscripten/bind.h>
// #include <emscripten.h>

namespace game
{
namespace tic_tac_toe
{
/**
 * @brief Player vs Computer modelisation, player1 is the player and player 2 the MCTS player
 * 
 */
class PlayerVComputer : public TicTacToe
{
public:
    PlayerVComputer();
    ~PlayerVComputer();

    using TicTacToe::play;
    bool play(int row, int col);
    AbstractBoardCell *mctsResult();
};
} // namespace tic_tac_toe
} // namespace game

// using namespace emscripten;

// #ifdef __EMSCRIPTEN__
// extern "C"{
//  game::PlayerVComputer gameInstance;
// bool playPlayer1(int x, int y)
// {
//     return gameInstance.playPlayer1(x, y);
// }

// bool playPlayer2()
// {
//     return gameInstance.playPlayer2();
// }
// }
// #endif

#endif
