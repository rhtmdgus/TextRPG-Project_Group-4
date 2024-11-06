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

// 전역 플레이어 객체 선언
extern Player player;

// Player 관련 함수 선언
void drawPlayer();
void erasePlayer();
void movePlayer();


#endif // PLAYER_H
