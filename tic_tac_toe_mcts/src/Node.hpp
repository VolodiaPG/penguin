#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <stack>
#include <iostream>
#include <math.h>
#include <limits>
#include "RandomPlayer.hpp"
#include "DefinedPlayer.hpp"
#include "Tree.hpp"
#include "AbstractBoardCell.hpp"

#include "log.hpp"
#include "BoardCell.hpp"

namespace game
{
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
    game::AbstractPlayer *player = nullptr;
    game::AbstractBoardCell *targetedCell = nullptr;

    static double formula(int winsSuccessor, int numberVisitsSuccessor, int numberVisitsFather);

    Node *selectPromisingNode() const;

public:
    int victories = 0;
    int visits = 0;

    explicit Node(Node *parent, game::AbstractPlayer *player, game::AbstractBoardCell *targetedCell);
    ~Node();

    bool doAction(game::AbstractBoard *board);

    void revertAction(game::AbstractBoard *board);

    Node *selectBestChildAndDoAction(game::AbstractBoard *board);

    Node *nodeWithMaxVisits() const;

    void expandNode(std::vector<game::AbstractBoardCell *> possibleMove, game::AbstractPlayer *nextPlayer);

    game::AbstractPlayer *getPlayer() const { return player; };
    
    Node *getParent() const { return parent; };

    game::AbstractBoardCell *getTargetedCell() const { return targetedCell; };

    int randomSimulation(game::AbstractGame *game) const;

    Node* randomChooseChildOrDefaultMe();

    void backPropagateAndRevertAction(const int winnerId, game::AbstractBoard *board);
};
} // namespace mcts

#endif /*NODE_HPP_*/
