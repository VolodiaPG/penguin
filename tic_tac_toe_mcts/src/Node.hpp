#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <stack>
#include <iostream>
#include <math.h>
#include "RandomPlayer.hpp"
#include "DefinedPlayer.hpp"
#include "Tree.hpp"
#include "AbstractBoardCell.hpp"

namespace mcts
{

class Tree;

typedef struct
{
    game::AbstractBoardCell *myAction = nullptr;
    // game::AbstractPlayer *associatedPlayer = nullptr;
} State;

class Node
{
private:
    int totalVictories = 0;
    int totalScenarii = 0;

protected:
    /**
     * @brief Nodes, lifetime tied to the parent object
     * 
     */
    std::vector<Node *> childNodes;
    Node *parentNode;
    Tree *tree;
    State state;

    inline static double formula(int winsSuccessor, int numberVisitsSuccessor, int numberVisitsFather);
    void executeMyAction();

public:
    explicit Node(Tree *tree, Node *parent, const State &state);
    ~Node();

    /**
     * @brief execute the MCTS
     * 
     */
    void execute();

    void selection();
    void expansion();
    void simulation();
    void backpropagation(bool victoryOnRandomPlay);

    State getState() const { return state; };

    const Node *nodeWithMaxVictories() const;
};
} // namespace mcts

#endif /*NODE_HPP_*/
