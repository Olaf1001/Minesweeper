#ifndef GAME_H
#define GAME_H

void startGame();

void processUserInput(Board *board, char command, int row, int col, int *gameOver, int mineCount);

int checkIfWin(Board* board);

void selectLevel(int * boardLevel, int * boardRows, int * boardCols, int *boardMines);

#endif