#include "node.hpp"

Node::~Node()
{
    for(Node * child : children)
    {
        delete child;
    }
}

Node::Node(Board * t_board, int t_player)
{
    board = t_board;
    player = t_player;
}

Node::Node(Board * t_board, int t_player, Node * t_parent, int t_movePosition)
{
    board = t_board;
    player = t_player;
    parent = t_parent;
    movePosition = t_movePosition;
}

int Node::getPlayer()
{
    return player;
}

Node * Node::getParent()
{
   return parent;
}

int Node::getChildrenSize()
{
    return children.size();
}

std::vector<Node *> * Node::getChildren()
{
    return &children;
}

Node * Node::getBestChildByUct()
{
    double maxValue = -10000;
    Node * bestChild = nullptr;
    for(Node * child : children)
    {
        if(child->isVisited() == false)
        {
            int parentVisitCount = visitCount;
            int childVisitCount = child->visitCount;
            int childWinCount = child->winCount;
            double valueOfChild = uctValue(parentVisitCount, childWinCount, childVisitCount);
            if(valueOfChild > maxValue)
            {
                maxValue = valueOfChild;
                bestChild = child;
            }
        }
    }
    return bestChild;
}

Node * Node::getBestChildByValue()
{
    double maxValue = -10000;
    Node * bestChild = nullptr;
    for(Node * child : children)
    {
        int childVisitCount = child->visitCount;
        int childWinCount = child->getWinCount();
        //double score = (double)childWinCount/(double)childVisitCount;
        double score = (double)childVisitCount;
        if(score > maxValue)
        {
            maxValue = score;
            bestChild = child;
        }
    }
    return bestChild;
}

Node * Node::getBestChildByValueBis()
{
    double maxValue = -10000;
    Node * bestChild = nullptr;
    for(Node * child : children)
    {
        int childVisitCount = child->visitCount;
        int childWinCount = child->getWinCount();
        double score = (double)childWinCount/(double)childVisitCount;
        //double score = (double)childVisitCount;
        if(score > maxValue)
        {
            maxValue = score;
            bestChild = child;
        }
    }
    return bestChild;
}

Node * Node::getRandomChild()
{
    int randomIndex = rand() % children.size();
    Node * child = children.at(randomIndex);
    return child;
}

void Node::generateChildren()
{
    putSequence();
    std::vector<int> possiblePositions = board->getPossiblePositions();
    //int newPlayer = (player + 1)%2;
    int newPlayer = player;
    for(int i : possiblePositions)
    {

        Node * newNode = new Node(board, newPlayer, this, i);
        board->play(i);
        //board->show();
        //std::cout<<board->getResult()<<std::endl;
        //std::cout<<std::endl;
        newNode->status = board->getResult();
        //board->show();
        //std::cout<<newNode->status<<std::endl;
        board->removePlayer(i);
        children.push_back(newNode);
    }
    removeSequence();
}

int Node::randomMove()
{
    std::vector<int> possiblePositions = board->getPossiblePositions();
    int randomIndex = rand() % possiblePositions.size();
    int randomMove = possiblePositions.at(randomIndex);
    return randomMove;
}

int Node::doRandomPlayout()
{
    putSequence();
    std::vector<int> moves;
    while(board->status() == IN_PROGRESS)
    {
        int rM = randomMove();
        board->play(rM);
        moves.push_back(rM);
    }
    //board->show();
    int result = board->getResult();
    for(int i = moves.size() - 1; i >= 0; i --)
    {
        board->removePlayer(moves.at(i));
    }
    removeSequence();
    return result;
}

void Node::putSequence()
{
    std::vector<int> sequence = getSequence();
    for(int i = sequence.size() - 1; i >= 0; i--)
    {
        int position = sequence.at(i);
        board->play(position);
    }
}

void Node::removeSequence()
{
    std::vector<int> sequence = getSequence();
    for(unsigned int i = 0; i < sequence.size(); i++)
    {
        int position = sequence.at(i);
        board->removePlayer(position);
    }
}

std::vector<int> Node::getSequence()
{
    std::vector<int> sequence;
    Node * ptr_Node = this;
    while(ptr_Node->getParent() != nullptr)
    {
        int position = ptr_Node->getMovePosition();
        sequence.push_back(position);
        ptr_Node = ptr_Node->getParent();
    }
    return sequence;
}

int Node::getWinCount()
{
    return winCount;
}

int Node::getVisitCount()
{
    return visitCount;
}

void Node::incrVisitCount(int qte)
{
    visitCount+=qte;
}

void Node::incrWinCount(int qte)
{
    winCount+=qte;
}

int Node::getMovePosition()
{
    return movePosition;
}

int Node::getStatus()
{
    return status;
}

void Node::setVisited(bool val)
{
    visited = val;
}

bool Node::isVisited()
{
    return visited;
}
