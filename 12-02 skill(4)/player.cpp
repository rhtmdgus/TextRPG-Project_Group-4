#include "player.h"
#include "questmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int EXPbar = 10;
int maxhp = 100;
int maxmp = 100;

void drawPlayer()
{
	setColor(1);
	setCursorPosition(player.pos.x, player.pos.y);
	printf("P");
	setColor(7);
}
void erasePlayer()
{
	setCursorPosition(player.pos.x, player.pos.y);
	printf(" ");
}


void movePlayer()
{

	int key = 0;

	if (_kbhit() != 0) {
		key = _getch();
		if (key == 'q' || key == 'Q') {
			printQuestWindow();  // 퀘스트 창 출력 함수 호출

		}
	}

	switch (key)
	{
	case 77://move to right
		if (player.pos.x < MAP_WIDTH - 2 && map[player.pos.y][player.pos.x + 1] != '#')
		{
			previousPos = player.pos;
			erasePlayer();
			player.pos.x++;
		}
		break;
	case 75://move to left
		if (player.pos.x > 1 && map[player.pos.y][player.pos.x - 1] != '#')
		{
			previousPos = player.pos;
			erasePlayer();
			player.pos.x--;
		}
		break;

	case 80:  // move to up
		if (player.pos.y < MAP_HEIGHT - 2 && map[player.pos.y + 1][player.pos.x] != '#')
		{
			previousPos = player.pos;
			erasePlayer();
			player.pos.y++;
		}
		break;
	case 72:// move to down
		if (player.pos.y > 1 && map[player.pos.y - 1][player.pos.x] != '#')
		{
			previousPos = player.pos;
			erasePlayer();
			player.pos.y--;
		}
		break;
	}
}