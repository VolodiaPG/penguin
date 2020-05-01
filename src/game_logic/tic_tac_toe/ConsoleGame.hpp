#ifndef TIC_TAC_TOE_CONSOLE_GAME_HPP_
#define TIC_TAC_TOE_CONSOLE_GAME_HPP_

#include "../AbstractInterface.hpp"
#include "TicTacToe.hpp"
#include "Player.hpp"

#include "../../mcts/MCTSPlayer.hpp"

namespace game
{
namespace tic_tac_toe
{
class ConsoleGame : public TicTacToe, public AbstractInterface
{
public:
    ConsoleGame();
    ~ConsoleGame();

    friend mcts::MCTSPlayer<BoardCell, Player, Player>;

    void draw() override;

    /**
     * @brief Loop while the game is not finished, told by the `isFinished` method
     * 
     */
    void loop();
};
} // namespace tic_tac_toe
} // namespace game

#endif