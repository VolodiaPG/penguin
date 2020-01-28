#ifndef CONSOLE_GAME_HPP_
#define CONSOLE_GAME_HPP_

#include <iostream>
#include "TicTacToe.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Tree.hpp"
#include "TreeVisualizer.hpp"

namespace game
{
class ConsoleGame : public TicTacToe, public AbstractInterface
{
public:
    ConsoleGame();
    ~ConsoleGame();

    /**
     * @brief Draws the board
     * 
     */
    void draw() const override;
    
    /**
     * @brief Loop while the game is not finished, told by the `isFinished` method
     * 
     */
    void loop();
};
} // namespace game

#endif