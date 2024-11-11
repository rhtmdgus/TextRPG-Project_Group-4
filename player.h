#ifndef PLAYER_H
#define PLAYER_H

//#include "player.h"
#include "utility.h"

typedef struct
{
	int hp;
	int mp;
	int attack;
	int defense;
	int hppotion;
	int mppotion;
	Position pos;
} Player;

// ���� �÷��̾� ��ü ����
extern Player player;

// Player ���� �Լ� ����
void drawPlayer();
void erasePlayer();
void movePlayer();


#endif // PLAYER_H
