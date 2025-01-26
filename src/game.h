#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"
int play(board * cur_board, FILE * f);

int around(board * cur_board, int row, int col);

void dfs(board * cur_board, int row, int col, int visited[60][60]);
#endif