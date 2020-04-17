#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>
#include "Position.hpp"
#include "Position3D.hpp"
#include "conversions.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_utils_bind)
{
    value_object<Position>("Position")
        .field("x", &Position::x)
        .field("y", &Position::y);

    value_object<Position3D>("Position3D")
        .field("x", &Position3D::x)
        .field("y", &Position3D::y)
        .field("z", &Position3D::z);

    function("hex_axial_to_cube", &hex_axial_to_cube);
    function("hex_cube_to_axial", &hex_axial_to_cube);
    function("hex_cube_to_offset", &hex_cube_to_offset);
    
}
} // namespace penguin
} // namespace game

#endif
#endif