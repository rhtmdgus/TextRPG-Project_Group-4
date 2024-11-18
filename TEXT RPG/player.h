#ifndef PLAYER_H
#define PLAYER_H

//#include "player.h"
#include "utility.h"

extern int EXPbar;
extern Position previousPos;

typedef struct
{
	int hp;
	int mp;
	int attack;
	int defense;
	int accuracy;
	int HPpotion;
	int MPpotion;
	int level;
	int exp;
	int JRelationship;
	int RRelationship;
	int WRelationship;
	int job;
	int money;
	int questitem;
	int currentmap;
	Position pos;
} Player;

// ���� �÷��̾� ��ü ����
extern Player player;

// Player ���� �Լ� ����
void drawPlayer();
void erasePlayer();
void movePlayer();


#endif // PLAYER_H