#include "MCTSPlayer.hpp"

namespace game
{

MCTSPlayer::MCTSPlayer(game::AbstractGame *g,
    unsigned int id,
    const mcts::MCTSConstraints &c)
    : AbstractPlayer(id)
{
    num_threads = 2;   
    for(int i = 0; i < num_threads; i++)
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
    unleash_mcts();

    mcts::Tree tree = joinTrees();

    AbstractBoardCell* bestMove = getCorrespondingMove(tree.bestMove());
    return bestMove;
}

void MCTSPlayer::updateTree(AbstractBoardCell* cell)
{
    tree_test->moveRootToCell(cell);
    for(unsigned long i = 0; i < trees.size(); i++)
        trees.at(i)->moveRootToCell(cell);
}

void MCTSPlayer::unleash_mcts()
{
    std::vector<std::thread> threads;

    if(num_threads > 1)
    {
        for(int i = 0; i < num_threads; i++)
        {
            mcts::MCTS ai(game->clone(), trees.at(i), constraints);
            threads.push_back(std::thread(&mcts::MCTS::begin, ai));
        }
        for(int i = 0; i < num_threads; i++)
        {
            threads.at(i).join();
        }
    }else
    {
        mcts::MCTS ai(game->clone(), trees.at(0), constraints);
        ai.begin();
    }
    
}

AbstractBoardCell* MCTSPlayer::getCorrespondingMove(AbstractBoardCell* cell)
{
    for(unsigned long i = 0; i < game->board->getBoardCells().size(); i++)
    {
        AbstractBoardCell* cellToTest = game->board->getBoardCells().at(i);
        if(cell->equals(cellToTest))
        {
            return cellToTest;
        }
    }
    return nullptr;
}

mcts::Tree MCTSPlayer::joinTrees()
{
    mcts::Tree tree(this);
    for(int i = 0; i < num_threads; i++)
    {
        tree.merge(trees.at(i));
    }
    return tree;
}

} // namespace game