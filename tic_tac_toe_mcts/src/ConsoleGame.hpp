#ifndef CONSOLE_GAME_HPP_
#define CONSOLE_GAME_HPP_

#include "AbstractGame.hpp"
#include "AbstractConsoleInterface.hpp"

namespace game
{
class ConsoleGame : public AbstractGame, public AbstractConsoleInterface
{

};
} // namespace game

#endif