#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"

board_info EZ = {9,9,10};
board_info MEDIUM = {16,16,40};
board_info HARD = {16,30,99};
board_info WRONG = {0, 0, 0};

board_info Create_Custom_Board_Info()
{
    printf("Podaj wielkosc planszy:\n");
    printf("Szerokosc:");
    int w;
    if (scanf("%d", &w) != 1 || w <= 0) return WRONG;

    printf("Wyskokosc:");
    int c;
    if (scanf("%d", &c) != 1 || c <= 0) return WRONG;

    printf("Miny:");
    int m;
    if (scanf("%d", &m) != 1 || m <= 0 || m > m * c) return WRONG;

    board_info new = {w, c, m};
    return new;
}
board_info Select_Board()
{   
    printf("Wybierz poziom trudnosci:\n");
    printf("1. Latwy  9x9   pol, 10 min\n");
    printf("2. Sredni 16x16 pol, 40 min\n");
    printf("3. Trudny 16x30 pol, 99 min\n");
    printf("4. Wlasna plansza\n");
    printf("5. Wyjdz\n");
    int level;
    if (scanf("%d", &level) != 1) return WRONG;

    switch (level)
    {
        case 1:
            return EZ;
        case 2:
            return MEDIUM;
        case 3:
            return HARD;
        case 4:
            return Create_Custom_Board_Info();
        case 5:
            return WRONG;

    }

}

int main(int argc, char* argv[])
{
    board_info info = Select_Board();
    if (info.rows == 0) return 1; 


    srand(time(NULL));
    board cur_board = Create_Board(&info);

    // for (int i =0; i< info.rows; i++)
    // {
    //     for (int j=0; j<info.cols; j++)
    //     {
    //         printf("%c", cur_board.area[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for (int i =0; i< info.rows; i++)
    // {
    //     for (int j=0; j<info.cols; j++)
    //     {
    //         printf("%d", cur_board.planted_mines[i][j]);
    //     }
    //     printf("\n");
    // }
    play(&cur_board);
}