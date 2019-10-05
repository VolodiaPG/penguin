#include "Tree.hpp"

namespace mcts
{
Tree::Tree(std::shared_ptr<Node> root)
{
    _root = std::move(root);
}

const Node &Tree::getRoot()
{
    return *_root;
}

void Tree::setRoot(std::shared_ptr<Node> root)
{
    _root = std::move(root);
}
} // namespace mcts