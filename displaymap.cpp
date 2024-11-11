#include "displaymap.h"
#include <stdio.h>

void displayMap()
{
	system("cls");

	map1_1();

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

	// ¸ÊÀ» ±×¸° ÈÄ ³²¾Æ ÀÖ´Â ¸ðµç ÀûÀ» ´Ù½Ã Ç¥½ÃÇÕ´Ï´Ù.
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (currentEnemies[i].hp > 0) {
			drawEnemy(&currentEnemies[i]);
		}
	}
}


void displayBattleScreen()
{
	system("cls");
	//¸ÊÃÊ±âÈ­
	initializeMapBattle();

	// º´»ç 1 (ÇÃ·¹ÀÌ¾î)
	int playerX = MAP_WIDTH / 2 - 5; // Áß¾Ó¿¡ À§Ä¡
	int playerY = MAP_HEIGHT / 2 - 2; // Áß¾Ó¿¡ À§Ä¡
	mapBattle[playerY][playerX] = 'P';  // ¸Ó¸®
	mapBattle[playerY + 1][playerX - 1] = '/';  // ¿ÞÆÈ
	mapBattle[playerY + 1][playerX] = '|'; // ¸ö
	mapBattle[playerY + 2][playerX] = '|'; // ¸ö
	mapBattle[playerY + 1][playerX + 1] = '\\'; // ¿À¸¥ÆÈ
	mapBattle[playerY + 1][playerX + 2] = '/';//°Ë
	mapBattle[playerY][playerX + 3] = '/';//°Ë
	mapBattle[playerY + 2][playerX - 1] = '/';  // ¿Þ´Ù¸®
	mapBattle[playerY + 2][playerX] = ' '; // ºó °ø°£
	mapBattle[playerY + 2][playerX + 1] = '\\'; // ¿À¸¥´Ù¸®

	// º´»ç 2 (Àû±º)
	int enemyX = MAP_WIDTH / 2 + 2; // Áß¾Ó¿¡ À§Ä¡
	int enemyY = MAP_HEIGHT / 2 - 2; // Áß¾Ó¿¡ À§Ä¡
	mapBattle[enemyY][enemyX] = 'E';   // ¸Ó¸®
	mapBattle[enemyY + 1][enemyX - 1] = '/';   // ¿ÞÆÈ
	mapBattle[enemyY + 1][enemyX - 2] = '\\';//°Ë
	mapBattle[enemyY][enemyX - 3] = '\\';//°Ë
	mapBattle[enemyY + 1][enemyX] = '|'; // ¸ö
	mapBattle[enemyY + 2][enemyX] = '|'; // ¸ö
	mapBattle[enemyY + 1][enemyX + 1] = '\\'; // ¿À¸¥ÆÈ
	mapBattle[enemyY + 3][enemyX - 1] = '/';   // ¿Þ´Ù¸®
	mapBattle[enemyY + 3][enemyX] = ' '; // ºó °ø°£
	mapBattle[enemyY + 3][enemyX + 1] = '\\'; // ¿À¸¥´Ù¸®

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", mapBattle[i][j]);
		}
		printf("\n");
	}

	/*
	setCursorPosition(100, 0);
	printf("What would you like to do?\n");
	setCursorPosition(100, 1);
	printf("1. Attack enemy\n");
	setCursorPosition(100, 2);
	printf("2. Drink potion\n");
	setCursorPosition(100, 3);
	printf("3. Run away!\n");
	*/
}

void displayPlayerStat()
{
	setCursorPosition(101, 1);
	printf("HP: %3d", player.hp);
	setCursorPosition(101, 2);
	printf("MP: %3d", player.mp);
	setCursorPosition(101, 3);
	printf("attack point: %3d", player.attack);
	setCursorPosition(101, 4);
	printf("defense point: %3d", player.defense);
	setCursorPosition(101, 5);
	printf("hp potion: %3d", player.hppotion);
	setCursorPosition(101, 6);
	printf("mp potion: %3d", player.mppotion);
}

void displayEnemyStat(const Enemy* enemy)
{
	if (enemy == nullptr) {
		printf("Error: Enemy data not available.\n");
		return;
	}

	setCursorPosition(101, 9);
	printf("%-70s", enemy->name);
	setCursorPosition(101, 10);
	printf("HP: %3d", enemy->hp);
	setCursorPosition(101, 11);
	printf("attack point: %3d", enemy->attack);
	setCursorPosition(101, 12);
	printf("defense point: %3d", enemy->defense);
}

