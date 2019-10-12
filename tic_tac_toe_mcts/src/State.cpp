#include "State.hpp"

namespace mcts
{
State::State()
{
    _board = std::make_shared<game::Board>();
}

State::State(std::shared_ptr<game::Board> board)
{
    _board = board;
}

std::list<State> getAllPossibleStates()
{
    
}

} // namespace mcts