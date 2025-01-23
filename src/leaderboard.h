#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_

#include <stdio.h>

typedef struct{
    char name[100];
    int score;
} Player;

void add_score(const char *name, int score);

void display_scores();

#endif