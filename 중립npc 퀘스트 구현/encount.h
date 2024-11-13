#ifndef ENCOUNT_H
#define ENCOUNT_H

#include "utility.h"
#include "enemy.h"
#include "npc.h"

extern Enemy* currentEnemy;
extern NpcData* currentNPC;

int encountEnemy();
void encountChoice();
int encountShop();
void encountShopChoice();
int encountNpc();
void encountNpcChoice();

#endif	//ENCOUNT_H