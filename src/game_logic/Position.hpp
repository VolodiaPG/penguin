#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <stdlib.h>
#include <unordered_map>

namespace game
{
struct Position
{
     int x = 0;
     int y = 0;

     /**
      * @brief Comparaison operator, first used in order to provide a collision escape in an unordered_map
      * 
      */
     bool operator==(const Position &position) const
     {
          return x == position.x && y == position.y;
     }
};

/**
 * @brief Proper hash function specialized for Position
 * 
 */
struct position_hash_function
{

     std::size_t operator()(const Position &position) const
     {
          std::size_t h_x = std::hash<unsigned int>()(position.x);
          std::size_t h_y = std::hash<unsigned int>()(position.y);
          return h_x ^ h_y;
     }
};

} // namespace game

#endif
