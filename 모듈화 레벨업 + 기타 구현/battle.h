#ifndef BATTLE_H
#define BATTLE_H

#include "utility.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"

extern Enemy* currentEnemy;
extern int Situation;      // 외부에서 선언된 Situation 사용

void LevelUp();
void battle(Enemy* enemy);

#endif // BATTLE_H
