#ifndef TREE_HPP_
#define TREE_HPP_

#include <memory>

#include "Node.hpp"

namespace mcts
{
class Tree
{
private:
    std::shared_ptr<Node> _root;

public:
    /**
    * @brief Construct a new Tree object
    * 
    * @param root The root node
    */
    Tree(std::shared_ptr<Node> root);

    /**
    * @brief Get the Root object
    * 
    * @return const Node&
    */
    const Node &getRoot();
    /**
     * @brief Set the Root object
     * 
     * @param root 
     */
    void setRoot(std::shared_ptr<Node> root);
};

} // namespace mcts
#endif /*TREE_HPP_*/