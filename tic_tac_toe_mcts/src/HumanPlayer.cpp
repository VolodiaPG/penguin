#include "HumanPlayer.hpp"

namespace game
{
HumanPlayer::HumanPlayer(unsigned int id)
    : AbstractPlayer(id)
{
}

void HumanPlayer::action(AbstractBoard *board)
{
    Position pos;
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
            // do the move
            correct = board->performMove(getId(), pos);
        }
    } while (!correct);
}
} // namespace game