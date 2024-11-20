#ifndef BOSS_H
#define BOSS_H

#include "utility.h"


typedef struct {
	char name[50];
	int hp;
	int attack;
	int defense;
	int appearMap;
	int weaponReward;
	int equipmentReward;

	Position pos;

} MiddleBoss;



typedef struct {
	char name[50];
	int hp;
	int attack;
	int defense;
	int appearMap;
	int weaponReward;
	int equipmentReward;

	Position pos;

} LastBoss;


extern MiddleBoss middleBoss[15];

extern LastBoss lastBoss[1];




#endif // BOSS_H