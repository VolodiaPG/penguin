#include <thread>
#include <functional>

// #include "../game_logic/AbstractBoardCell.hpp"
#include "Tree.hpp"
#include "MCTS.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "MCTSPlayer.hpp"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
MCTSPlayer<CellT, PlayerT, PawnT>::MCTSPlayer(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    game::AbstractPlayer *player,
    const mcts::MCTSConstraints &constraints)
    : _binded_player(player)
{
    tree = new mcts::Tree<CellT, PlayerT, PawnT>(game, constraints);
}

template <class CellT, class PlayerT, class PawnT>
game::Move<CellT, PawnT> MCTSPlayer<CellT, PlayerT, PawnT>::bestMove()
{
    return tree->bestMove();
}

template <class CellT, class PlayerT, class PawnT>
void MCTSPlayer<CellT, PlayerT, PawnT>::updateTree(const game::Move<CellT, PawnT> &last_move_played)
{
    tree->moveRootToMove(last_move_played);
}

template <class CellT, class PlayerT, class PawnT>
void MCTSPlayer<CellT, PlayerT, PawnT>::unleash_mcts()
{
    std::vector<std::thread> threads;
    //We test here if there are more than 1 thread
    //We don't really need to launch a new thread if we only have 1 tree
    if (num_threads > 1)
    {
        //Create an ai for every thread with the clone of the board
        //If we used the current board, it gets very messy very quick
        for (int i = 0; i < num_threads; i++)
        {
            mcts::MCTS<CellT, PlayerT, PawnT> ai(game->clone(), trees.at(i), constraints);
            threads.push_back(std::thread(&mcts::MCTS<CellT, PlayerT, PawnT>::begin, ai));
        }
        //Wait for all threads to finish
        for (int i = 0; i < num_threads; i++)
        {
            threads.at(i).join();
        }
    }
    else
    {
        //Create only 1 ai and run it
        mcts::MCTS<CellT, PlayerT, PawnT> ai(game->clone(), trees.at(0), constraints);
        // TODO check for the life time of the object, where is it destroyed ?
        ai.begin();
    }
}

// template <class CellT, class PlayerT, class PawnT>
// game::AbstractBoardCell* MCTSPlayer<CellT, PlayerT, PawnT>::getCorrespondingMove(game::AbstractBoardCell* cell)
// {
//     //For every cell in the current game, test if it is equal to cell
//     //If it is then return that cell
//     for(unsigned long i = 0; i < game->board->getBoardCells().size(); i++)
//     {
//         game::AbstractBoardCell* cellToTest = game->board->getBoardCells().at(i);
//         if(cell->equals(cellToTest))
//         {
//             return cellToTest;
//         }
//     }
//     return nullptr;
// }

template <class CellT, class PlayerT, class PawnT>
mcts::Tree<CellT, PlayerT, PawnT> MCTSPlayer<CellT, PlayerT, PawnT>::joinTrees()
{
    mcts::Tree<CellT, PlayerT, PawnT> tree(nullptr, constraints);
    //For every tree, merge it into the new tree
    for (int i = 0; i < num_threads; i++)
    {
        tree.merge(trees.at(i));
    }
    return tree;
}

template class MCTSPlayer<game::tic_tac_toe::BoardCell, game::tic_tac_toe::Player, game::tic_tac_toe::Player>;
template class MCTSPlayer<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn>;

} // namespace mcts