#include "ConsoleGame.hpp"

namespace game
{
ConsoleGame::ConsoleGame()
    : TicTacToe(nullptr, nullptr) // instanciate the players afterwards
{
    /*
    player1 = new Player(1);
    player2 = new Player(2);
    */
    mcts::MCTSConstraints constraints;
    constraints.time = 250;
    player1 = new MCTSPlayer(this, 1, constraints);
    player2 = new MCTSPlayer(this, 2, constraints);
}

ConsoleGame::~ConsoleGame()
{
    delete player1;
    delete player2;
}

// AbstractBoardCell *ConsoleGame::play(AbstractPlayer *player1, AbstractPlayer *player2)
// {
//     Board *bo = (Board *)board;
//     AbstractPlayer *player = player1;

//     if (bo->getTotalMoves() % 2)
//     {
//         player = player2;
//     }

//     return player->action(board);
// }

void ConsoleGame::draw() const
{
    // clear the output stdout
    // std::cout << "\033c";

    const std::vector<AbstractBoardCell *> &cells = board->getBoardCells();

    for (const AbstractBoardCell *absCell : cells)
    {
        const BoardCell *cell = (BoardCell *)absCell;
        const Position &pos = cell->getPosition();

        std::cout << cell->getValue() << (pos.y < board->size() - 1 ? " │ " : "");

        // ignore last line
        if (pos.y == board->size() - 1 && pos.x < board->size() - 1)
        {
            std::cout << std::endl;
            // ignore last column
            for (unsigned int ii = 0; ii < board->size() - 1; ++ii)
            {
                std::cout << "──┼─" << (ii == (unsigned int)board->size() - 2 ? "─" : "");
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

/*
void ConsoleGame::loop()
{
    std::cout << "test" << std::endl;

    //int turn = 0;
    draw();
    AbstractPlayer *player = player1;
    while (!TicTacToe::isFinished())
    {
        mcts::MCTSConstraints constraints;
        constraints.time = 250;

        //std::string filename = "turn_" + std::to_string(turn++);
        mcts::Tree tree(this, player, constraints);
        tree.begin();

        //std::cout << filename << std::endl;

        //mcts::TreeVisualizer visualizer(&tree, 2, filename + "_rough.txt");
        //visualizer.exportLog();

        //mcts::TreeVisualizer visualizer2(&tree, 4, filename + "_precise.txt");
        //visualizer2.exportLog();

        AbstractBoardCell *bestMove = tree.bestMove();
        play(player, bestMove);
        draw();

        player = getPlayerToPlay();
    }

    // print results
    if (board->checkStatus() == -1)
    {
        std::cout << "This is a draw :(" << std::endl;
    }
    else
    {
        std::cout << "Player #" << board->checkStatus()
                  << " won!" << std::endl;
    }
}
*/


void ConsoleGame::loop()
{
    std::cout << "test" << std::endl;

    //int turn = 0;
    draw();
    AbstractPlayer *player = player1;
    while (!TicTacToe::isFinished())
    {
        std::cout << "Player : " << player->getId() << " is playing."<< std::endl;
        AbstractBoardCell* bestMove = nullptr;
        if(dynamic_cast<MCTSPlayer*>(player) != nullptr)
        {
            MCTSPlayer * mcts_player = ((MCTSPlayer *) player);
            bestMove = mcts_player->bestMove();
            play(mcts_player, bestMove);
            mcts_player->updateTree(bestMove);
        }
        
        std::cout << "Switching players" << std::endl;
        player = getPlayerToPlay();
        if(dynamic_cast<MCTSPlayer*>(player) != nullptr)
        {
            MCTSPlayer * mcts_player_opponent = ((MCTSPlayer *) player);
            if(bestMove != nullptr)
                mcts_player_opponent->updateTree(bestMove);
        }
        draw();
    }

    // print results
    if (board->checkStatus() == -1)
    {
        std::cout << "This is a draw :(" << std::endl;
    }
    else
    {
        std::cout << "Player #" << board->checkStatus()
                  << " won!" << std::endl;
    }
}

AbstractGame* ConsoleGame::clone() const
{
    ConsoleGame* cg = new ConsoleGame(*this);
    cg->player1 = new AbstractPlayer(*player1);
    cg->player2 = new AbstractPlayer(*player2);
    cg->board = board->clone();
    return cg;
}

} // namespace game