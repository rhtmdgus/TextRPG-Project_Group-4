#ifndef ENCOUNT_H
#define ENCOUNT_H

#include "utility.h"
#include "enemy.h"
#include "npc.h"
#include "potal.h"
#include "randomencount.h"

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

int encountRandom();
void encountRandomChoice();

int encountQuestItem();


#endif	//ENCOUNT_H