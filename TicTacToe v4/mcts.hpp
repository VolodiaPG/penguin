#ifndef MCTS_HPP
#define MCTS_HPP

#include "board.hpp"
#include "node.hpp"
#include <fstream>
#include <iostream>

class Mcts
{
public:
    Mcts(Board * b, int p);
    int findNextMove();
    Node * selectPromisingNode(Node * rootNode);
    void backpropagate(int result, Node * node);
    void showTree(Node * node);
    void showTree(Node * node, int pos);
    void printTree(Node * node, int num);
    void printTree(Node * node, int pos, std::ofstream * flux);

private:
    Board * board;
    int player;
};

#endif // MCTS_HPP
