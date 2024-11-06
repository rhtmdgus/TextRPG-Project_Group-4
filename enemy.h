#ifndef ENEMY_H
#define ENEMY_H

//#include "player.h"
#include "utility.h"
#define MAX_ENEMY 5

typedef enum {
	warrior,  //�ֱ����� ����
	spear,   //�ֱ� â�� ����
	archor      //�ֱ� �ú� ����
} EnemyType;

typedef struct
{
	char name[50];
	int hp;
	int attack;
	int defense;
	Position pos;
	EnemyType type;
} Enemy;

extern Enemy enemyTemplates[3];
extern Enemy currentEnemies[MAX_ENEMY];
extern Enemy* currentEnemy;

Enemy createEnemy(const Enemy* enemyTemplate, Position pos);


int isPositionOccupied(int x, int y);
void spawnEnemies();
void drawEnemy(Enemy* enemy);
void eraseEnemy(Enemy* enemy);

#endif // ENEMY_H
