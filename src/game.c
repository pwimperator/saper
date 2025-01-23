#include <stdio.h>
#include "draw.h"
#include "board.h"

#define MAX_SIZE 60


int around(board * cur_board, int row, int col)
{
    int res = 0;

    int moves[] = { // row col
        -1, -1,
        0, -1,
        1, -1,
        -1, 0,
        1, 0,
        -1, 1,
        0, 1,
        1, 1
    };
    int cur_row = 0;
    int cur_col = 0;

    for (int i = 0; i < 8; i++)
    {   
        cur_row = row + moves[i * 2];
        cur_col = col + moves[i * 2 + 1];

        if ( (cur_row >= 0 && cur_row < cur_board->rows) && (cur_col >= 0 && cur_col < cur_board->cols) && cur_board->planted_mines[cur_row][cur_col] == 1)
            res += 1;
    }
    return res;
}

void dfs(board * cur_board, int row, int col, int visited[MAX_SIZE][MAX_SIZE])
{   
    if (visited[row][col] == 1) return;

    visited[row][col] = 1;

    int val = around(cur_board, row, col);

    cur_board->area[row][col] = val > 0 ? val + '0' : ' ';

    if (val > 0) return;

    int moves[] = { // row col
        -1, -1,
        0, -1,
        1, -1,
        -1, 0,
        1, 0,
        -1, 1,
        0, 1,
        1, 1
    };

    int cur_row = 0;
    int cur_col = 0;
    for (int i = 0; i < 8; i++)
    {   
        cur_row = row + moves[i * 2];
        cur_col = col + moves[i * 2 + 1];
        if ( (cur_col >= 0 && cur_col < cur_board->cols) && (cur_row >= 0 && cur_row < cur_board->rows) && visited[cur_row][cur_col] != 1 && cur_board->planted_mines[cur_row][cur_col] != 1)
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
    printf("Prosze podac koordynaty\n");

    while (1)
    {   
        val = scanf(" %c %d %d", &option, &row, &col);
        // printf("%d %d %d %c\n",val,row,col,option);
    
        if(val == 0 | val == 1 || val == 2)
        {   

            printf("Podano zle polecenie! Uzyj komendy \"h\"\n");
            fseek(stdin,0,SEEK_END); // czyszczenie bufora
            continue;
        }

        if (option == 'r')
        {
            if ((col >= 0 && col < cur_board->cols) && (row >= 0 && row < cur_board->rows))
            {
                if (cur_board->area[row][col] == '#'){

                    int res = reveal(cur_board, row, col, &first_guess, visited);
                
                    if (res == -1)
                    {
                        draw_with_mines(cur_board);
                        printf("Przegrales!\n", row, col);
                        break;
                    }

                    printf("Odkryto pole: [%d %d]\n", row, col);
                    
                }
                else if (cur_board->area[row][col] == 'F')
                {
                    cur_board->area[row][col] = '#';
                    printf("Usunieto flage: [%d %d]\n", row, col);
                }
                else
                    printf("Pole: [%d %d] jest odkryte\n", row, col);
                    
            }
            else
            {
                printf("Podano zle wartosci koordynatow\n");
                continue;
            }
        }
        else if (option == 'f')
        {
            if ((col >= 0 && col < cur_board->cols) && (row >= 0 && row < cur_board->rows))
            {   

                if (cur_board->area[row][col] == '#'){
                    cur_board->area[row][col] = 'F';
                    printf("Ustawionio flage: [%d %d]\n", row, col);
                }
                else if (cur_board->area[row][col] == 'F'){
                    cur_board->area[row][col] = '#';
                    printf("Usunieto flage: [%d %d]\n", row, col);
                }
                else
                    printf("Pole: [%d %d] jest odkryte\n", row, col);
                    
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


