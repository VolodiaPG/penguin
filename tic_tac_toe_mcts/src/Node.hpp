#ifndef NODE_HPP_
#define NODE_HPP_

#include <list>
#include <iostream>
#include <iterator>
#include <memory>

namespace mcts
{
class Node
{
protected:
    std::list<Node> childNodes;
    Node const *parentNode;

public:
    void selection();
    void expansion();
    void simulation();
    void backpropagation();
};
} // namespace mcts

#endif /*NODE_HPP_*/
