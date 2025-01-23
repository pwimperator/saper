#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "draw.h"
#include "game.h"
#include "board.h"

board_info EZ = {9,9,10, 1};
board_info MEDIUM = {16,16,40, 2};
board_info HARD = {16,30,99, 3};
board_info WRONG = {0, 0, 0, 0};

board_info Create_Custom_Board_Info()
{
    printf("Podaj wielkosc planszy:\n");
    printf("Wysokosc:");
    int w;
    if (scanf("%d", &w) != 1 || w <= 0) return WRONG;

    printf("Szerokosc:");
    int c;
    if (scanf("%d", &c) != 1 || c <= 0) return WRONG;

    printf("Miny:");
    int m;
    if (scanf("%d", &m) != 1 || m <= 0 || m > m * c) return WRONG;

    if (w > 50 || c > 50)
    {
        printf("Maksymalne wymiary planszy to 50x50!\n");
        return WRONG;
    }

    board_info new = {w, c, m, 1};
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

    if (level > 5 || level < 1)
    {
        printf("Zla liczba!");
        return WRONG;
    }

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
    int opt;
    
    // Opcje: -h, -f <plik>
    while ((opt = getopt(argc, argv, "hf:")) != -1) {
        switch (opt) {
            case 'h':
                help_arg();
                return 0;
            case 'f':
                printf("Wybrano opcje -f z wartoscia: %s\n", optarg);
                break;
            case '?':
                printf("Nieznana opcja: %c\n");
                return 1;
        }
    }


    board_info info = Select_Board();
    if (info.rows == 0) return 1; 

    srand(time(NULL));
    board cur_board = Create_Board(&info);

    play(&cur_board);
}