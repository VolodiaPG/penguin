#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include "../Position.hpp"
#include "../Position3D.hpp"

namespace game
{
/**
 * @brief Converts an axial position to a cube position in an hexagonal grid
 * 
 * @param position the postion to be converted
 * @return Position3D the resulting position
 */
Position3D hex_axial_to_cube(const Position &position);
/**
 * @brief Converts position in a cube coordinate system to position in an axial system for a hexagonal grid
 * 
 * @param position the postion to be converted
 * @return Position3D the resulting position
 */
Position hex_cube_to_axial(const Position3D &position);

/**
 * @brief Converts a cube position in an offset system
 * 
 * @param position the position to be converted
 * @return Position the position, in an offset fashion
 */
Position hex_cube_to_offset(const Position3D &position);

} // namespace game

#endif