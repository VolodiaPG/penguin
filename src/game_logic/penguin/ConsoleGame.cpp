#include <iostream>

#include "../../mcts/MCTSPlayer.hpp"
#include "../AbstractGame.hpp"
#include "Board.hpp"
#include "PenguinGame.hpp"
#include "PenguinPawn.hpp"
#include "PrintHex.hpp"

#include "ConsoleGame.hpp"

namespace game
{
namespace penguin
{
ConsoleGame::ConsoleGame(const bool &no_print)
    : _game(7, 2),
      _print_hex(static_cast<Board *>(_game.board)),
      _no_print(no_print)
{
    Board *board = static_cast<Board *>(_game.board);

    // Placing all the penguins
    // team 1
    board->performMove(board->getPawnById(0), board->getCell(0, 0));
    board->performMove(board->getPawnById(1), board->getCell(3, 6));
    // team 2
    board->performMove(board->getPawnById(2), board->getCell(-3, 6));
    board->performMove(board->getPawnById(3), board->getCell(6, 0));
}

ConsoleGame::~ConsoleGame()
{
}

void ConsoleGame::draw()
{
    if (!_no_print)
    {
        _print_hex.print();
    }
}

void ConsoleGame::loop()
{
    if (!_no_print)
    {
        std::cout << "Looping, wheeeeeeeeee" << std::endl;
    }

    mcts::MCTSConstraints constraints;
    constraints.time = 250;

    mcts::MCTSPlayer<BoardCell, HumanPlayer, PenguinPawn> mcts_player_1(&_game, _game.board->getPlayerById(1), constraints);
    mcts::MCTSPlayer<BoardCell, HumanPlayer, PenguinPawn> mcts_player_2(&_game, _game.board->getPlayerById(2), constraints);
    Move<BoardCell, PenguinPawn> move;

    draw();

    while (!_game.isFinished())
    {
        mcts_player_1.updateTree(move);
        mcts_player_2.updateTree(move);

        if (_game.getPlayerToPlay() == 1)
        {
            move = mcts_player_1.bestMove();
        }
        else
        {
            move = mcts_player_2.bestMove();
        }

        _game.play(move.pawn, move.target);
        draw();
    }

    // print results
    if (_game.board->checkStatus() == -1)
    {
        std::cout << "This is a draw :(" << std::endl;
    }
    else
    {
        std::cout << "Player #" << _game.board->checkStatus()
                  << " won!" << std::endl;
    }
}

} // namespace penguin
} // namespace game