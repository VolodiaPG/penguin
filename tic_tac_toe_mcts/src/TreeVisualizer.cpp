#include "TreeVisualizer.hpp"

namespace mcts
{
TreeVisualizer::TreeVisualizer(
    const Tree *tree,
    int cutAfter,
    const std::string &filename)
    : tree(tree),
      cutAfter(cutAfter),
      filename(filename)
{
}

void TreeVisualizer::exportLog()
{
    //std::cout<<std::to_string(num)<<std::endl;
    std::ofstream flux(filename);
    if (flux)
    {        
        printTree(&tree->rootNode, flux, 0);
    }
}

void TreeVisualizer::printTree(const Node *node, std::ofstream &flux, int zindex)
{
    if (zindex > cutAfter)
        return;

    if (node->targetedCell)
    {
        flux << zindex << ";" << node->targetedCell->to_string() << ";" << node->score << ";" << node->visits << std::endl;
    }
    else
    {
        flux << zindex << ";" << 0 << ";" << node->score << ";" << node->visits << std::endl;
    }

    for (Node *child : node->childNodes)
    {
        printTree(child, flux, zindex + 1);
    }
}

} // namespace mcts