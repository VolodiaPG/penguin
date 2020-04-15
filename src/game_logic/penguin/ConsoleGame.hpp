#ifndef  PENGUIN_CONSOLE_GAME_HPP_
#define  PENGUIN_CONSOLE_GAME_HPP_

#include <iostream>
#include "../AbstractInterface.hpp"
#include "../AbstractGame.hpp"
#include "PenguinGame.hpp"
#include "PrintHex.hpp"
#include "../../mcts/Tree.hpp"

// #include "../../dbg.h"

namespace game
{
namespace penguin
{
class ConsoleGame : public AbstractInterface
{
private:
    PenguinGame _game;
    PrintHex _print_hex;
    bool _no_print;

public:
    ConsoleGame(const bool& no_print);
    ~ConsoleGame();

    void draw() override;

    /**
     * @brief Loop while the game is not finished, told by the `isFinished` method
     * 
     */
    void loop();
};
} // namespace penguin
} // namespace game

#endif