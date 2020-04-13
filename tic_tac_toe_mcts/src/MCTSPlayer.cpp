#include "MCTSPlayer.hpp"

namespace game
{

MCTSPlayer::MCTSPlayer(game::AbstractGame *g,
    unsigned int id,
    const mcts::MCTSConstraints &constraints)
    : AbstractPlayer(id)
{
    tree = new mcts::Tree(game, this, constraints);
    game = g;
}

MCTSPlayer::~MCTSPlayer()
{
    delete tree;
}

AbstractBoardCell * MCTSPlayer::bestMove()
{
    /*
    std::thread th1(&mcts::Tree::begin, tree);
    std::thread th2(&mcts::Tree::begin, tree);
    //tree->begin();
    th1.join();
    th2.join();
    */
    mcts::MCTS ai(game, tree, tree->constraints);
    ai.begin();
    return tree->bestMove();
}

void MCTSPlayer::updateTree(AbstractBoardCell* cell)
{
    tree->moveRootToCell(cell);
}

} // namespace game