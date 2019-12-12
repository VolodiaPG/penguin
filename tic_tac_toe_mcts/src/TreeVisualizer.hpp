#ifndef TREE_VISUALIZER_HPP_
#define TREE_VISUALIZER_HPP_

#include <iostream>
#include <fstream>
#include "Tree.hpp"
#include "BoardCell.hpp"

namespace mcts
{
class Tree;

class TreeVisualizer
{
private:
    void printTree(
        const Node *node,
        std::ofstream &flux,
        int zindex);

protected:
    const Tree *tree;
    const int cutAfter;
    const std::string filename;

public:
    explicit TreeVisualizer(
        const Tree *tree,
        int cutAfter,
        const std::string &filename);
    void exportLog();
};

} // namespace mcts

#endif