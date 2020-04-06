#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>
#include "Board.hpp"
#include "PrintHex.hpp"
#include "BoardCell.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_penguin_bind)
{
    // TODO add Position, PenguinPlayer
    class_<BoardCell>("BoardCell")
        .constructor<const Position, int>()
        .function("getPosition", &BoardCell::getPosition)
        .function("isGone", &BoardCell::isGone)
        .function("getOwner", &BoardCell::getOwner)
        .function("isOwned", &BoardCell::isOwned)
        .function("getFish", &BoardCell::getFish)
    
    class_<Board>("Board")
        .constructor<const size_t, const int>()
        .function("performMove", &Board::performMove, allow_raw_pointers())
        .function("revertMove", &Board::revertMove, allow_raw_pointers())
        .function("checkStatus", &Board::checkStatus)
        .function("getAvailableCells", &Board::getAvailableCells,allow_raw_pointers())
        .function("getBoardCells", &Board::getBoardCells, allow_raw_pointers())
        .function("size", &Board::size)
        .function("getCell", &Board::getCell, allow_raw_pointers())
        .function("getPlayersOnBoard", &Board::getPlayersOnBoard, allow_raw_pointers())
        .function("getPlayerById", &Board::getPlayerById, allow_raw_pointers());

    class_<PrintHex>("PrintHexASCII")
        .constructor<size_t>()
        .function("print", &PrintHex::print);
}
} // namespace penguin
} // namespace game

#endif
#endif