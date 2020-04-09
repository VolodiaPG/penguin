#include "conversions.hpp"

namespace game
{
Position3D hex_axial_to_cube(const Position &position)
{
    Position3D ret;
    ret.x = position.x;
    ret.z = position.y;
    ret.y = -ret.x - ret.z;
    return ret;
}

Position hex_cube_to_axial(const Position3D &position)
{
    Position ret;
    ret.x = position.x;
    ret.y = position.z;
    return ret;
}

Position hex_cube_to_offset(const Position3D &position)
{
    Position ret;
    ret.x = position.x + (position.z - (position.z&1))/2;
    ret.y = position.z;
    return ret;
}
} // namespace game