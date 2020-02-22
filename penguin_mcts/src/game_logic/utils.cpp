#include "utils.hpp"

namespace game
{
Position3D hex_axial_to_cube(const Position &position)
{
    return Position3D{
        position.x,
        position.y,
        -position.x - position.y};
}

Position hex_cube_to_axial(const Position3D &position)
{

    return Position{
        position.x,
        position.z};
}
} // namespace game