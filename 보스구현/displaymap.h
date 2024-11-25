#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H

#include "utility.h"
#include "initmap.h"
#include "log.h"
#include "player.h"
#include "enemy.h"
#include "selectmap.h"
#include "shop.h"
#include "animation.h"
#include "npc.h"
#include "interaction.h"
#include "potal.h"

extern Enemy* currentEnemy;
extern NpcData* currentNPC;

void displayMap();
void displayShopMap();
void displayBattleScreen();
void displayBossBattleScreen();
void displayPlayerStat();
void displayEnemyStat(const Enemy* enemy);
void displayBossStat(const Enemy* boss);
void displayShopScreen();
void displayNPCScreen();

void clearScreen();
#endif // DISPLAYMAP_H