#ifndef BATTLE_H
#define BATTLE_H

#include "utility.h"
#include "enemy.h"
#include "prologue.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"
#include "animation.h"

extern int OriginalLevel;

extern Enemy* currentEnemy;
extern int Situation;      // �ܺο��� ����� Situation ���

void LevelUp();
void battle(Enemy* enemy);
int Crit();

#endif // BATTLE_H
