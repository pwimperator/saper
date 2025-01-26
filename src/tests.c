#include <stdio.h>
#include "board.h"
#include "load.h"
#include "game.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int test_around(board * cur_board, int row, int col, int expected)
{
    int res = around(cur_board, row, col);
    return res == expected;
}

int test_dfs(board * cur_board, int row, int col, int visited[60][60], char tab[5][5])
{
    dfs(cur_board, row, col, visited);
    int valid = 1;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (tab[i][j] != cur_board->area[i][j])
            {
                valid = 0;
                break;
            }
        }
    }

    return valid;
}

int test_load()
{
    if (load_minesweeper_board("tests/1"))
        return 1;
    else
        return 0;
}

int test_all()
{   
    int valid = 1;
    board_info n = {5, 5, 2, 1};
    board first = Create_Board(&n);
    board second = Create_Board(&n);
    board third = Create_Board(&n);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            first.planted_mines[i][j] = 0;
            second.planted_mines[i][j] = 0;
            third.planted_mines[i][j] = 0;
        }
    }
    
    first.planted_mines[0][0] = 1;
    first.planted_mines[0][1] = 1;
    second.planted_mines[0][0] = 1;
    second.planted_mines[4][4] = 1;
    third.planted_mines[0][0] = 1;
    third.planted_mines[1][1] = 1;

    valid = min(test_around(&first, 1, 0, 2), valid);
    valid = min(test_around(&first, 4, 4, 0), valid);
    valid = min(test_around(&first, 0, 2, 1), valid);

    int visited[60][60] = {0};
    char tab[5][5] = {
        {'#','1',' ',' ',' '},
        {'1','1',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ','1','1'},
        {' ',' ',' ','1','#'}
    };
    valid = min(test_dfs(&second, 0, 2, visited, tab), valid);
    if (valid)
    {
        printf("\nTesty jednostkowe zaakceptowane!");
    }
    return valid;
}

