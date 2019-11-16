#ifndef CONSOLE_GAME_HPP_
#define CONSOLE_GAME_HPP_

#include <iostream>
#include "AbstractGame.hpp"
#include "Board.hpp"
#include "HumanPlayer.hpp"

namespace game
{
class ConsoleGame : public AbstractGame
{
protected:
    HumanPlayer player1;
    HumanPlayer player2;

public:
    ConsoleGame();
    ~ConsoleGame();

    void draw() const override;
    bool isFinished() const override;
    void play() override;
};
} // namespace game

#endif