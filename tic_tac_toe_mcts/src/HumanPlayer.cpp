#include "HumanPlayer.hpp"

namespace game
{
HumanPlayer::HumanPlayer()
    : AbstractPlayer()
{
    static int nextPlayerId = 1;
    id = nextPlayerId++;
}

void HumanPlayer::action(AbstractBoard *board)
{
    Position pos;

    // while the input is not correct, ask
    std::cout << "[" << id << "] Please enter a coordinate between 0 and " << board->size() << std::endl;
    do
    {
        std::cout << "X Coodinate: " << std::endl;
        std::cin >> pos.x;
        std::cout << "Y Coodinate: " << std::endl;
        std::cin >> pos.y;
    } while (!(pos.x < board->size() && pos.y < board->size()));

    // do the move
    board->performMove(id, pos);
}
} // namespace game