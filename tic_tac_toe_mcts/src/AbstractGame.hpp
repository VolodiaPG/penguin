#ifndef ABSTRACT_GAME_HPP_
#define ABSTRACT_GAME_HPP_

#include "AbstractInterface.hpp"
#include "AbstractPlayer.hpp"

namespace game
{
class AbstractGame : public AbstractInterface
{

public:
    void play(const AbstractPlayer &player);
    virtual void launch();
    void loop();
};
} // namespace game

#endif