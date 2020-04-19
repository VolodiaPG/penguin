#include "../game_logic/AbstractBoard.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "MCTS.hpp"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
MCTS<CellT, PlayerT, PawnT>::MCTS(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    mcts::Tree<CellT, PlayerT, PawnT> *tree,
    const MCTSConstraints &constraints)
    : constraints(constraints),
      game(game),
      tree(tree)
{
}

template <class CellT, class PlayerT, class PawnT>
MCTS<CellT, PlayerT, PawnT>::~MCTS()
{
}

template <class CellT, class PlayerT, class PawnT>
size_t MCTS<CellT, PlayerT, PawnT>::begin()
{
    Node<CellT, PawnT> &rootNode = tree->getRootNode();
    timer t;
    while (t.milliseconds_elapsed() < static_cast<unsigned long>(constraints.time))
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            Node<CellT, PawnT> *promisingNode = selectBestChildAndDoAction(&rootNode);

            if (!game->isFinished() && promisingNode->childNodes.size() == 0)
            {
                expandNode(promisingNode);
            }

            Node<CellT, PawnT> *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

            if (nodeToExplore != promisingNode)
            {
                doActionOnBoard(*nodeToExplore);
            }

            int winnerId = randomSimulation();

            backPropagateAndRevertAction(winnerId, nodeToExplore);
        }
    }

    return rootNode.visits;

    // timer t;
    // root = tree->getRootNode();

    // while (t.milliseconds_elapsed() < (unsigned long)constraints.time)
    // {
    //     for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
    //     {
    //         //std::cout << "Selection" << std::endl;
    //         Node<CellT, PawnT> *promisingNode = selectBestChildAndDoAction(root);

    //         //std::cout << "Expand" << std::endl;
    //         if (!game->isFinished())
    //         {

    //             expandNode(promisingNode);
    //         }

    //         //std::cout << "Random" << std::endl;
    //         Node<CellT, PawnT> *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

    //         //std::cout << "Do Action" << std::endl;
    //         if (nodeToExplore != promisingNode)
    //         {
    //             doActionOnBoard(*nodeToExplore);
    //         }

    //         //std::cout << "Simulation" << std::endl;
    //         int winnerId = randomSimulation();

    //         //std::cout << "Backprop" << std::endl;
    //         backPropagateAndRevertAction(winnerId, nodeToExplore);
    //     }
    // }
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::expandNode(Node<CellT, PawnT> *nodeToExpand)
{
    // the turn has already been played, now it's the next player's turn
    PlayerT *player = game->board->getPlayerById(game->getPlayerToPlay());

    for (const game::Move<CellT, PawnT> &move : game->getAvailableMoves(player))
    {
        Node<CellT, PawnT> *node = new Node<CellT, PawnT>();
        node->parent = nodeToExpand;
        node->move = move;

        nodeToExpand->childNodes.push_back(node);
    }
    // // the turn has already been played, now it's the next player's turn
    // game::AbstractPlayer *nextPlayer = game->getPlayerToPlay();

    // for (game::AbstractBoardCell *move : game->board->getAvailableCells())
    // {
    //     Node<CellT, PawnT> *node = new Node<CellT, PawnT>();
    //     node->parent = nodeToExpand;
    //     node->player = nextPlayer;
    //     node->targetedCell = move;

    //     nodeToExpand->childNodes.push_back(node);
    // }
}

