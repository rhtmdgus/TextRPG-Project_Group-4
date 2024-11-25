#ifndef PROLOGUE_H
#define PROLOGUE_H

#include "utility.h"
#include "prologuemap.h"
#include "player.h"
#include "initmap.h"
#include "log.h"
#include "displaymap.h"
#include "jobselect.h"
#include "battle.h"
#include "enemy.h"
#include "animation.h"
#include "potion.h"

typedef struct
{
	char name[50];
	int currentmap;
	int nextmap;
	Position pos;
	Position playerNextPos;
	bool SpawnPotal_P;
}Potal_prologue;

extern int mapLogShown[3];

#define MAX_NPCP 3

typedef enum {
	Storage,	//Ã¢°í
	Deadbody,	//Á×Àº NPC
} NpcTypeP;

typedef struct
{
	char name[100];
	bool hasQuest;
	int currentmap;
	Position pos;
	NpcTypeP type;
} NpcDataP;

extern NpcDataP npcListP[MAX_NPCP];

void drawNpc_prologue(NpcDataP* npcListP);
extern NpcDataP* currentNPCP;

extern int outNpcInteract_prologue;
extern int checkingSpawnEnemy_P;


extern Enemy enemyTemplates_P[1];
extern Enemy currentEnemies_P[3];
extern int Enemy_PNum;

Enemy createEnemy_P(const Enemy* enemyTemplate, Position pos);
void spawnEnemies_P();
void drawEnemy_P(Enemy* enemy_P);
void eraseEnemy_P(Enemy* enemy_P);

int encountEnemy_P();
void encountChoice_P();

int encountNpc_prologue();
void encountNpcChoice_prologue();
void displayNPCScreen_prologue();

void selectPrologueMap();
void displayMap_Prologue();
void showTutorial();
void drawPotal_prologue();
void gotoNextMapPrologue();

int encountPotal_prologue();
void encountPotal_prologueChoice();
void interactionNPC_prologue();
void DeadbodyLog_1();
void DeadbodyLog_2();
void StorageLog();
void backToMap_prologue();

void battle_P(Enemy* enemy);

#endif // !PROLOGUE_H
