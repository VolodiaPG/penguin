#include "PenguinGame.hpp"

namespace game
{
namespace penguin
{

PenguinGame::PenguinGame(const size_t dimension, const size_t number_of_penguins_per_team)
    : AbstractGame(new Board(dimension, number_of_penguins_per_team))
{
}

PenguinGame::~PenguinGame()
{
    delete board;
}

bool PenguinGame::play(PenguinPawn *pawn, BoardCell *move)
{
    bool moved = board->performMove(pawn, move);
    if (moved)
    {
        ++numberMoves;
    }
    return moved;
}

void PenguinGame::revertPlay()
{
    --numberMoves;
    int player = 2;

    if (numberMoves % 2)
    {
        player = 1;
    }

    board->revertMove(board->getPlayerById(player));
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

std::vector<Move> PenguinGame::getAvailableMoves(HumanPlayer *human_player)
{
    assert(human_player != nullptr);
    std::vector<Move> ret;
    Board *penguin_board = (Board *)board;
    std::vector<PenguinPawn *> penguins = human_player->getPenguins();

    for (PenguinPawn *penguin : penguins)
    {
        BoardCell *current_cell = (BoardCell *)penguin->getCurrentCell();
        std::cout << "Penguin #" << penguin->getId() << " @(" << current_cell->getPosition().x << "," << current_cell->getPosition().y << ")" << std::endl;
        std::vector<BoardCell *> availableCells = penguin_board->getAvailableCells(penguin);
        for (auto cell : availableCells)
        {
            std::cout << cell->getPosition().x << "," << cell->getPosition().y << std::endl;
        }
        std::transform(availableCells.begin(), availableCells.end(), std::back_inserter(ret), [current_cell, penguin](BoardCell *cell) -> Move {
            // std::cout << penguin->getId()<<","<<cell->getPosition().x << ","<< cell->getPosition().y << std::endl;
             return {current_cell, cell, (AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell> *)penguin}; });
    }

    return ret;
}
} // namespace penguin
} // namespace game
