#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H

#include "utility.h"
#include "initmap.h"
#include "log.h"
#include "player.h"
#include "enemy.h"

extern Enemy* currentEnemy;

void displayMap();
void displayBattleScreen();
void displayPlayerStat();
void displayEnemyStat(const Enemy* enemy);

#endif // DISPLAYMAP_H