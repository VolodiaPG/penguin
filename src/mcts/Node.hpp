#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <stack>
#include <iostream>
#include <math.h>
#include <limits>

#include "Tree.hpp"
#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/AbstractPlayer.hpp"
#include "../game_logic/Move.hpp"

#include "../dbg.h"
#include "../game_logic/penguin/BoardCell.hpp"

#include "../log.hpp"

namespace game
{
template <class CellT, class PlayerT, class PawnT>
class AbstractGame;
}

namespace mcts
{

class Node
{
protected:
    /**
     * @brief Nodes, lifetime tied to the parent object
     * 
     */
    std::vector<Node *> childNodes;
    Node *parent = nullptr;
    game::Move _move;
    game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game = nullptr;

    static double formula(int winsSuccessor, int numberVisitsSuccessor, int numberVisitsFather);

    Node *selectPromisingNode() const;

public:
    int victories = 0;
    int visits = 0;

    explicit Node(
        Node *parent,
        game::Move move,
        game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game);
    ~Node();

    bool doAction();

    void revertAction();

    Node *selectBestChildAndDoAction();

    Node *nodeWithMaxVisits() const;

    // void expandNode(std::vector<game::Move> possibleMove, game::AbstractPlayer *nextPlayer);
    void expandNode(std::vector<game::Move> possibleMove);

    // unsigned int getPlayerID() const { return _move_associated.pawn->getOwner()->getId(); };

    Node *getParent() const { return parent; };

    game::AbstractBoardCell *getTargetedCell() const { return _move.target; };

    static game::Move getRandomAvailableMove(
        game::AbstractGame<game::AbstractBoardCell, game::AbstractPlayer, game::AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell>> *game,
        unsigned int player_id);

    int randomSimulation() const;

    Node *randomChooseChildOrDefaultMe();

    void backPropagateAndRevertAction(const int winnerId);

    game::Move getMove() const { return _move; };
};
} // namespace mcts

#endif /*NODE_HPP_*/
