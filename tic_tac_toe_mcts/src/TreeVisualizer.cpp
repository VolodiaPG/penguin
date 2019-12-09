#include "TreeVisualizer.hpp"

namespace mcts
{
TreeVisualizer::TreeVisualizer(
    const Tree *tree,
    const std::string &filename)
    : tree(tree),
      filename(filename)
{
}

void TreeVisualizer::exportLog()
{
    //std::cout<<std::to_string(num)<<std::endl;
    std::ofstream flux(filename);
    if (flux)
    {
        const Node *node = &tree->rootNode;
        // std::cout << node->targetedCell->to_string() << std::endl;
        // flux << node->targetedCell->to_string() << ";";
        // if (node->childNodes.size() == 0)
        // {
        //     *flux << node->getMovePosition() << ";" << node->getWinCount() << ";" << node->getVisitCount() << ";" << node->isVisited() << std::endl;
        // }
        // else
        // {
        // }
        printTree(node, flux, 0);
    }
}

void TreeVisualizer::printTree(const Node *node, std::ofstream &flux, int zindex)
{
    if (node->targetedCell)
    {
        std::cout << node->targetedCell->to_string() << std::endl;
        flux << zindex << ";" << node->targetedCell->to_string() << ";" << node->score << ";" << node->visits << std::endl;
    }
    for (Node *child : node->childNodes)
    {
        printTree(child, flux, zindex + 1);
    }
}

} // namespace mcts