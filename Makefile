CC=cc
FLAGS=-Wall -g
OUT=saper

FILES_C=src/main.c src/board.c src/draw.c src/leaderboard.c src/game.c src/load.c
FILES_H=src/board.h src/draw.h src/leaderboard.h src/game.h src/load.h

$(OUT): $(FILES_C) $(FILES_H)
	$(CC) $(FLAGS) $(FILES_C) -o $(OUT)

test: $(OUT)
	./$(OUT) -t tests/1
	./$(OUT) -t tests/2
	./$(OUT) -t tests/3
	./$(OUT) -t tests/4
	./$(OUT) -t tests/5