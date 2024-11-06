#ifndef PLAYER_H
#define PLAYER_H

//#include "player.h"
#include "utility.h"

typedef struct
{
	int hp;
	int attack;
	int defense;
	int potion;
	Position pos;
} Player;

// ���� �÷��̾� ��ü ����
extern Player player;

// Player ���� �Լ� ����
void drawPlayer();
void erasePlayer();
void movePlayer();


#endif // PLAYER_H
