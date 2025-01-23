#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define MAX_SIZE 50

void load_minesweeper_board(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        exit(EXIT_FAILURE);
    }

    // rozmiary planszy
    int rows = 0;
    int cols = 0;
    int mines = 0;
    int level = 0;
    fscanf(file, "%d %d %d %d", &rows, &cols, &mines, &level);

    if (rows > MAX_SIZE || cols > MAX_SIZE) {
        printf("Zbyt duży rozmiar planszy!\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    board_info b = {rows, cols, mines, level}; // tworzenie planszy
    board cur_b = Create_Board(&b);

    // Wczytanie min planszy
    char line[100];
    for (int i = 0; i < rows; i++) {
        fscanf(file, "%s", line);  // Odczytujemy cały wiersz jako string

        for (int j = 0; j < cols; j++)
        {
            cur_b.planted_mines[i][j] = line[j] == '*' ? 1 : 0;
        }
    }


    // Wczytanie ruchów
    // *move_count = 0;
    // while (fscanf(file, " %c %d %d", &moves[*move_count].action, &moves[*move_count].row, &moves[*move_count].col) == 3) {
    //     (*move_count)++;
    // }

    // fclose(file);
}

