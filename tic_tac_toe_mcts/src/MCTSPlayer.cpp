#include "MCTSPlayer.hpp"

namespace game
{

MCTSPlayer::MCTSPlayer(game::AbstractGame *g,
    unsigned int id,
    const mcts::MCTSConstraints &c)
    : AbstractPlayer(id)
{
    num_threads = 2;
    //Initialize all trees
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
    //begins the mcts search
    unleash_mcts();

    //merge every result into 1 tree
    mcts::Tree tree = joinTrees();

    //get the best move out of all trees, and get the corresponding cell on the actual board
    AbstractBoardCell* bestMove = getCorrespondingMove(tree.bestMove());
    return bestMove;
}

void MCTSPlayer::updateTree(AbstractBoardCell* cell)
{
    tree_test->moveRootToCell(cell);
    //Moves all rootNodes to the corresponding cell
    for(unsigned long i = 0; i < trees.size(); i++)
        trees.at(i)->moveRootToCell(cell);
}

void MCTSPlayer::unleash_mcts()
{
    std::vector<std::thread> threads;
    //We test here if there are more than 1 thread
    //We don't really need to launch a new thread if we only have 1 tree
    if(num_threads > 1)
    {
        //Create an ai for every thread with the clone of the board
        //If we used the current board, it gets very messy very quick
        for(int i = 0; i < num_threads; i++)
        {
            mcts::MCTS ai(game->clone(), trees.at(i), constraints);
            threads.push_back(std::thread(&mcts::MCTS::begin, ai));
        }
        //Wait for all threads to finish
        for(int i = 0; i < num_threads; i++)
        {
            threads.at(i).join();
        }
    }else
    {
        //Create only 1 ai and run it
        mcts::MCTS ai(game->clone(), trees.at(0), constraints);
        ai.begin();
    }
    
}

AbstractBoardCell* MCTSPlayer::getCorrespondingMove(AbstractBoardCell* cell)
{
    //For every cell in the current game, test if it is equal to cell
    //If it is then return that cell
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
    //For every tree, merge it into the new tree
    for(int i = 0; i < num_threads; i++)
    {
        tree.merge(trees.at(i));
    }
    return tree;
}

} // namespace game