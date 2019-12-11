#ifndef NODE_HPP
#define NODE_HPP

#include <time.h>
#include <vector>
#include <random>
#include "board.hpp"
#include "uctfunction.hpp"


class Node
{
public:
    ~Node();
    Node(Board * t_board, int t_player);
    Node(Board * t_board, int t_player, Node * t_parent, int t_movePosition);

    int getPlayer();
    Node * getParent();
    int getChildrenSize();
    std::vector<Node *> * getChildren();
    Node * getBestChildByUct();
    Node * getBestChildByValue();
    Node * getBestChildByValueBis();
    Node * getRandomChild();
    void generateChildren();
    int randomMove();
    int doRandomPlayout();
    void putSequence();
    void removeSequence();
    std::vector<int> getSequence();
    int getWinCount();
    int getVisitCount();
    void incrVisitCount(int qte);
    void incrWinCount(int qte);
    int getMovePosition();
    int getStatus();
    void setVisited(bool val);
    bool isVisited();


private:
    int player;
    int movePosition = - 1;
    Board * board;
    Node * parent = nullptr;
    std::vector<Node *> children;
    int winCount = 0;
    int visitCount = 0;
    int status = IN_PROGRESS;
    bool visited = false;
};

#endif // NODE_HPP
