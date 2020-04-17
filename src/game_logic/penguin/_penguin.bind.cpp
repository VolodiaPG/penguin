#ifndef PENGUIN_BIND_CPP_
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "../AbstractBoard.hpp"
#include "../AbstractPawn.hpp"
#include "../AbstractPlayer.hpp"
#include "../AbstractGame.hpp"

#include "Board.hpp"
#include "PrintHex.hpp"
#include "BoardCell.hpp"
#include "Position.hpp"
#include "HumanPlayer.hpp"
#include "PenguinPawn.hpp"
#include "PenguinGame.hpp"

namespace game
{
namespace penguin
{
using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(game_logic_penguin_bind)
{
    using AbstractBoard = AbstractBoard<penguin::BoardCell, penguin::HumanPlayer, penguin::PenguinPawn>;
    using AbstractGame = AbstractGame<penguin::BoardCell, penguin::HumanPlayer, penguin::PenguinPawn>;
    using AbstractPawn = AbstractPawn<penguin::HumanPlayer, penguin::BoardCell>;

    register_vector<BoardCell *>("vector<BoardCell *>");
    register_vector<PenguinPawn *>("vector<PenguinPawn *>");

    class_<HumanPlayer, base<AbstractPlayer>>("HumanPlayer")
        .function("getScore", &HumanPlayer::getScore);

    class_<PenguinPawn, base<AbstractPawn>>("PenguinPawn");

    class_<BoardCell>("BoardCell")
        .function("getPosition", &BoardCell::getPosition)
        .function("isGone", &BoardCell::isGone)
        .function("getOwner", &BoardCell::getOwner, allow_raw_pointers())
        .function("isOwned", &BoardCell::isOwned)
        .function("getFish", &BoardCell::getFish);

    class_<Board, base<AbstractBoard>>("Board");

    class_<PrintHex>("PrintHex")
        .constructor<Board *>()
        .function("print", &PrintHex::print);

    class_<PenguinGame, base<AbstractGame>>("PenguinGame")
        .constructor<const size_t, const size_t>()
        .function("getBoard", &PenguinGame::getBoard, allow_raw_pointers())
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