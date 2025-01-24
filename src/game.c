#include <stdio.h>
#include "draw.h"
#include "board.h"
#include "leaderboard.h"

#define MAX_SIZE 60

int around(board * cur_board, int row, int col) // sprawdzanie liczby min wokol danego pola
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

void dfs(board * cur_board, int row, int col, int visited[MAX_SIZE][MAX_SIZE]) // dfs do odkrywania planszy
{   
    if (visited[row][col] == 1) return;

    visited[row][col] = 1;
    cur_board->points += cur_board->level;
    cur_board->empty_squares++;
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

int reveal(board * cur_board, int row, int col, int * first_guess, int visited[MAX_SIZE][MAX_SIZE]) // odkrycie danego pola
{
    if (*first_guess) // jesli na pierwszym wybranym polu jest mina, przenies ja
    {
        if (cur_board->planted_mines[row][col] == 1)
            Regenerate(cur_board, row, col);

        *first_guess = 0;
    }

    if (cur_board->planted_mines[row][col] == 1) // przegrana, odkrycie miny
        return -1;

    dfs(cur_board, row, col, visited); // odkrywanie sasiednich pol

    if (cur_board->all_safe_squares == cur_board->empty_squares) // wygrana
        return 2;

    return 1;
}

int play(board * cur_board, FILE * f) // rozgrywanie gry
{
    char option = '0';
    int r_row = 0;
    int r_col = 0;
    int row = 0;
    int col = 0;
    int first_guess = 1;
    int visited[MAX_SIZE][MAX_SIZE] = {0};

    f == stdin ? draw(cur_board): 0;
    f == stdin ? printf("Prosze podac koordynaty\n") : 0;
    
    while (1) // nieskonczona petla (rundy)
    {   
        fscanf(f, " %c", &option); // czytanie danych wejsciowych
        
        if (option == 'r')
        {   
            fscanf(f, " %d", &r_row);
            fscanf(f, " %d", &r_col);
            row = r_row - 1;
            col = r_col - 1;
            if ((col >= 0 && col < cur_board->cols) && (row >= 0 && row < cur_board->rows))
            {
                if (cur_board->area[row][col] == '#'){

                    int res = reveal(cur_board, row, col, &first_guess, visited);
                
                    if (res == -1)
                    {
                        draw_with_mines(cur_board);
                        printf("Przegrales!\n");
                        break;
                    }

                    if (res == 2){
                        draw_with_mines(cur_board);
                        printf("Wygrales!\n");
                        break;
                    }
                    f == stdin ? draw(cur_board) : 0;
                    f == stdin ? printf("Odkryto pole: [%d %d]\n", r_row, r_col) : 0;
                    
                }
                else if (cur_board->area[row][col] == 'F')
                {
                    cur_board->area[row][col] = '#';
                    f == stdin ? draw(cur_board) : 0;
                    f == stdin ? printf("Usunieto flage: [%d %d]\n", r_row, r_col) : 0;
                }
                else
                {
                    f == stdin ? draw(cur_board): 0;
                    f == stdin ? printf("Pole: [%d %d] jest odkryte\n", r_row, r_col) : 0;
                }   
            }
            else
            {
                f == stdin ? draw(cur_board) : 0;
                f == stdin ? printf("Podano zle wartosci koordynatow. Uzyj komendy \"h\"\n") : 0;
                fseek(stdin,0,SEEK_END); // czyszczenie bufora
            }
        }
        else if (option == 'f')
        {
            fscanf(f, " %d", &r_row);
            fscanf(f, " %d", &r_col);
            row = r_row - 1;
            col = r_col - 1;
            if ((col >= 0 && col < cur_board->cols) && (row >= 0 && row < cur_board->rows))
            {   

                if (cur_board->area[row][col] == '#'){
                    cur_board->area[row][col] = 'F';
                    f == stdin ? draw(cur_board) : 0;
                    f == stdin ? printf("Ustawionio flage: [%d %d]\n", r_row, r_col) : 0;
                    fseek(stdin,0,SEEK_END); // czyszczenie bufora
                }
                else if (cur_board->area[row][col] == 'F'){
                    cur_board->area[row][col] = '#';
                    f == stdin ? draw(cur_board) : 0;
                    f == stdin ? printf("Usunieto flage: [%d %d]\n", r_row, r_col): 0;
                }
                else
                {
                    f == stdin ? draw(cur_board): 0;
                    f == stdin ? printf("Pole: [%d %d] jest odkryte\n", r_row, r_col): 0;
                }
                    
            }
            else
            {
                f == stdin ? draw(cur_board) : 0;
                f == stdin ? printf("Podano zle wartosci koordynatow\n") : 0;
                fseek(stdin,0,SEEK_END); // czyszczenie bufora
            }
        }
        else if (option == 'h')
        {
            help();
            int d;
            scanf("%d",&d);
            draw(cur_board);
        }
        else
        {
            f == stdin ? draw(cur_board) : 0;
            f == stdin ? printf("Podano zle polecenie! Uzyj komendy \"h\"\n"): 0;
            fseek(stdin,0,SEEK_END); // czyszczenie bufora
        }
        r_row = 0;
        r_col = 0;
    }

    if (f == stdin){ // zapisywanie wynikow
    char imie[100];
    printf("\nPodaj imie: "); // imie
    scanf("%s", imie);

    add_score(imie, cur_board->points); // dodawanie wynikow

    display_scores(); // wyspiwyanie 5 najlepszych
    }

    return cur_board->points;
}