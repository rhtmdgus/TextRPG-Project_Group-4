#ifndef BATTLE_H
#define BATTLE_H

#include "utility.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"

extern Enemy Jap1;         // 외부에서 선언된 Jap1 사용
extern Player player;      // 외부에서 선언된 player 사용
extern int Situation;      // 외부에서 선언된 Situation 사용

void battle();

#endif // BATTLE_H
