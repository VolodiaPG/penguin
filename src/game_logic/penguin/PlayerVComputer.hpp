#ifndef TIC_TAC_TOE_PLAYER_V_COMPUTER_HPP_
#define TIC_TAC_TOE_PLAYER_V_COMPUTER_HPP_

#include <iostream>
#include "PenguinGame.hpp"
#include "../../mcts/Tree.hpp"

// #include <emscripten/bind.h>
// #include <emscripten.h>

namespace game
{
namespace penguin
{
/**
 * @brief Player vs Computer modelisation, player1 is the player and player 2 the MCTS player
 * 
 */
class PlayerVComputer : public PenguinGame
{
public:
    PlayerVComputer();
    ~PlayerVComputer();

    using PenguinGame::play;
    bool play(int row, int col);
    AbstractBoardCell *mctsResult();
};
} // namespace penguin
} // namespace game

#endif
