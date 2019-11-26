#include "JSPlayer.hpp"

namespace game
{
JSPlayer::JSPlayer(unsigned int id, action_callback callback)
    : AbstractPlayer(id),
      callback(callback)
{
}

AbstractBoardCell *JSPlayer::action(AbstractBoard *board)
{
    Position pos;
    AbstractBoardCell *cell = nullptr;
    bool correct = false;

    // while the input is not correct, ask
    do
    {
        pos = callback(getId());
        std::cout << "Got: " << pos.x << ", " << pos.y << std::endl;
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