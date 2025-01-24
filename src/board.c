#include "board.h"
#include <stdio.h>
#include <stdlib.h>


board Create_Board(board_info * cur_info) // towrzenie struktury-planszy
{
    
    board new_board;

    new_board.cols = cur_info->cols;
    new_board.rows = cur_info->rows;
    new_board.mines = cur_info->mines;
    new_board.points = 0;
    new_board.level = cur_info->level;

    new_board.all_safe_squares = new_board.cols * new_board.rows - new_board.mines;
    new_board.empty_squares = 0;


    // alokacja pamieci
    new_board.area = malloc(new_board.rows * sizeof(char *)); 
    new_board.planted_mines = malloc(new_board.rows * sizeof(char *));
    for (int i = 0; i < new_board.rows; i++)
    {
        new_board.area[i] = malloc(new_board.cols * sizeof(char) + 1);
        new_board.planted_mines[i] = malloc(new_board.cols * sizeof(char) + 1);
    }

    // wypelnianie pol 
    for (int i = 0; i < new_board.rows; i++)
    {
        for(int j = 0; j < new_board.cols; j++)
        {
            new_board.area[i][j] = '#';
            new_board.planted_mines[i][j] = 0;
        }
    }

    // wypelnianie pol minami
    int free_mines = new_board.mines;
    while (free_mines)
    {   
        int plant_row = rand() % cur_info->rows;
        int plant_col = rand() % cur_info->cols;

        if (new_board.planted_mines[plant_row][plant_col] != 1)
        {   
            new_board.planted_mines[plant_row][plant_col] = 1;
            free_mines--;
        }
    }
    return new_board;
}

void Regenerate(board * cur_board, int row, int col) // losowanie miny w inne miejsce
{
    cur_board->planted_mines[row][col] = 0;

    while (1)
    {
        int plant_row = rand() % cur_board->rows;
        int plant_col = rand() % cur_board->cols;

        if (cur_board->planted_mines[plant_row][plant_col] != 1)
        {   
            cur_board->planted_mines[plant_row][plant_col] = 1;
            break;
        }
    }

}