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
#include "cutscene.h"

extern int OriginalLevel;

extern Enemy* currentEnemy;
extern Enemy* currentBoss;
extern int Situation;      // 외부에서 선언된 Situation 사용

int Crit();
void LevelUp();
void battle(Enemy* enemy);
void bossbattle(Enemy* boss);

#endif // BATTLE_H
