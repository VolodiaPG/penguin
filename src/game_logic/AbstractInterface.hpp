#ifndef ABSTRACT_INTERFACE_HPP_
#define ABSTRACT_INTERFACE_HPP_

namespace game
{
class AbstractInterface
{
public:
    virtual ~AbstractInterface(){};
    virtual void draw() = 0;

};
} // namespace game

#endif