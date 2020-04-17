#include "Tree.hpp"

namespace mcts
{

Tree::Tree(
    game::AbstractGame *game,
    game::AbstractPlayer *me,
    const MCTSConstraints &constraints)
    : playerMe(me),
      game(game),
      constraints(constraints)
{
    rootNode.player = playerMe;
    rootNode.isRoot = true;
}

Tree::~Tree()
{
}

void Tree::begin()
{
    
}

game::AbstractBoardCell *Tree::bestMove() const
{
    return nodeWithMaxVisits(&rootNode)->targetedCell;
}

Node *Tree::nodeWithMaxVisits(const Node *nodeFrom) const
{
    Node *chosen = nullptr;
    int max = -1;

    for (Node *node : nodeFrom->childNodes)
    {
        if (node->visits > max)
        {
            max = node->visits;
            chosen = node;
        }
    }

    return chosen;
}

void Tree::moveRootToCell(game::AbstractBoardCell* cell)
{
    Node* nextRoot = nullptr;
    
    while(rootNode.childNodes.size() != 0)
    {
        Node* n = rootNode.childNodes.back();
        rootNode.childNodes.pop_back();
        if(n->targetedCell == cell)
        {
            nextRoot = n;
        }else
        {
            delete n;
        }
    }

    if(nextRoot != nullptr)
    {
        rootNode = *nextRoot;
        rootNode.parent = nullptr;
        rootNode.targetedCell = nullptr;
        rootNode.isRoot = true;
        for(unsigned long i = 0; i < rootNode.childNodes.size(); i++)
        {
            rootNode.childNodes.at(i)->parent = &rootNode;
        }
    }
}

Node* Tree::getRootNode() { return &rootNode; }

} // namespace mcts