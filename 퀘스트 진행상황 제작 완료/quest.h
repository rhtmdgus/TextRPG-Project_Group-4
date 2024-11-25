#ifndef QUEST_H
#define QUEST_H
#include "utility.h"
#define MAX_QUEST 10
#define MAX_QUESTITEM 3

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
} PrologueQuest; // ���ѷα� ����Ʈ

typedef enum {
	VolunArmyQ,	//�Ǻ�
	GoverArmyQ,	//����
	JapArmyQ,	//�ֱ�
	NobodyQ		//���Ҽ�
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
extern PrologueQuest prologuequest; //���ѷα� ����Ʈ

void initializeQuest();
void initializePrologueQuest();
void QuestComplete1();
void QuestComplete2();
void QuestComplete3();
void QuestComplete4();
void QuestComplete5();
void QuestComplete6();
void QuestComplete7();

void initializeQuestItem();
void drawQuestItem(QuestItemData *QuestItemList);

#endif // QUEST_H

