#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct 
{
    int rows;
    int cols;
    int mines;
    int level;
} board_info;

typedef struct
{
    int all_squares;
    int empty_squares;
    char ** area;
    char ** planted_mines;
    int rows;
    int cols;
    int mines;
    int points;
    int level;

} board;

board Create_Board(board_info * cur_info);

void Regenerate(board * cur_board, int row, int col);
#endif