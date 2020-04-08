#include "Board.hpp"

namespace game
{
namespace penguin
{
Board::Board(const size_t dimension, const size_t number_of_penguins)
    : AbstractBoard(),
      _dimension(dimension)
{
    // generate the 2 players &
    // Generate the penguins for each team (x2)
    for (int ii = 0; ii < 2; ++ii)
    {
        HumanPlayer* player = new HumanPlayer(ii);
        _players.push_back(player);
        for (size_t jj = 0; jj < number_of_penguins; ++jj)
        {
            _penguins_on_board.push_back(new PenguinPlayer(ii * number_of_penguins + jj, player)); //TODO verify no crashing because doing shadowy things with references
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
                                                       rand() % 3 + 1 // random number of fish between 1 and 3 (included)
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

bool Board::checkForCorrectness(const Position &start_axial, const Position &destination_axial) const
{
    const Position3D start = hex_axial_to_cube(start_axial);
    const Position3D destination = hex_axial_to_cube(destination_axial);

    // checking if the move is allowed <=> checking if the hex cell is on a direct line from one of the side of the start one
    // <=> in a cube coordinate system, it is the same as looking if one of the coordinate is the same
    return !boardValues.at(destination_axial)->isOwned() && (start.x == destination.x ||
                                                             start.y == destination.y ||
                                                             start.z == destination.z);
}

bool Board::performMove(const int penguin_id, BoardCell *cell)
{
    PenguinPlayer *penguin_player = getPlayerById(penguin_id);
    BoardCell *cell_standing_on = penguin_player->getStandingOn();
    bool isCorrect = true;

    std::cout << "passing" << std::endl;

    if (cell_standing_on)
    {
        isCorrect = checkForCorrectness(cell_standing_on->getPosition(), cell->getPosition());
        std::cout << "inside cell standing on statement" << std::endl;
    }

    if (isCorrect)
    {
        std::cout << "inside is correct statement" << std::endl;
        if (cell_standing_on)
        {
            cell_standing_on->clearOwner(); // clear the owner and create a hole in the board
            cell_standing_on->setGone(true);
        }

        cell->setOwner(penguin_player);
        penguin_player->getOwner()->addScore(cell->getFish());
        penguin_player->setStandingOn(cell);
    }

    return isCorrect;
}

void Board::revertMove(const int penguin_id, BoardCell *cell)
{
    PenguinPlayer *penguin_player = getPlayerById(penguin_id);
    BoardCell *previousCell = penguin_player->getPreviousStandingOn();
    cell->clearOwner(); // clear the owner of the current cell

    previousCell->setOwner(penguin_player);                    // set the penguin as the owner of the previous cell
    penguin_player->getOwner()->substractScore(cell->getFish()); // update the score
    penguin_player->setStandingOn(previousCell);
}

//TODO check for win
// int Board::checkForWin(const board_line_t &line) const
// {
//     int previous = line[0]->getValue();
//     // check if this is the same value all along the line
//     for (const BoardCell *cell : line)
//     {
//         int value = cell->getValue();
//         if (value != previous)
//         {
//             // line is not full of the same values
//             return 0;
//         }
//     }

//     // it has been the same value all along from the beginning,
//     // return the id of the line's owner
//     return previous;
// }

int Board::checkStatus()
{
    bool all_zero = true;
    int winner_id = IN_PROGRESS;

    //TODO Optimize, we can just look at the cells around
    for (auto &penguin : getPlayersOnBoard())
    {
        if (getAvailableCells(penguin->getId()).size() > 0)
        {
            all_zero = false;
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

std::vector<BoardCell *> Board::getAvailableCells(const int penguin_id)
{
    // dbg(penguin_id);
    PenguinPlayer *penguin = getPlayerById(penguin_id);
    // dbg(penguin->getStandingOn());
    Position penguin_current_pos = penguin->getStandingOn()->getPosition();

    // dbg(penguin_current_pos.x);dbg(penguin_current_pos.y);

    std::vector<BoardCell *> ret;

    int inc_val = -1;
    while (inc_val == -1 || inc_val == 1)
    {
        int ii = penguin_current_pos.x;
        int jj = penguin_current_pos.y;
        BoardCell *ptr_cell;
        // check first diag, jj is varying
        while ((ptr_cell = boardValues[Position{ii, jj += inc_val}]) != nullptr && !ptr_cell->isGone() && !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        jj = penguin_current_pos.y;

        // check second diag, ii is varying
        while ((ptr_cell = boardValues[Position{ii += inc_val, jj}]) != nullptr && !ptr_cell->isGone() && !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        ii = penguin_current_pos.x;

        // check row, both varying
        while ((ptr_cell = boardValues[Position{ii += inc_val, jj -= inc_val}]) != nullptr && !ptr_cell->isGone() && !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        inc_val += 2; // -1; 1; out of scope, while is over
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
    const Position pos = Position{xx, yy};
    return boardValues.at(pos);
}

std::vector<PenguinPlayer *> Board::getPlayersOnBoard()
{
    std::vector<PenguinPlayer *> ret;
    for (PenguinPlayer* penguin : _penguins_on_board)
    {
        ret.push_back(penguin);
    }

    return ret;
}
} // namespace penguin
} // namespace game