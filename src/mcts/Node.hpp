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

#include "../log.hpp"

namespace game
{
template <class PlayerT, class CellT>
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
    const unsigned int player_id;
    game::AbstractBoardCell *targetedCell = nullptr;
    game::AbstractGame<game::AbstractPlayer, game::AbstractBoardCell> *game = nullptr;

    static double formula(int winsSuccessor, int numberVisitsSuccessor, int numberVisitsFather);

    Node *selectPromisingNode() const;

public:
    int victories = 0;
    int visits = 0;

    explicit Node(
        Node *parent,
        const unsigned int player_id,
        game::AbstractBoardCell *targetedCell,
        game::AbstractGame<game::AbstractPlayer, game::AbstractBoardCell> *game);
    ~Node();

    bool doAction();

    void revertAction();

    Node *selectBestChildAndDoAction();

    Node *nodeWithMaxVisits() const;

    // void expandNode(std::vector<game::Move> possibleMove, game::AbstractPlayer *nextPlayer);
    void expandNode(std::vector<game::Move> possibleMove);

    unsigned int getPlayerID() const { return player_id; };

    Node *getParent() const { return parent; };

    game::AbstractBoardCell *getTargetedCell() const { return targetedCell; };

    game::AbstractBoardCell *getRandomAvailableCell() const;

    int randomSimulation() const;

    Node *randomChooseChildOrDefaultMe();

    void backPropagateAndRevertAction(const int winnerId);
};
} // namespace mcts

#endif /*NODE_HPP_*/
