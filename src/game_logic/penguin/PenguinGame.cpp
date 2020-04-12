#include "PenguinGame.hpp"

namespace game
{
namespace penguin
{

PenguinGame::PenguinGame(const size_t dimension, const size_t number_of_penguins_per_team)
    : AbstractGame(new Board(dimension, number_of_penguins_per_team)) // nullptr during construct, then we define the board
{
}

PenguinGame::~PenguinGame()
{
    delete board;
}

bool PenguinGame::play(const int penguin_player_id, BoardCell *move)
{
    bool moved = board->performMove(penguin_player_id, move);
    if (moved)
    {
        ++numberMoves;
    }
    return moved;
}

void PenguinGame::revertPlay()
{
    --numberMoves;
    int player = 0;

    if (numberMoves % 2)
    {
        player = 1;
    }

    board->revertMove(player);
}

bool PenguinGame::isFinished() const
{
    return board->checkStatus() != 0;
}

unsigned int PenguinGame::getPlayerToPlay() const
{
    int nextPlayer = 2;

    if (numberMoves % 2)
    {
        nextPlayer = 1;
    }

    return nextPlayer;
}

std::vector<Move> PenguinGame::getAvailableMoves(const unsigned int human_player_id)
{
    std::vector<Move> ret;
    Board *penguin_board = (Board *)board;

    HumanPlayer *human_player = penguin_board->getHumanPlayerById(human_player_id);
    for (unsigned int penguin_id : human_player->getPenguins())
    {
        std::vector<BoardCell *> availableCells = penguin_board->getAvailableCells(penguin_id);
        ret.reserve(ret.size() + availableCells.size());
        std::transform(availableCells.begin(), availableCells.end(), ret.end(), [penguin_id](BoardCell *cell) -> Move { return Move{penguin_id, cell}; });
    }

    return ret;
}
} // namespace penguin
} // namespace game
