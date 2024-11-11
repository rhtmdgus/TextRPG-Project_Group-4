#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void drawPlayer()
{
	setCursorPosition(player.pos.x, player.pos.y);
	printf("P");
}
void erasePlayer()
{
	setCursorPosition(player.pos.x, player.pos.y);
	printf(" ");
}


void movePlayer()
{

	int key = 0;

	if (_kbhit() != 0)
		key = _getch();

	switch (key)
	{
	case 77://move to right
		if (player.pos.x < MAP_WIDTH - 2)
		{
			erasePlayer();
			player.pos.x++;
		}
		break;
	case 75://move to left
		if (player.pos.x > 1)
		{
			erasePlayer();
			player.pos.x--;
		}
		break;

	case 80:  // down block manual
		if (player.pos.y < MAP_HEIGHT - 2)
		{
			erasePlayer();
			player.pos.y++;
		}
		break;
	case 72:// rotation
		if (player.pos.y > 1)
		{
			erasePlayer();
			player.pos.y--;
		}
		break;
	}

	/*
	else if (map[player.pos.y][player.pos.x] == 'I')
	{
		player.hp += 5;
		updateLog("You found a potion! HP +5");
	}
	*/
}