#ifndef GAME_HHISTORY_HPP_
#define GAME_HHISTORY_HPP_

#include <stack>
#include "utils/Move.hpp"

namespace game
{

template <class CellT, class PawnT>
class History final
{
private:
    std::stack<Move<CellT, PawnT>> _stack;

public:
    /**
     * @brief Construct a new History object
     * 
     */
    History();

    void enqueue(const Move<CellT, PawnT>& move);

    const Move<CellT, PawnT> dequeue();

    const Move<CellT, PawnT> &top() const;

    size_t size() const;
};
} // namespace game

#endif