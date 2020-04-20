#include <thread>
#include <functional>
#include <algorithm>
#include <assert.h>

#include "../game_logic/AbstractBoard.hpp"
#include "Tree.hpp"
#include "MCTS.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "MCTSPlayer.hpp"

#include "../dbg.h"
#pragma message("PrintHex here")
#include "../game_logic/penguin/PrintHex.hpp"
#include "../game_logic/penguin/PenguinGame.hpp"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
MCTSPlayer<CellT, PlayerT, PawnT>::MCTSPlayer(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    game::AbstractPlayer *player,
    const mcts::MCTSConstraints &constraints)
    : _binded_player(player),
      game(game),
      constraints(constraints),
      num_threads(THREAD_NUMBER)
{
    //Initialize all trees
    //TODO optimiser, pas besoin de cloner a chaque fois pour le 0, prendre directe le game qu'on passe !
    for (int i = 0; i < num_threads; i++)
        trees.push_back(new mcts::Tree<CellT, PlayerT, PawnT>(game->clone(), constraints));
}

template <class CellT, class PlayerT, class PawnT>
MCTSPlayer<CellT, PlayerT, PawnT>::~MCTSPlayer()
{
    for (mcts::Tree<CellT, PlayerT, PawnT> *tree : trees)
        delete tree;
    trees.clear();
}

template <class CellT, class PlayerT, class PawnT>
game::Move<CellT, PawnT> MCTSPlayer<CellT, PlayerT, PawnT>::bestMove()
{
    //begins the mcts search
    unleash_mcts();

    //merge every result into 1 tree
    mcts::Tree<CellT, PlayerT, PawnT> tree = joinTrees();

    return getCorrespondingMove(tree.bestMove());
}

template <class CellT, class PlayerT, class PawnT>
void MCTSPlayer<CellT, PlayerT, PawnT>::updateTree(const game::Move<CellT, PawnT> &last_move_played)
{
    // tree->moveRootToMove(last_move_played);

    //Moves all rootNodes to the corresponding cell
    // game::penguin::PrintHex printer(reinterpret_cast<game::penguin::PenguinGame *>(game)->getBoard());
    // printer.print();
    for (unsigned long i = 0; i < trees.size(); i++)
    {
        // game::penguin::PrintHex printer2(reinterpret_cast<game::penguin::PenguinGame *>(game)->getBoard());
        // printer2.print();
        trees.at(i)->moveRootToMove(last_move_played);
    }
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
            mcts::MCTS<CellT, PlayerT, PawnT> ai(trees.at(i), constraints);
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
        mcts::MCTS<CellT, PlayerT, PawnT> ai(trees.at(0), constraints);
        // TODO check for the life time of the object, where is it destroyed ?
        ai.begin();
    }
}

template <class CellT, class PlayerT, class PawnT>
const game::Move<CellT, PawnT> MCTSPlayer<CellT, PlayerT, PawnT>::getCorrespondingMove(const game::Move<CellT, PawnT> &move)
{
    //For every cell in the current game, test if it is equal to cell
    //If it is then return that cell
    std::vector<game::Move<CellT, PawnT>> moves = game->getAvailableMoves(game->board->getPlayerById(move.pawn->getOwner()->getId()));
    const auto it = std::find_if(
        std::begin(moves),
        std::end(moves),
        [move](const game::Move<CellT, PawnT> &move_testing) -> bool { return move == move_testing; });

    assert("Should never return null !!!!! Meaning the move doesn't translate to the current game playing" && it != std::end(moves));

    if (it != std::end(moves))
    {
        return *it;
    }

    return {nullptr, nullptr, nullptr};
}

template <class CellT, class PlayerT, class PawnT>
mcts::Tree<CellT, PlayerT, PawnT> MCTSPlayer<CellT, PlayerT, PawnT>::joinTrees()
{
    mcts::Tree<CellT, PlayerT, PawnT> tree(game, constraints);
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