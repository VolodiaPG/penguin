#ifndef NODE_HPP_
#define NODE_HPP_

#include <list>
#include <iostream>
#include <iterator>
#include <memory>

#include "State.hpp"

namespace mcts
{
class Node
{

private:
    std::shared_ptr <State> _state;
    std::shared_ptr <Node> _parent;

    std::list<std::shared_ptr <Node>> _childList;

public:
    Node(std::shared_ptr <Node> parent);
    ~Node();

    const State &getState();
    void setState(std::shared_ptr <State> state);

    const Node &getParent();
    void setParent(std::shared_ptr <Node> parent);

    const std::list<std::shared_ptr<Node>> getChildList();
};
} // namespace tree

#endif /*NODE_HPP_*/
