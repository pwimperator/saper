#include <stdio.h>
#include "board.h"

void draw_mines(board * cur_board) // funkcja developerska do pokazywania min
{ 
    int cmt_10 = cur_board->cols >= 10 ? 1 : 0;
    int rmt_10 = cur_board->rows >= 10 ? 1 : 0;

    if (cmt_10)
    {   
        rmt_10 ? printf("   "): printf("  ");
        for (int i = 1; i <= cur_board->cols; i++)
        {
            i / 10 ? printf("%d", i / 10) : printf(" ");
        }
        printf("\n");
    }
    rmt_10 ? printf("   "): printf("  ");
    for (int i = 1; i <= cur_board->cols; i++)
    {   
        printf("%d", i % 10);
    }
    printf("\n\n");

    for (int i =0; i< cur_board->rows; i++)
    {
        if (rmt_10)
        {
            (i + 1) / 10 ? printf("%d", (i + 1) / 10) : printf(" ");
        }
        printf("%d ", (i + 1) % 10);
        for (int j=0; j <cur_board->cols; j++)
        {
            printf("%d", cur_board->planted_mines[i][j]);
        }
        printf("\n");
    }
}

void draw(board * cur_board) // funkcja rysujaca aktualny stan planszy
{
    printf("\e[1;1H\e[2J"); // czyszczenie konsoli
    printf("Miny:%5d | Wynik:%5d\n\n", cur_board->mines, cur_board->points); // wypisanie liczby min i wyniku
    int cmt_10 = cur_board->cols >= 10 ? 1 : 0;
    int rmt_10 = cur_board->rows >= 10 ? 1 : 0;

    if (cmt_10) // wypisywanie numeracji rzedow i kolumn w zaleznosci od ich liczby
    {   
        rmt_10 ? printf("   "): printf("  ");
        for (int i = 1; i <= cur_board->cols; i++)
        {
            i / 10 ? printf("%d", i / 10) : printf(" ");
        }
        printf("\n");
    }
    rmt_10 ? printf("   "): printf("  ");
    for (int i = 1; i <= cur_board->cols; i++)
    {   
        printf("%d", i % 10);
    }
    printf("\n\n");


    for (int i =0; i< cur_board->rows; i++) // faktyczne wypisywanie planszy
    {   
        if (rmt_10)
        {
            (i + 1) / 10 ? printf("%d", (i + 1) / 10) : printf(" ");
        }
        printf("%d ", (i + 1) % 10);
        for (int j=0; j<cur_board->cols; j++)
        {
            printf("%c", cur_board->area[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // draw_mines(cur_board);
}

void draw_with_mines(board * cur_board) // wypisywanie planszy z pokazanymi minami - koniec gry
{   
    printf("\e[1;1H\e[2J"); // czyszczenie konsoli
    printf("Miny:%5d | Wynik:%5d\n\n", cur_board->mines, cur_board->points); // wypisanie liczby min i wyniku

    int cmt_10 = cur_board->cols >= 10 ? 1 : 0;
    int rmt_10 = cur_board->rows >= 10 ? 1 : 0;

    if (cmt_10) // wypisywanie numeracji rzedow i kolumn w zaleznosci od ich liczby
    {   
        rmt_10 ? printf("   "): printf("  ");
        for (int i = 1; i <= cur_board->cols; i++)
        {
            i / 10 ? printf("%d", i / 10) : printf(" ");
        }
        printf("\n");
    }
    rmt_10 ? printf("   "): printf("  ");
    for (int i = 1; i <= cur_board->cols; i++)
    {   
        printf("%d", i % 10);
    }
    printf("\n\n");

    for (int i =0; i< cur_board->rows; i++) // faktyczne wypisywanie planszy
    {
        if (rmt_10)
        {
            (i + 1) / 10 ? printf("%d", (i + 1) / 10) : printf(" ");
        }
        printf("%d ", (i + 1) % 10);
        for (int j=0; j<cur_board->cols; j++)
        {
            cur_board->planted_mines[i][j] == 1 ? printf("\033[33m%c\033[0m", '*') : printf("%c", cur_board->area[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // draw_mines(cur_board);
}

void help() // wypisywanie polecen - help
{
    printf("\e[1;1H\e[2J");
	printf("Polecenia:\n"
		" f [rzad] [kolumna] - ustawia lub usuwa flage w danym polu\n"
		" r [rzad] [kolumna] - odkrywa pole lub usuwa flage w danym polu\n"
		" h - pokazuje ta wiadomosc\n"
        " Nacisnij dowolny przycisk i zatwierdz enterem aby wyjsc\n");
}

void help_arg() // wypisywanie argumentow - help
{
	printf("Argumenty:\n"
		" -t [plik] - testuje program wczytujac procedury z pliku\n"
		" -t        - przeprowadza testy jednostkowe\n"
		" -h    - wyswietla ta wiadomosc\n\n");
    printf("Polecenia:\n"
		" f [rzad] [kolumna] - ustawia lub usuwa flage w danym polu\n"
		" r [rzad] [kolumna] - odkrywa pole lub usuwa flage w danym polu\n"
		" h - pokazuje ta wiadomosc\n");
}