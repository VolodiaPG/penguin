#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>
#include "conversions.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_utils_bind)
{
    function("hex_axial_to_cube", &hex_axial_to_cube);
    function("hex_cube_to_axial", &hex_axial_to_cube);
    function("hex_cube_to_offset", &hex_cube_to_offset);
    
}
} // namespace penguin
} // namespace game

#endif
#endif