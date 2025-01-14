#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/score.h"

int compareScores(const void *a, const void *b) {
    const ScoreRecord *recordA = (const ScoreRecord *)a;
    const ScoreRecord *recordB = (const ScoreRecord *)b;

    return recordB->score - recordA->score;
}

void fillScoreboard(char *userName, int userScore) {
    FILE *scoreboard;
    ScoreRecord records[MAX_RECORDS];
    int recordCount = 0;

    scoreboard = fopen("scoreboard.txt", "r");
    if (scoreboard != NULL) {
        while (fscanf(scoreboard, "%s %d", records[recordCount].name, &records[recordCount].score) == 2) {
            recordCount++;
            if (recordCount >= MAX_RECORDS) {
                printf("[!] Maximum number of records reached.\n");
                break;
            }
        }
        fclose(scoreboard);
    }

    strncpy(records[recordCount].name, userName, MAX_NAME_LENGTH - 1);
    records[recordCount].name[MAX_NAME_LENGTH - 1] = '\0';
    records[recordCount].score = userScore;
    recordCount++;

    qsort(records, recordCount, sizeof(ScoreRecord), compareScores);

    scoreboard = fopen("scoreboard.txt", "w");
    if (scoreboard == NULL) {
        printf("[!] Can't open scoreboard file for writing.\n");
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        fprintf(scoreboard, "%s %d\n", records[i].name, records[i].score);
    }

    fclose(scoreboard);
}

void displayScoreboard() {
    FILE *scoreboard;
    scoreboard = fopen("scoreboard.txt", "r");

    char name[MAX_NAME_LENGTH];
    int score;
    int counter = 1;

    if (scoreboard != NULL) {
        while ((fscanf(scoreboard, "%s %d", name, &score) == 2) && counter <= 5 ) {
            printf("%d. %s %d\n", counter, name, score);
            counter++;
    }
        fclose(scoreboard);
    }
}