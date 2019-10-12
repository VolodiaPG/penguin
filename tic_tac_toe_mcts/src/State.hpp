#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>
#include <list>

#include "Board.hpp"

namespace mcts
{
class State
{
private:
    std::shared_ptr<game::Board> _board;
    int _playerNo = 0;
    int _visitCount = 0;
    double _winScore = 0;

public:
    State();
    State(std::shared_ptr<game::Board> board);

    std::list<State> getAllPossibleStates();
    void randomPlay();
};
} // namespace mcts

#endif /*STATE_HPP_*/
