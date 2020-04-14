#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>
#include "Position.hpp"
#include "Position3D.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_bind)
{
    // TODO add Position, PenguinPlayer

    value_object<Position>("Position")
        .field("x", &Position::x)
        .field("y", &Position::y);

    value_object<Position3D>("Position3D")
        .field("x", &Position3D::x)
        .field("y", &Position3D::y)
        .field("z", &Position3D::z);
}
} // namespace penguin
} // namespace game

#endif
#endif