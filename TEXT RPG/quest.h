#ifndef QUEST_H
#define QUEST_H
#include "utility.h"
#define MAX_QUEST 10

typedef struct {
	char title[50];
	char description1[200];
	int take;
	int clear;
	char description2[200];
	char description3[200];
	char description4[200];
} Quest;

extern Quest quest[MAX_QUEST];

void initializeQuest();
void QuestComplete1();

#endif // QUEST_H
