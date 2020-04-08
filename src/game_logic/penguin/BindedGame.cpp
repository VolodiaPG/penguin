#include "BindedGame.hpp"

namespace game
{
namespace penguin
{

BindedGame::BindedGame(const size_t map_size, const size_t number_of_penguins_per_team)
{
    _board = new Board(map_size, number_of_penguins_per_team);
}

BindedGame::~BindedGame()
{
    if (_board)
        delete _board;
}

} // namespace penguin

} // namespace game
