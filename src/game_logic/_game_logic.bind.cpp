#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "AbstractBoard.hpp"
#include "AbstractBoardCell.hpp"
#include "AbstractPawn.hpp"
#include "AbstractPlayer.hpp"
#include "AbstractGame.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_bind)
{
    using AbstractBoard = AbstractBoard<AbstractBoardCell, AbstractPlayer, AbstractPawn<AbstractPlayer, AbstractBoardCell>>;
    using AbstractGame = AbstractGame<AbstractBoardCell, AbstractPlayer, AbstractPawn<AbstractPlayer, AbstractBoardCell>>;
    using AbstractPawn = AbstractPawn<AbstractPlayer, AbstractBoardCell>;
    
    class_<AbstractBoard>("AbstractBoard")
        .function("performMove", &AbstractBoard::performMove, allow_raw_pointers())
        .function("revertMove", &AbstractBoard::revertMove, allow_raw_pointers())
        .function("checkStatus", &AbstractBoard::checkStatus)
        .function("getAvailableCells", &AbstractBoard::getAvailableCells, allow_raw_pointers())
        .function("getBoardCells", &AbstractBoard::getBoardCells, allow_raw_pointers())
        .function("size", &AbstractBoard::size)
        .function("getCell", &AbstractBoard::getCell, allow_raw_pointers())
        .function("getPawnsOnBoard", &AbstractBoard::getPawnsOnBoard, allow_raw_pointers())
        .function("getPawnById", &AbstractBoard::getPawnById, allow_raw_pointers())
        .function("getPlayerById", &AbstractBoard::getPlayerById, allow_raw_pointers());

    class_<AbstractGame>("AbstractGame")
        .function("isFinished", &AbstractGame::isFinished)
        .function("play", &AbstractGame::play, allow_raw_pointers())
        .function("revertPlay", &AbstractGame::revertPlay)
        .function("getPlayerToPlay", &AbstractGame::getPlayerToPlay)
        .function("checkStatus", &AbstractGame::checkStatus);

    class_<AbstractPlayer>("AbstractPlayer")
        .function("getId", &AbstractPlayer::getId);

    class_<AbstractPawn>("AbstractPawn")
        .function("getId", &AbstractPawn::getId);
}
} // namespace penguin
} // namespace game

#endif
#endif