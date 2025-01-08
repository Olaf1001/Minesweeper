#ifndef GAME_H
#define GAME_H

void startGame();

void processUserInput(Board *board, char command, int row, int col, int *gameOver);

int checkIfWin(Board* board);

#endif