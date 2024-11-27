#ifndef ENCOUNT_H
#define ENCOUNT_H

#include "utility.h"
#include "enemy.h"
#include "npc.h"
#include "potal.h"

extern Enemy* currentEnemy;
extern NpcData* currentNPC;

int encountEnemy();
int encountBoss();
void encountChoice();
void encountBossChoice();
int encountShop();
void encountShopChoice();
int encountNpc();
void encountNpcChoice();
int encountPotal();
void encountPotalChoice();

int encountQuestItem();


#endif	//ENCOUNT_H