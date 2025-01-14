build:
	gcc -o minesweeper main.c src/board.c src/game.c src/score.c -Iinclude -Wall

run:
	./minesweeper

clean:
	rm -f minesweeper