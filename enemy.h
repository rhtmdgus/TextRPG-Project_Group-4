#ifndef ENEMY_H
#define ENEMY_H

//#include "player.h"
#include "utility.h"

typedef struct
{
	char name[50];
	int hp;
	int attack;
	int defense;
	Position pos;
} Enemy;

Enemy createEnemy(const char* name, int hp, int attack, int defense, Position pos);
void drawEnemy(Enemy* enemy);
void eraseEnemy(Enemy* enemy);

#endif // ENEMY_H
