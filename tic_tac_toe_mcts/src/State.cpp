#include "State.hpp"

namespace mcts
{
State::State()
{
    _board = std::make_shared<Board>();
}

State::State(std::shared_ptr<Board> board)
{
    _board = board;
}

std::list<State> getAllPossibleStates()
{
    
}

} // namespace mcts