#ifndef QUEST_H
#define QUEST_H
#include "utility.h"
#define MAX_QUEST 22
#define MAX_QUESTITEM 7

typedef struct {
	char title[50];
	char description1[200];
	int take;
	int clear;
	char description2[200];
	char description3[200];
	char description4[200];
	int questCondition;
	int questGoal;
} Quest;

typedef struct {
	char title[50];
	char description1[200];
	char description2[200];
	char description3[200];
} PrologueQuest; // 프롤로그 퀘스트

typedef enum {
	VolunArmyQ,	//의병
	GoverArmyQ,	//관군
	JapArmyQ,	//왜군
	NobodyQ		//무소속
} QuestItemType;

typedef struct
{
	char name[100];
	int currentmap;
	int isActive;
	Position pos;
	QuestItemType type;
} QuestItemData;

extern QuestItemData QuestItemList[MAX_QUESTITEM];
extern QuestItemData* currentQuestItem;

extern Quest quest[MAX_QUEST];
extern int checkboss1;
extern int checkboss2;
extern PrologueQuest prologuequest; //프롤로그 퀘스트

void initializeQuest();
void ActiveQuestItem();
void QuestComplete1();
void QuestComplete2();
void QuestComplete3();
void QuestComplete4();
void QuestComplete5();
void QuestComplete6();
void QuestComplete7();
void QuestComplete8();
void QuestComplete9();
void QuestComplete10();
void QuestComplete11();
void QuestComplete12();
void QuestComplete13();
void QuestComplete14();
void QuestComplete15();
void QuestComplete16();
void QuestComplete17();
void QuestComplete18();
void QuestComplete19();

void initializeQuestItem();
void drawQuestItem(QuestItemData *QuestItemList);

#endif // QUEST_H

