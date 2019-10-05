#include "Node.hpp"

namespace mcts
{

Node::Node(std::shared_ptr <Node> parent)
{
    _parent = std::move(parent);
}

Node::~Node()
{
}

const State &Node::getState()
{
    return *_state;
}

void Node::setState(std::shared_ptr <State> state)
{
    _state = std::move(state);
}

const Node &Node::getParent()
{
    return *_parent;
}

void Node::setParent(std::shared_ptr <Node> parent)
{
    _parent = std::move(parent);
}

const std::list<std::shared_ptr <Node>> Node::getChildList()
{
    return _childList;
}
} // namespace tree