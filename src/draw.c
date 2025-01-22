#include <stdio.h>
#include "board.h"

void draw(board * cur_board)
{

    for (int i =0; i< cur_board->rows; i++)
        {
            for (int j=0; j<cur_board->cols; j++)
            {
                printf("%c", cur_board->area[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        for (int i =0; i< cur_board->rows; i++)
        {
            for (int j=0; j <cur_board->cols; j++)
            {
                printf("%d", cur_board->planted_mines[i][j]);
            }
            printf("\n");
        }
}