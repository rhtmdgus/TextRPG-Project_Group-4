#ifndef BATTLE_H
#define BATTLE_H

#include "utility.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"
#include "animation.h"

extern Enemy* currentEnemy;
extern Enemy* currentBoss;
extern int Situation;      // �ܺο��� ����� Situation ���

void LevelUp();
void battle(Enemy* enemy);
void bossbattle(Enemy* boss);

#endif // BATTLE_H
