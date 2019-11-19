#include "TreeVisualizer.hpp"

namespace mcts
{
TreeVisualizer::TreeVisualizer(const Tree *tree)
    : tree(tree)
{
}

void TreeVisualizer::visualizeBestPath()
{
    const Node *node = tree->getRootNode();
    // while we didn't reach max depth
    while ((node = node->nodeWithMaxVisits()))
    {
        int player = ((game::BoardCell *)node->getState().myAction)->getValue();
        game::Position pos = ((game::BoardCell *)node->getState().myAction)->getPosition();
        std::cout << "Playing #" << player << " at: (" << pos.x << ", " << pos.y << ")" << std::endl;
    }
}
} // namespace mcts