#include "ConsoleGame.hpp"
#include "../../dbg.h"

namespace game
{
namespace penguin
{
ConsoleGame::ConsoleGame()
    : board(7, 4)
{
}

ConsoleGame::~ConsoleGame()
{
}

void ConsoleGame::draw()
{
    PrintHex print_hex(board.size());
    print_hex.print(board);
    
    // int dimension = board.size();

    // int offset = 0;
    // for (int jj = 0; jj < (int)dimension; ++jj) // jj for the rows
    // {
    //     for (int ii = offset; ii < (int)dimension + offset; ++ii) // ii for the cols
    //     {
    //         BoardCell *cell = (BoardCell *)board.getCell(ii, jj);
    //         Position position = cell->getPosition();
    //         Position3D position_cube = hex_axial_to_cube(position);
    //         Position position_offset = hex_cube_to_offset(position_cube);
    //         std::cout << "(" << position.x << "," << position.y <<  "->" << position_cube.x << "," << position_cube.y << "," << position_cube.z << "->" << position_offset.x << "," << position_offset.y << ") ";
    //         // std::cout << "(" << position.x << "," << position.y << "->" << position_offset.x << "," << position_offset.y << ") ";
    //     }

    //     if (jj % 2 == 1)
    //     {
    //         --offset;
    //     }
    //     std::cout << std::endl;
    // }

    // board.getPlayerById(0)->setStandingOn(board.getCell(1,1));
    // dbg(board.getCell(1,1)->getOwner());
    // for (auto& cell : board.getAvailableCells(0))
    // {
    //     std::cout << "(" << cell->getPosition().x << ";" << cell->getPosition().y << ") ";   
    // }

    // const size_t area_of_hex = 6 * 9; // 6x6
    

    // int offset = 0;

    // board.getCell(2,2)->setGone(true);

    

    // for (int yy = 0; yy < (int)board.size(); ++yy) // ii for the rows
    // {
    //     // // top of the pointy hex
    //     // for (int kk = 0; kk < 6; ++kk)
    //     // {
    //         // top row
    //         for (int kk = 0; kk < 2 ; ++kk)
    //         {
    //             for (int xx = offset ; xx < (int)board.size() + offset; ++xx) // jj for the cols
    //             {
    //                 bool is_void = !board.getCell(xx, yy);
    //                 // is iut the first row || top-left / top-right verif
    //                 std::cout << 
    //                     (kk == 0 ? "....." : "...") <<
    //                     (!is_void && (yy == 0 || yy % 2 == 0 || !board.getCell(xx, yy-1)->isGone()) ? "/" : " ") << 
    //                     (kk == 0 ? "." : ".....") <<
    //                     (!is_void && (yy == 0 || yy % 2 == 1 || !board.getCell(xx+1, yy-1)->isGone()) ? "\\" : " ");
    //             }
    //             std::cout << std::endl;
    //         }

    //         // sides
    //         // for (int jj = 0; jj < (int)board.size() ; ++jj) // ii for the cols
    //         // {
    //         //     bool is_void = !board.getCell(jj + offset, ii);
                
    //         //     std::cout << 
    //         //         (!is_void && (ii == 0 || board.getCell(jj-1, ii)->isGone()) ? "|" : " ") << 
    //         //         (!is_void ? "|" : " ");
    //         // }
    //         // std::cout << std::endl;

    //         // // bottom
    //         // for (int jj = 0; jj < (int)board.size() ; ++jj) // ii for the cols
    //         // {
    //         //     bool is_void = !board.getCell(jj + offset, ii);
                
    //         //     std::cout << 
    //         //         (!is_void ? "\\" : " ") << 
    //         //         (!is_void ? "/" : " ");
    //         // }
    //         // std::cout << std::endl;
    //     // }

    //     if (yy % 2 == 1)
    //     {
    //         --offset;
    //     }
    // }
}

void ConsoleGame::loop()
{
    draw();
    // while (!TicTacToe::isFinished())
    // {

    // }

    // print results
    // if (board->checkStatus() == -1)
    // {
    //     std::cout << "This is a draw :(" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Player #" << board->checkStatus()
    //               << " won!" << std::endl;
    // }
}

} // namespace penguin
} // namespace game