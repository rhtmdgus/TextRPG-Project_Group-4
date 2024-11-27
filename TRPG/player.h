#ifndef PLAYER_H
#define PLAYER_H

//#include "player.h"
#include "utility.h"

extern int EXPbar;
extern int maxhp;
extern int maxmp;
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
	int currentmap;
	int questitem1;
	int questitem2;
	int questitem3;
	int killcount;
	int questmax;
	int currentweapon;
	int currentequipment;
	char currentweaponName[20];
	char currentequipmentName[20];
	Position pos;
} Player;

// ���� �÷��̾� ��ü ����
extern Player player;

// Player ���� �Լ� ����
void drawPlayer();
void erasePlayer();
void movePlayer();


#endif // PLAYER_H