#include "PlayerVComputer.hpp"

namespace game
{
namespace penguin
{
PlayerVComputer::PlayerVComputer()
    : PenguinGame(7, 2)
{
    Board *board = (Board *)this->board;
    // Placing all the penguins
    // team 1
    board->performMove(0, board->getCell(0, 0));
    board->performMove(1, board->getCell(3, 6));
    // team 2
    board->performMove(2, board->getCell(-3, 6));
    board->performMove(3, board->getCell(6, 0));
}

PlayerVComputer::~PlayerVComputer()
{
}

bool PlayerVComputer::play(int row, int col)
{
    return play(getPlayerToPlay(), board->getCell(row, col));
}

AbstractBoardCell *PlayerVComputer::mctsResult()
{
    mcts::MCTSConstraints constraints;
    constraints.time = 250;
    auto game = dynamic_cast<AbstractGame<AbstractPlayer, AbstractBoardCell> *>(this);
    mcts::Tree tree(game, board->getPlayerById(getPlayerToPlay()), constraints);
    tree.begin();
    AbstractBoardCell *bestMove = tree.bestMove();

    return bestMove;
}
} // namespace penguin
} // namespace game