template <class CellT, class PlayerT, class PawnT>
double MCTS<CellT, PlayerT, PawnT>::formula(
    const Node<CellT, PawnT> &node,
    const Node<CellT, PawnT> &nodeSuccessor) const
{
    double ret = std::numeric_limits<double>::max();
    if (nodeSuccessor.visits != 0)
    {
        ret = nodeSuccessor.score / static_cast<double>(nodeSuccessor.visits) +
              sqrt(2.0 * log(static_cast<double>(node.visits)) / static_cast<double>(nodeSuccessor.visits));
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::doActionOnBoard(const Node<CellT, PawnT> &nodeToGetTheActionFrom)
{
    game->play(nodeToGetTheActionFrom.move.pawn,
               nodeToGetTheActionFrom.move.target);
    // game->play(nodeToGetTheActionFrom.player,
    //            nodeToGetTheActionFrom.targetedCell);
}

template <class CellT, class PlayerT, class PawnT>
const game::Move<CellT, PawnT> MCTS<CellT, PlayerT, PawnT>::getRandomAvailableMoveFromBoard(const unsigned int &player_id) const
{
    std::vector<game::Move<CellT, PawnT>> cells = game->getAvailableMoves(game->board->getPlayerById(player_id));
    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    return cells[index];

    // std::vector<game::AbstractBoardCell *> cells = game->board->getAvailableCells();
    // // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    // if (cells.size() == 0)
    //     throw - 1;
    // unsigned int index = rand() % cells.size();

    // return cells[index];
}

template <class CellT, class PlayerT, class PawnT>
void MCTS<CellT, PlayerT, PawnT>::backPropagateAndRevertAction(int winnerId, Node<CellT, PawnT> *terminalNode)
{
    Node<CellT, PawnT> *node = terminalNode;

    // iterate until the root node, not excluded tho!
    do
    {
        node->visits++;
        if (!node->isRoot)
        {
            double increment = INCREMENT_DEFEAT;
            if (static_cast<int>(node->move.pawn->getOwner()->getId()) == winnerId)
            { // victory
                increment = INCREMENT_VICTORY;
            }
            else if (winnerId == -1)
            { // draw
                increment = INCREMENT_DRAW;
            }
            node->score += increment;

            if (node->parent)
            { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
                game->revertPlay();
            }
        }

    } while ((node = node->parent) != nullptr);

    // Node<CellT, PawnT> *node = terminalNode;

    // // iterate until the root node, not excluded tho!
    // do
    // {
    //     double increment = INCREMENT_DEFEAT;
    //     if ((int)node->player->getId() == winnerId)
    //     { // victory
    //         increment = INCREMENT_VICTORY;
    //     }
    //     else if (winnerId == -1)
    //     { // draw
    //         increment = INCREMENT_DRAW;
    //     }
    //     node->visits++;

    //     node->score += increment;
    //     if (node->parent)
    //     { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
    //         game->revertPlay(node->targetedCell);
    //     }

    // } while ((node = node->parent) != nullptr);
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *MCTS<CellT, PlayerT, PawnT>::randomChooseChildOrFallbackOnNode(Node<CellT, PawnT> *node) const
{
    Node<CellT, PawnT> *ret = node;
    if (node->childNodes.size() != 0)
    {
        unsigned int index = rand() % node->childNodes.size();
        ret = node->childNodes[index];
    }

    return ret;
}

template <class CellT, class PlayerT, class PawnT>
int MCTS<CellT, PlayerT, PawnT>::randomSimulation() const
{
    size_t number_games_played = 0;
    while (!game->isFinished())
    {
        const game::Move<CellT, PawnT> move = getRandomAvailableMoveFromBoard(game->getPlayerToPlay());
        game->play(
            move.pawn,
            move.target);
        ++number_games_played;
    }

    // check the victory
    int winner = game->checkStatus();

    // revert the random game
    while (number_games_played-- > 0)
    {
        game->revertPlay();
    }

    return winner;

    // // save the actions done so we can revert them;
    // std::queue<game::AbstractBoardCell *> playedCells;

    // while (!game->isFinished())
    // {
    //     try
    //     {
    //         game::AbstractBoardCell *cell = getRandomAvailableCellFromBoard();
    //         game->play(
    //             game->getPlayerToPlay(),
    //             cell);
    //         playedCells.push(cell);
    //     }
    //     catch (int code)
    //     {
    //     }
    // }

    // // check the victory
    // int winner = game->checkStatus();

    // // revert the random game
    // while (!playedCells.empty())
    // {
    //     game->revertPlay(playedCells.front());
    //     // remove the element
    //     playedCells.pop();
    // }

    // return winner;
}

template <class CellT, class PlayerT, class PawnT>
Node<CellT, PawnT> *MCTS<CellT, PlayerT, PawnT>::selectBestChildAndDoAction(Node<CellT, PawnT> *input)
{
    Node<CellT, PawnT> *ret = input;

    if (!ret->isRoot)
    {
        doActionOnBoard(*ret);
    }

    while (ret->childNodes.size() != 0)
    {
        Node<CellT, PawnT> *interestingToReturn = nullptr;
        double interestingValue = std::numeric_limits<double>::lowest();

        // One child must be selected to further develop
        for (Node<CellT, PawnT> *node : ret->childNodes)
        {
            double res = formula(
                *ret,
                *node);

            if (res > interestingValue)
            {
                // update ret
                interestingValue = res;
                interestingToReturn = node;
            }
        }

        // exclude the root node that doesn't have any action associated...
        if (!interestingToReturn->isRoot)
        {
            doActionOnBoard(*interestingToReturn);
        }
        ret = interestingToReturn;
    }

    return ret;
}

template class MCTS<game::tic_tac_toe::BoardCell, game::tic_tac_toe::Player, game::tic_tac_toe::Player>;
template class MCTS<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn>;

} // namespace mcts