#include "ConsoleGame.hpp"

namespace game
{
namespace penguin
{
ConsoleGame::ConsoleGame()
    : _game(7, 2),
      _print_hex((Board *)_game.board)
{
    Board *board = (Board *)_game.board;
    // Placing all the penguins
    // team 1
    board->performMove(0, board->getCell(0, 0));
    board->performMove(1, board->getCell(3, 6));
    // team 2
    board->performMove(2, board->getCell(-3, 6));
    board->performMove(3, board->getCell(6, 0));
}

ConsoleGame::~ConsoleGame()
{
}

void ConsoleGame::draw()
{
    _print_hex.print();
}

void ConsoleGame::loop()
{
    std::cout << "Looping, wheeeeeeeeee" << std::endl;

    while (!_game.isFinished())
    {
        bool keep_asking = true;
        unsigned int penguin_id, xx, yy;
        const unsigned int player_to_play = _game.getPlayerToPlay();

        draw();

        while (keep_asking)
        {
            std::cout << "Player #" << player_to_play << " please make your move: " << std::endl
                      << "<PenguinId> <Position x> <Position y>" << std::endl;
            std::cin >> penguin_id >> xx >> yy;
            std::cout << std::endl;

            keep_asking = !(penguin_id < (player_to_play + 1) * 2 && penguin_id >= player_to_play);
        }

        _game.play(penguin_id, _game.board->getCell(xx, yy));
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