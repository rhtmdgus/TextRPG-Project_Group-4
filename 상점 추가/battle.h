#ifndef BATTLE_H
#define BATTLE_H

#include "utility.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"

extern Enemy* currentEnemy;
extern int Situation;      // �ܺο��� ����� Situation ���

void LevelUp();
void battle(Enemy* enemy);

#endif // BATTLE_H
