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


extern Enemy* currentEnemy;

void displayMap();
void displayShopMap();
void displayBattleScreen();
void displayPlayerStat();
void displayEnemyStat(const Enemy* enemy);
void displayShopScreen();

#endif // DISPLAYMAP_H