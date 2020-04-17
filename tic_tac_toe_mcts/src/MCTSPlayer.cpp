#include "MCTSPlayer.hpp"

namespace game
{

MCTSPlayer::MCTSPlayer(game::AbstractGame *g,
    unsigned int id,
    const mcts::MCTSConstraints &c)
    : AbstractPlayer(id)
{
    int nb = 1;
    
    for(int i = 0; i < nb; i++)
        trees.push_back(new mcts::Tree(this));
    game = g;
    constraints = c;
    tree_test = new mcts::Tree(this);
}

MCTSPlayer::~MCTSPlayer()
{
    delete tree_test;
    for(mcts::Tree* tree : trees)
        delete tree;
    trees.clear();
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
    mcts::MCTS ai(game->clone(), trees.at(0), constraints);
    
    ai.begin();
    
    return trees.at(0)->bestMove();
}

void MCTSPlayer::updateTree(AbstractBoardCell* cell)
{
    tree_test->moveRootToCell(cell);
    for(unsigned long i = 0; i < trees.size(); i++)
        trees.at(i)->moveRootToCell(cell);
}

} // namespace game