#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leaderboard.h"
#define FILENAME "leaderboard"
#define MAX_LINE_LENGTH 100


// Funkcja dodająca wynik do pliku w odpowiednim miejscu
void add_score(const char *name, int score) {
    Player players[100];  // Tablica na wyniki
    int count = 0;

    // Otwórz plik do odczytu
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d", players[count].name, &players[count].score) == 2) {
            count++;
        }
        fclose(file);
    }

    // Znalezienie miejsca do wstawienia nowego wyniku
    int pos = 0;
    while (pos < count && players[pos].score >= score) {
        pos++;
    }

    // Przesunięcie wyników w dół, aby zrobić miejsce dla nowego wyniku
    for (int i = count; i > pos; i--) {
        players[i] = players[i - 1];
    }

    // Wstawienie nowego wyniku
    strcpy(players[pos].name, name);
    players[pos].score = score;
    count++;

    // Zapisz wyniki do pliku
    file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Nie można otworzyć pliku do zapisu.\n\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", players[i].name, players[i].score);
    }

    fclose(file);
    printf("Wynik dodany poprawnie!\n\n");
}

void display_scores() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Brak zapisanych wyników.\n");
        return;
    }

    char name[100];
    int score;
    printf("Lista wynikow:\n");

    for (int i =0; i < 5; i++)
    {
        if (fscanf(file, "%s %d", name, &score) == 2)
            printf("%s - %d\n", name, score);
        else
            break;
    }


    fclose(file);
}
