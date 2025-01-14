PROGRAM = minesweeper

SRC = main.c src/board.c src/game.c src/score.c
INCLUDE = -Iinclude

CFLAGS = -Wall

CC = gcc

.PHONY: all clean run run_scoreboard run_file

build: $(PROGRAM)

$(PROGRAM): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(PROGRAM) $(SRC)

run: $(PROGRAM)
	./$(PROGRAM)

run_scoreboard: $(PROGRAM)
	./$(PROGRAM) -s

run_file: $(PROGRAM)
	./$(PROGRAM) -f input.txt

clean:
	rm -f $(PROGRAM)
