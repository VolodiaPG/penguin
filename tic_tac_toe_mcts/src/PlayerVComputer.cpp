#include "PlayerVComputer.hpp"

namespace game
{
PlayerVComputer::PlayerVComputer(JSPlayer::action_callback humanActionCallback)
    : AbstractGame(nullptr)
{
    // player1 = new MCTSPlayer(1, this);
    player1 = new JSPlayer(1, humanActionCallback);
    // player2 = new MCTSPlayer(1, this);
    player2 = new MCTSPlayer(2, this);

    // player2 = new HumanPlayer(2);

    board = new Board();
}

PlayerVComputer::~PlayerVComputer()
{
    delete player1;
    delete player2;
    delete board;
}

AbstractBoardCell *PlayerVComputer::play(AbstractPlayer *player1, AbstractPlayer *player2)
{
    Board *bo = (Board *)board;
    AbstractPlayer *player = player1;

    if (bo->getTotalMoves() % 2)
    {
        player = player2;
    }

    return player->action(board);
}

void PlayerVComputer::revertPlay(AbstractBoardCell *move)
{
    board->revertMove(move);
}

bool PlayerVComputer::isFinished() const
{
    return board->checkStatus() != 0;
}
} // namespace game
