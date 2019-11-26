#ifndef JS_PLAYER_HPP_
#define JS_PLAYER_HPP_

#include <iostream>
#include "AbstractPlayer.hpp"

namespace game
{

class JSPlayer : public AbstractPlayer
{
public:
    typedef Position (*action_callback)(unsigned int id);
    /**
     * @brief Callback type definition
     * 
     */

protected:
    action_callback callback;

public:
    explicit JSPlayer(unsigned int id, action_callback callback);
    AbstractBoardCell *action(AbstractBoard *board) override;
};
} // namespace game

#endif