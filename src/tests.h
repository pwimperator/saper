#ifndef _TESTS_H_
#define _TESTS_H_

#include "board.h"

int test_around(board * cur_board, int row, int col, int expected);

int test_dfs(board * cur_board, int row, int col, int visited[60][60]);

int test_load();

int test_all();


#endif