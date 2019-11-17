#include "HumanPlayer.hpp"

namespace game
{
HumanPlayer::HumanPlayer(unsigned int id)
    : AbstractPlayer(id)
{
}

AbstractBoardCell *HumanPlayer::action(AbstractBoard *board)
{
    Position pos;
    AbstractBoardCell *cell = nullptr;
    bool correct = false;

    // while the input is not correct, ask
    std::cout << "[" << getId() << "] Please enter a coordinate between 0 and " << board->size() << std::endl;
    do
    {
        std::cout << "X Coodinate: " << std::endl;
        std::cin >> pos.x;
        std::cout << "Y Coodinate: " << std::endl;
        std::cin >> pos.y;
        correct = pos.x < board->size() && pos.y < board->size();
        if (correct)
        {
            cell = board->getCell(pos.x, pos.y);
            // do the move
            correct = board->performMove(getId(), cell);
        }
    } while (!correct);
    return cell;
}
} // namespace game