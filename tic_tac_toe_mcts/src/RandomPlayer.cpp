#include "RandomPlayer.hpp"

namespace game
{

RandomPlayer::RandomPlayer(unsigned int id) : AbstractPlayer(id)
{
}

void RandomPlayer::action(AbstractBoard *board)
{
    std::vector<AbstractBoardCell *> cells = board->getEmptyCells();

    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    board->performMove(getId(), cells[index]);
}

} // namespace game