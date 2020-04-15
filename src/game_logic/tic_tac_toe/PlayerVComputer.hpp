#ifndef TIC_TAC_TOE_PLAYER_V_COMPUTER_HPP_
#define TIC_TAC_TOE_PLAYER_V_COMPUTER_HPP_

#include "TicTacToe.hpp"

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
    Move mctsResult();
};
} // namespace tic_tac_toe
} // namespace game

#endif
