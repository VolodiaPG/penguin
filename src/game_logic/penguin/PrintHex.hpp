// Inspired from https://github.com/cmelchior/asciihexgrid

#ifndef PENGUIN_PRINT_HEX_HPP_
#define PENGUIN_PRINT_HEX_HPP_

#include <iostream>
#include "Board.hpp"
#include <cstring>
#include <algorithm>

namespace game
{
namespace penguin
{
class PrintHex
{
private:
    char *_char_map;
    char *_buffer_template;
    const char *TEMPLATE = "\
   / \\   \n\
 /     \\ \n\
|  X    |\n\
|  Y    |\n\
 \\     / \n\
   \\ /   \n\0";
    const size_t HEIGHT = 6;
    const size_t WIDTH = 10; // 10 prevoously
    // const size_t SIDE_LENGTH = 4;
    const size_t SIDE_HEIGHT = 2;
    const size_t BORDERS_LENGTH = 2;
    #define MAX_TEXT_LENGTH 3

    size_t _dimension;
    size_t _size_line;
    size_t _size_char_map;

    Board* _board;

    void printHex(
        const Position &axial_coords,
        const char *line1,
        const char *line2);

    void mapHexCoordsToCharCoords(
        const Position &axial_coords,
        int *res_xx,
        int *res_yy);

    void clear_map();

public:
    explicit PrintHex(Board* board);
    ~PrintHex();
    void print();
};
} // namespace penguin
} // namespace game
#endif