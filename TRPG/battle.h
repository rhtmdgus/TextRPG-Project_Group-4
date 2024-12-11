#ifndef BATTLE_H
#define BATTLE_H

#include "utility.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"
#include "animation.h"
#include "questmanager.h"
#include "skill.h"

extern int OriginalLevel;

extern Enemy* currentEnemy;
extern Enemy* currentBoss;
extern int Situation;      // �ܺο��� ����� Situation ���

int Crit();
void LevelUp();
void battle(Enemy* enemy);
void bossbattle(Enemy* boss);
void battleRand(Enemy* enemy);

#endif // BATTLE_H
