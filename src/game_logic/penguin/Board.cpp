#include <assert.h>

#include "../AbstractBoard.hpp"
#include "../utils/Position3D.hpp"
#include "../utils/conversions.hpp"
#include "BoardCell.hpp"
#include "PenguinPawn.hpp"
#include "HumanPlayer.hpp"
#include "PrintHex.hpp"

#include "Board.hpp"

namespace game
{
namespace penguin
{
Board::Board(const size_t dimension, const size_t number_of_penguins)
    : AbstractBoard(),
      _dimension(dimension)
{
    // generate the 2 players (1 & 2, 0 is forbidden) &
    // Generate the penguins for each team (x2)
    for (int ii = 0; ii < 2; ++ii)
    {
        HumanPlayer *player = new HumanPlayer(ii + 1);
        _players.push_back(player);
        for (size_t jj = 0; jj < number_of_penguins; ++jj)
        {
            const unsigned int penguin_id = ii * number_of_penguins + jj;
            PenguinPawn *penguin = new PenguinPawn(penguin_id, player);
            _penguins_on_board.push_back(penguin);
            player->addPenguin(penguin);
        }
    }

    //TODO découpler la génération et le parcours de la structure elle même (pattern visiteur)
    int offset = 0;
    for (int yy = 0; yy < (int)_dimension; ++yy) // ii for the rows
    {
        for (int xx = offset; xx < (int)_dimension + offset; ++xx) // jj for the cols
        {
            // rows in x and cols in y
            Position pos;
            pos.x = xx;
            pos.y = yy;

            boardValues.insert_or_assign(pos,
                                         new BoardCell(pos,
                                                    1 //    rand() % 3 + 1 // random number of fish between 1 and 3 (included)
                                                       ));
        }

        if (yy % 2 == 1)
        {
            --offset;
        }
    }
}

Board::~Board()
{
    for (auto entry : boardValues)
    {
        if (entry.second)
            delete entry.second;
    }

    for (auto player : _players)
    {
        if (player)
            delete player;
    }

    for (auto player : _penguins_on_board)
    {
        if (player)
            delete player;
    }
}

bool Board::checkForCorrectness(const Position &start_axial, const Position &destination_axial)
{
    bool ret;
    const Position3D start = hex_axial_to_cube(start_axial);
    const Position3D destination = hex_axial_to_cube(destination_axial);

    // check if the move is on a diagonal
    // checking if the move is allowed <=> checking if the hex cell is on a direct line from one of the side of the start one
    // <=> in a cube coordinate system, it is the same as looking if one of the coordinate is the same
    ret = !boardValues.at(destination_axial)->isOwned() && (start.x == destination.x ||
                                                            start.y == destination.y ||
                                                            start.z == destination.z);

    if (ret)
    {
        int xx = start_axial.x, yy = start_axial.y, inc_xx = 0, inc_yy = 0;
        BoardCell *ptr_cell = nullptr;
        // check is a cell is owned or gone between the target and the origin
        if (start.x == destination.x || start.y == destination.y)
        {
            inc_yy = (destination_axial.y - start_axial.y < 0) ? -1 : 1;
        }

        if (start.z == destination.z || start.y == destination.y)
        {
            inc_xx = (destination_axial.x - start_axial.x < 0) ? -1 : 1;
        }
        //TODO check if we are not creating new values (nullptr ones)
        while ((ptr_cell = boardValues[{xx += inc_xx, yy += inc_yy}]) != nullptr &&
               (ret = (!ptr_cell->isGone() && !ptr_cell->isOwned())) &&
               destination_axial.x != xx && destination_axial.y != yy)
            ;
    }

    return ret;
}

bool Board::performMove(PenguinPawn *penguin, BoardCell *cell)
{
    assert(penguin != nullptr);
    assert(cell != nullptr);
    HumanPlayer *human_player = penguin->getOwner();
    BoardCell *cell_standing_on = penguin->getCurrentCell();
    bool isCorrect = true;
    // std::cout << "Asked penguin#" << penguin->getId() << " (" << cell->getPosition().x << "," << cell->getPosition().y << ")" << std::endl;

    if (cell_standing_on)
    {
        isCorrect = checkForCorrectness(cell_standing_on->getPosition(), cell->getPosition());
    }

    if (isCorrect)
    {
        if (cell_standing_on)
        {
            // clear the owner and create a hole in the board
            cell_standing_on->clearOwner();
            cell_standing_on->setGone(true);
        }

        cell->setOwner(penguin);
        human_player->addScore(cell->getFish());
        penguin->makeMove(cell);
    }

    return isCorrect;
}

void Board::revertMove(HumanPlayer *human_player)
{
    assert(human_player != nullptr);
    assert("no more history is available/stored" && human_player->getNumberMovesDone() != 0);

    Move<BoardCell, PenguinPawn> current_move = human_player->dequeueLastMove();
    BoardCell *cell_previous = current_move.from;
    BoardCell *cell_current = current_move.target;
    PenguinPawn *penguin = cell_current->getOwner();

    cell_current->clearOwner();
    cell_current->setGone(false);
    human_player->substractScore(cell_current->getFish());

    if (cell_previous)
    {
        cell_previous->setGone(false);
        cell_previous->setOwner(penguin);
    }
}

int Board::checkStatus()
{
    bool all_zero = true;
    int winner_id = IN_PROGRESS;

    //TODO Optimize, we can just look at the cells around
    for (auto &human : _players)
    {
        all_zero = true;
        for (auto &penguin : human->getPenguins())
        {
            if (getAvailableCells(penguin).size() > 0)
            {
                all_zero = false;
                break;
            }
        }
        if (all_zero)
        {
            break;
        }
    }

    if (all_zero)
    {
        winner_id = _players[1]->getId();
        int score_player_0 = _players[0]->getScore();
        int score_player_1 = _players[1]->getScore();
        if (score_player_0 > score_player_1)
        {
            winner_id = _players[0]->getId();
        }
        else if (score_player_0 == score_player_1)
        {
            winner_id = DRAW;
        }
    }

    return winner_id;
}

std::vector<BoardCell *> Board::getAvailableCells(PenguinPawn *penguin)
{
    assert(penguin != nullptr);
    HumanPlayer *human_player = penguin->getOwner();
    assert(human_player != nullptr);
    Position penguin_current_pos = penguin->getCurrentCell()->getPosition();


    std::vector<BoardCell *> ret;

    int inc_val = -1;
    while (inc_val == -1 || inc_val == 1)
    {
        int ii = penguin_current_pos.x;
        int jj = penguin_current_pos.y;
        BoardCell *ptr_cell;
        // check first diag, jj is varying
        while ((ptr_cell = boardValues[{ii, jj += inc_val}]) != nullptr &&
               !ptr_cell->isGone() &&
               !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        jj = penguin_current_pos.y;

        // check second diag, ii is varying
        while ((ptr_cell = boardValues[{ii += inc_val, jj}]) != nullptr &&
               !ptr_cell->isGone() &&
               !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        ii = penguin_current_pos.x;

        // check row, both varying
        while ((ptr_cell = boardValues[{ii += inc_val, jj -= inc_val}]) != nullptr &&
               !ptr_cell->isGone() &&
               !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        inc_val += 2; // -1; 1; out of scope, while is over
    }

    for (auto cell : ret)
    {
        assert(checkForCorrectness(penguin_current_pos, cell->getPosition()) == true);
    }

    // return a copy
    return ret;
}

// TODO check if we want all the cells or just the ones that aren't gone yet
std::vector<BoardCell *> Board::getBoardCells()
{
    std::vector<BoardCell *> ret;

    for (const auto &entry : boardValues) // iterate over the "map"
    {
        ret.push_back(entry.second);
    }

    // copy return
    return ret;
}

BoardCell *Board::getCell(int xx, int yy)
{
    const Position pos = {xx, yy};
    return boardValues.at(pos);
}

std::vector<PenguinPawn *> Board::getPawnsOnBoard()
{
    std::vector<PenguinPawn *> ret;
    for (PenguinPawn *penguin : _penguins_on_board)
    {
        ret.push_back(penguin);
    }

    return ret;
}

PenguinPawn *Board::getPawnById(const unsigned int penguin_id)
{
    return _penguins_on_board[penguin_id];
}

HumanPlayer *Board::getPlayerById(const unsigned int human_player_id)
{
    return _players[human_player_id - 1];
}
} // namespace penguin
} // namespace game