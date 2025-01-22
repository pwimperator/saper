#include <stdio.h>
#include "draw.h"
#include "board.h"

#define MAX_SIZE 200


int around(board * cur_board, int row, int col)
{
    int res = 0;

    int moves[] = { // row col
        -1, -1,
        0, -1,
        1, -1,
        -1, 0,
        0, 0,
        1, 0,
        -1, 1,
        0, 1,
        1, 1
    };
    int cur_row = 0;
    int cur_col = 0;

    for (int i = 0; i < 9; i++)
    {   
        cur_row = row + moves[i * 2];
        cur_col = col + moves[i * 2 + 1];

        if ( (cur_row >= 0 && cur_row < cur_board->rows) && (cur_col >= 0 && cur_col < cur_board->cols) && cur_board->planted_mines[cur_row][cur_col] == '*')
            res += 1;
    }
    return res;
}

void dfs(board * cur_board, int row, int col, int visited[MAX_SIZE][MAX_SIZE])
{   
    if (visited[row][col] == 1)
        return;

    visited[row][col] = 1;

    int val = around(cur_board, row, col);
  
    cur_board->area[row][col] = val ? (char)val : ' ';

    if (val)
        return; 

    int moves[] = { // row col
        -1, 0, 
        1, 0,
        0, -1,
        0, 1
        };

    int cur_row = 0;
    int cur_col = 0;
    for (int i = 0; i < 4; i++)
    {   
        cur_row = row + moves[i * 2];
        cur_col = col + moves[i * 2 + 1];
        if ((row >= 0 && row < cur_board->rows) && (col >= 0 && col < cur_board->cols) && cur_board->area[cur_row][cur_col] == '#')
        {
            dfs(cur_board, cur_row, cur_col, visited);
        }
    }
    
}

int reveal(board * cur_board, int row, int col, int * first_guess, int visited[MAX_SIZE][MAX_SIZE])
{
    if (*first_guess)
    {
        if (cur_board->planted_mines[row][col] == 1)
            Regenerate(cur_board, row, col);

        *first_guess = 0;
    }

    if (cur_board->planted_mines[row][col] == 1)
        return -1;

    dfs(cur_board, row, col, visited);

    return 1;
}

void play(board * cur_board)
{
    char option = '0';
    int row = 0;
    int col = 0;
    int val = 0;
    int first_guess = 1;
    int visited[MAX_SIZE][MAX_SIZE] = {0};
    draw(cur_board);

    while (1)
    {   
        val = scanf(" %c %d %d", &option, &row, &col);
        // printf("%d %d %d %c\n",val,row,col,option);

        if(val == 0 | val == 1 || val == 2)
        {
            printf("Podano zle polecenie! Uzyj komendy \"help\"\n");
            continue;
        }

        if (option == 'r')
        {
            if ((col >= 0 && col < cur_board->cols) && (row >= 0 && row < cur_board->rows))
            {
                if (cur_board->area[row][col] == '#'){

                    reveal(cur_board, row, col, &first_guess, visited);
                    printf("Odslonieto pole: [%d %d]\n", row, col);
                    
                }
                else if (cur_board->area[row][col] == 'F')
                    printf("Usunieto flage: [%d %d]\n", row, col);
                else
                    printf("Pole: [%d %d] juz jest odsloniete\n", row, col);
                    
            }
            else
            {
                printf("Podano zle wartosci koordynatow\n");
                break;
                continue;
            }
        }
        else if (option == 'f')
        {
            if ((col >= 0 && col < cur_board->cols) && (row >= 0 && row < cur_board->rows))
            {   

                if (cur_board->area[row][col] == '#')
                    printf("Ustawionio flage: [%d %d]\n", row, col);
                else
                    printf("Usunieto flage: [%d %d]\n", row, col);
                    
            }
            else
            {
                printf("Podano zle wartosci koordynatow\n");
            }
        }
        else
        {
            printf("Podano zle polecenie! Uzyj komendy \"help\"\n");
        }

        draw(cur_board);
    }
}


