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

typedef struct {
	char title[50];
	int used;
	Position pos;
} QuestItem1;

typedef struct {
	char title[50];
	int used;
	Position pos;
} QuestItem2;

typedef struct {
	char title[50];
	int used;
	Position pos;
} QuestItem3;

extern Quest quest[MAX_QUEST];
extern QuestItem1 questitem1;
extern QuestItem2 questitem2;
extern QuestItem3 questitem3;

void initializeQuest();
void QuestComplete1();
void QuestComplete2();
void QuestComplete3();
void QuestComplete4();
void QuestComplete5();

void drawQuestItem1();
void drawQuestItem2();
void drawQuestItem3();
void eraseQuestItem1();
void eraseQuestItem2();
void eraseQuestItem3();

#endif // QUEST_H

