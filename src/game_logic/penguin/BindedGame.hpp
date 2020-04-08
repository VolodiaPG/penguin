#ifndef PENGUIN_BINDED_GAME_HPP_
#define PENGUIN_BINDED_GAME_HPP_

#include "Board.hpp"

namespace game
{
namespace penguin
{
class BindedGame
{
private:
    Board *_board;

public:
    BindedGame(const size_t size_map, const size_t number_of_penguins_per_team);
    ~BindedGame();
    Board* getBoard() { return _board; };
};
} // namespace penguin
} // namespace game

#endif