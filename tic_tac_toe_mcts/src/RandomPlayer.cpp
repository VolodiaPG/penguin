#include "RandomPlayer.hpp"

namespace game
{

RandomPlayer::RandomPlayer(unsigned int id) : AbstractPlayer(id)
{
}

AbstractBoardCell *RandomPlayer::action(AbstractBoard *board)
{
    std::vector<AbstractBoardCell *> cells = board->getEmptyCells();

    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    board->performMove(getId(), cells[index]);
    return cells[index];
}

} // namespace game