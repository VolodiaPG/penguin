#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "../penguin/BoardCell.hpp"
#include "../penguin/PenguinPawn.hpp"

#include "Position.hpp"
#include "Position3D.hpp"
#include "conversions.hpp"
#include "Move.hpp"
namespace game
{

using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_utils_bind)
{
    value_object<Position>("Position")
        .field("column", &Position::x) //To make the link with the frontend implementation
        .field("row", &Position::y);

    value_object<Position3D>("Position3D")
        .field("x", &Position3D::x)
        .field("y", &Position3D::y)
        .field("z", &Position3D::z);

    function("hex_axial_to_cube", &hex_axial_to_cube);
    function("hex_cube_to_axial", &hex_axial_to_cube);
    function("hex_cube_to_offset", &hex_cube_to_offset);

#define __GAME_LOGIC_UTILS_BIND__(name_prefix, BoardCell, Pawn)                                   \
    typedef Move<BoardCell, Pawn> Move;                                                           \
                                                                                                  \
    class_<Move>(name_prefix "_Move")                                                             \
        .constructor(&Move::generateMove, allow_raw_pointers()) \
        .function("getPawn", &Move::getPawn, allow_raw_pointers())                                \
        .function("setPawn", &Move::setPawn, allow_raw_pointers())                                \
        .function("getTarget", &Move::getTarget, allow_raw_pointers())                            \
        .function("setTarget", &Move::setTarget, allow_raw_pointers())                            \
        .function("getFrom", &Move::getFrom, allow_raw_pointers())                                \
        .function("setFrom", &Move::setFrom, allow_raw_pointers())

    typedef penguin::BoardCell testa;
    typedef penguin::PenguinPawn testb;

    __GAME_LOGIC_UTILS_BIND__("penguin", testa, testb);
}

} // namespace game

#endif
#endif