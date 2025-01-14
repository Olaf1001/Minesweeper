#ifndef SCORE_H
#define SCORE_H

#define MAX_NAME_LENGTH 100
#define MAX_RECORDS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} ScoreRecord;

int compareScores(const void *a, const void *b);

void fillScoreboard(char *userName, int userScore);

void displayScoreboard();

#endif