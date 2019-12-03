#ifndef TREE_VISUALIZER_HPP_
#define TREE_VISUALIZER_HPP_

#include <iostream>
#include "Tree.hpp"
#include "BoardCell.hpp"

namespace mcts
{
class Tree;

class TreeVisualizer
{
protected:
    const Tree *tree;

public:
    explicit TreeVisualizer(const Tree *tree);
    void visualizeBestPath();
};

} // namespace mcts

#endif