#include "HumanPlayer.hpp"

namespace game
{
HumanPlayer::HumanPlayer()
    : AbstractPlayer()
{
    static int nextPlayerId = 0;
    id = nextPlayerId++;
}

void HumanPlayer::action(AbstractBoard *board)
{
    Position pos;
    bool correct = false;

    // while the input is not correct, ask
    do
    {
        std::cout << "X Coodinate: " << std::endl;
        std::cin >> pos.x;
        std::cout << "Y Coodinate: " << std::endl;
        std::cin >> pos.y;
    } while ((correct = (pos.x < board->size() && pos.y < board->size())));

    // do the move
    board->performMove(id, pos);
}
} // namespace game