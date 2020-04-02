#include "utils.hpp"

namespace game
{
Position3D hex_axial_to_cube(const Position &position)
{
    int x = position.x;
    int z = position.y;
    int y = -x - z;
    return Position3D{
        x,
        y,
        z};
}

Position hex_cube_to_axial(const Position3D &position)
{
    return Position{
        position.x,
        position.z};
}

Position hex_cube_to_offset(const Position3D &position)
{
    return Position{
        position.x + (position.z - (position.z&1))/2,
        position.z
    };
}
} // namespace game