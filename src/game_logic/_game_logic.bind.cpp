// #define __EMSCRIPTEN__
#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "AbstractBoard.hpp"
#include "AbstractBoardCell.hpp"
#include "AbstractPawn.hpp"
#include "AbstractPlayer.hpp"
#include "AbstractGame.hpp"

#include "penguin/BoardCell.hpp"
#include "penguin/HumanPlayer.hpp"
#include "penguin/PenguinPawn.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_bind)
{
#define __GAME_LOGIC_BIND__(name_prefix, AbstractBoard, AbstractGame, AbstractPawn)             \
                                                                                                \
    class_<AbstractBoard>(name_prefix "_AbstractBoard")                                         \
        .function("performMove", &AbstractBoard::performMove, allow_raw_pointers())             \
        .function("revertMove", &AbstractBoard::revertMove)                                     \
        .function("checkStatus", &AbstractBoard::checkStatus)                                   \
        .function("getAvailableCells", &AbstractBoard::getAvailableCells, allow_raw_pointers()) \
        .function("getBoardCells", &AbstractBoard::getBoardCells, allow_raw_pointers())         \
        .function("size", &AbstractBoard::size)                                                 \
        .function("getCell", &AbstractBoard::getCell, allow_raw_pointers())                     \
        .function("getPawnsOnBoard", &AbstractBoard::getPawnsOnBoard, allow_raw_pointers())     \
        .function("getPawnById", &AbstractBoard::getPawnById, allow_raw_pointers())             \
        .function("getPlayerById", &AbstractBoard::getPlayerById, allow_raw_pointers());        \
                                                                                                \
    class_<AbstractGame>(name_prefix "_AbstractGame")                                           \
        .function("isFinished", &AbstractGame::isFinished)                                      \
        .function("play", &AbstractGame::play, allow_raw_pointers())                            \
        .function("revertPlay", &AbstractGame::revertPlay)                                      \
        .function("getPlayerToPlay", &AbstractGame::getPlayerToPlay)                            \
        .function("checkStatus", &AbstractGame::checkStatus);                                   \
                                                                                                \
    class_<AbstractPlayer>(name_prefix "_AbstractPlayer")                                       \
        .function("getId", &AbstractPlayer::getId);                                             \
                                                                                                \
    class_<AbstractPawn>(name_prefix "_AbstractPawn")                                           \
        .function("getOwner", &AbstractPawn::getOwner)                                          \
        .function("getId", &AbstractPawn::getId);

    typedef AbstractBoard<penguin::BoardCell, penguin::HumanPlayer, penguin::PenguinPawn> penguin_board_t;
    typedef AbstractGame<penguin::BoardCell, penguin::HumanPlayer, penguin::PenguinPawn> penguin_game_t;
    typedef AbstractPawn<penguin::HumanPlayer, penguin::BoardCell> penguin_pawn_t;
    __GAME_LOGIC_BIND__("penguin", penguin_board_t, penguin_game_t, penguin_pawn_t)
}
} // namespace penguin
} // namespace game

#endif
#endif