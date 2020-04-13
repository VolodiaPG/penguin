#ifndef MCTS_HPP
#define MCTS_HPP

#include "AbstractGame.hpp"
#include "Tree.hpp"

namespace mcts
{

class MCTS
{
public:
    explicit MCTS(game::AbstractGame *game,
         Tree* tree,
         const MCTSConstraints &constraints);
    ~MCTS();
    void begin();

protected:

    void backPropagateAndRevertAction(int winnerId, Node *terminalNode);

    game::AbstractBoardCell *getRandomAvailableCellFromBoard() const;

    double formula(
        const Node &node,
        const Node &nodeSuccessor) const;

    void doActionOnBoard(const Node &nodeToGetTheActionFrom);

    void expandNode();

    Node *selectBestChildAndDoAction(Node *node);

    Node *randomChooseChildOrFallbackOnNode(Node *node) const;

    int randomSimulation() const;

    void expandNode(Node *nodeToExpand);

private:
    MCTSConstraints constraints;
    game::AbstractGame* game;
    Tree* tree;
    Node* root;
};

}
#endif