#include "displaymap.h"
#include <stdio.h>

void displayMap()
{
	system("cls");
	initializeMap();
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", map[i][j]);
		}

		if (i == 1) printf("  HP: %d", player.hp);
		if (i == 2) printf("  attack point: %d", player.attack);
		if (i == 3) printf("  defense point: %d", player.defense);
		if (i == 4) printf("  healing potion: %d", player.potion);

		printf("\n");
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

		if (i == 1) printf("  HP: %d", player.hp);
		if (i == 2) printf("  attack point: %d", player.attack);
		if (i == 3) printf("  defense point: %d", player.defense);
		if (i == 4) printf("  healing potion: %d", player.potion);

		printf("\n");
	}
	displayBattleLog();


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
