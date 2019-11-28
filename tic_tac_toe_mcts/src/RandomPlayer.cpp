#include "RandomPlayer.hpp"

namespace game
{

RandomPlayer::RandomPlayer(unsigned int id, AbstractGame *game)
    : AbstractPlayer(id, game)
{
}

AbstractBoardCell *RandomPlayer::randomAction()
{
    std::vector<AbstractBoardCell *> cells = game->board->getEmptyCells();

    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    AbstractPlayer::action(cells[index]);

    return cells[index];
}

} // namespace game