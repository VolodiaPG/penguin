#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace mcts
{
class Position
{
public:
    /**
         * @brief X coordinate in a 2D plane
         * 
         */
    int x = 0;
    /**
         * @brief Y coordinate in a 2D plane
         * 
         */
    int y = 0;

    Position();
    Position(int x, int y);
};
} // namespace mcts

#endif