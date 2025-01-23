CC=gcc
FLAGS=-Wall -g
OUT=a.exe

FILES_C=src/main.c src/board.c src/draw.c src/leaderboard.c src/game.c
FILES_H=src/board.h src/draw.h src/leaderboard.h src/game.h

$(OUT): $(FILES_C) $(FILES_H)
	$(CC) $(FLAGS) $(FILES_C) -o $(OUT)