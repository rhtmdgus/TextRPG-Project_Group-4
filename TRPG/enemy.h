#ifndef ENEMY_H
#define ENEMY_H

//#include "player.h"
#include "utility.h"
#define MAX_ENEMY 10	//�� ���� ��
#define MAX_BOSS 3      //���� ������

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

extern Enemy enemyTemplates[14];
extern Enemy currentEnemies[MAX_ENEMY];
extern Enemy* currentEnemy;
extern Enemy currentBosses[MAX_BOSS];
extern Enemy* currentBoss;

Enemy createEnemy(const Enemy* enemyTemplate, Position pos);
Enemy createBoss(const Enemy* enemyTemplate, Position pos);

int isPositionOccupied(int x, int y);
void spawnEnemies();
void drawEnemy(Enemy* enemy);
void eraseEnemy(Enemy* enemy);
void spawnBoss1();
void spawnBoss2();
void spawnBoss3();
// void spawnBoss();
void drawBoss(Enemy* boss);
void eraseBoss(Enemy* boss);
void eraseAllEnemies();

#endif // ENEMY_H
