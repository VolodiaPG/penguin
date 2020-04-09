#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>
#include "Board.hpp"
#include "PrintHex.hpp"
#include "BoardCell.hpp"
#include "Position.hpp"
#include "HumanPlayer.hpp"
#include "PenguinPlayer.hpp"
#include "PenguinGame.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_penguin_bind)
{
    class_<HumanPlayer>("HumanPlayer")
        .function("getScore", &HumanPlayer::getScore);

    class_<PenguinPlayer>("PenguinPlayer")
        .function("getStandingOn", &PenguinPlayer::getStandingOn, allow_raw_pointers())
        .function("getPreviousStandingOn", &PenguinPlayer::getPreviousStandingOn, allow_raw_pointers())
        .function("getOwner", &PenguinPlayer::getOwner, allow_raw_pointers());

    class_<BoardCell>("BoardCell")
        .function("getPosition", &BoardCell::getPosition)
        .function("isGone", &BoardCell::isGone)
        .function("getOwner", &BoardCell::getOwner, allow_raw_pointers())
        .function("isOwned", &BoardCell::isOwned)
        .function("getFish", &BoardCell::getFish);

    class_<Board>("Board")
        .function("performMove", &Board::performMove, allow_raw_pointers())
        .function("revertMove", &Board::revertMove, allow_raw_pointers())
        .function("checkStatus", &Board::checkStatus)
        .function("getAvailableCells", &Board::getAvailableCells, allow_raw_pointers())
        .function("getBoardCells", &Board::getBoardCells, allow_raw_pointers())
        .function("size", &Board::size)
        .function("getCell", &Board::getCell, allow_raw_pointers())
        .function("getPlayersOnBoard", &Board::getPlayersOnBoard, allow_raw_pointers())
        .function("getPlayerById", &Board::getPlayerById, allow_raw_pointers());

    class_<PrintHex>("PrintHexASCII")
        .constructor<size_t>()
        .function("print", &PrintHex::print);

    class_<PenguinGame>("PenguinGame")
        .constructor<const size_t, const size_t>()
        .function("isFinished", &PenguinGame::isFinished)
        .function("play", &PenguinGame::play, allow_raw_pointers())
        .function("revertPlay", &PenguinGame::revertPlay, allow_raw_pointers())
        .function("getPlayerToPlay", &PenguinGame::getPlayerToPlay)
        .function("checkStatus", &PenguinGame::checkStatus);
}
} // namespace penguin
} // namespace game

#endif
#endif