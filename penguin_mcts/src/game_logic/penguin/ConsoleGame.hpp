#ifndef  PENGUIN_CONSOLE_GAME_HPP_
#define  PENGUIN_CONSOLE_GAME_HPP_

#include <iostream>
#include "../AbstractInterface.hpp"
#include "Board.hpp"

namespace game
{
namespace penguin
{
class ConsoleGame : public AbstractInterface
{
private:
    penguin::Board board;

public:
    ConsoleGame();
    ~ConsoleGame();

    void draw() const override;

    /**
     * @brief Loop while the game is not finished, told by the `isFinished` method
     * 
     */
    void loop();
};
} // namespace penguin
} // namespace game

#endif