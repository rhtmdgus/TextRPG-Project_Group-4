#ifndef BOSS_H
#define BOSS_H

#include "utility.h"


typedef struct {
	char name[50];
	int hp;
	int attack;
	int defense;
	int weaponReward;
	int equipmentReward;

	Position pos;

} MiddleBoss;







#endif // BOSS_H