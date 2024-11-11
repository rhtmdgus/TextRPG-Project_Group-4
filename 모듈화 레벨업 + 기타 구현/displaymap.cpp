#include "displaymap.h"
#include <stdio.h>

void displayMap()
{
	system("cls");

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

	// 맵을 그린 후 남아 있는 모든 적을 다시 표시합니다.
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (currentEnemies[i].hp > 0) {
			drawEnemy(&currentEnemies[i]);
		}
	}
}


void displayBattleScreen()
{
	system("cls");
	//맵초기화
	initializeMapBattle();

	// 병사 1 (플레이어)
	int playerX = MAP_WIDTH / 2 - 5; // 중앙에 위치
	int playerY = MAP_HEIGHT / 2 - 2; // 중앙에 위치
	mapBattle[playerY][playerX] = 'P';  // 머리
	mapBattle[playerY + 1][playerX - 1] = '/';  // 왼팔
	mapBattle[playerY + 1][playerX] = '|'; // 몸
	mapBattle[playerY + 2][playerX] = '|'; // 몸
	mapBattle[playerY + 1][playerX + 1] = '\\'; // 오른팔
	mapBattle[playerY + 1][playerX + 2] = '/';//검
	mapBattle[playerY][playerX + 3] = '/';//검
	mapBattle[playerY + 2][playerX - 1] = '/';  // 왼다리
	mapBattle[playerY + 2][playerX] = ' '; // 빈 공간
	mapBattle[playerY + 2][playerX + 1] = '\\'; // 오른다리

	// 병사 2 (적군)
	int enemyX = MAP_WIDTH / 2 + 2; // 중앙에 위치
	int enemyY = MAP_HEIGHT / 2 - 2; // 중앙에 위치
	mapBattle[enemyY][enemyX] = 'E';   // 머리
	mapBattle[enemyY + 1][enemyX - 1] = '/';   // 왼팔
	mapBattle[enemyY + 1][enemyX - 2] = '\\';//검
	mapBattle[enemyY][enemyX - 3] = '\\';//검
	mapBattle[enemyY + 1][enemyX] = '|'; // 몸
	mapBattle[enemyY + 2][enemyX] = '|'; // 몸
	mapBattle[enemyY + 1][enemyX + 1] = '\\'; // 오른팔
	mapBattle[enemyY + 3][enemyX - 1] = '/';   // 왼다리
	mapBattle[enemyY + 3][enemyX] = ' '; // 빈 공간
	mapBattle[enemyY + 3][enemyX + 1] = '\\'; // 오른다리

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
	printf("  LEVEL: %d", player.level);
	setCursorPosition(101, 2);
	printf("  EXP: %3d / %3d", player.exp, EXPbar);
	setCursorPosition(101, 3);
	printf("  HP: %d", player.hp);
	setCursorPosition(101, 4);
	printf("  MANA: %d", player.mana);
	setCursorPosition(101, 5);
	printf("  attack point: %d", player.attack);
	setCursorPosition(101, 6);
	printf("  defense point: %d", player.defense);
	setCursorPosition(101, 7);
	printf("  accuracy point: %d", player.accuracy);
	setCursorPosition(101, 8);
	printf("  healing potion: %d", player.HPpotion);
	setCursorPosition(101, 9);
	printf("  mana potion: %d", player.MANApotion);
	setCursorPosition(101, 10);
	printf("  관군과의 관계: %d", player.JRelationship);
	setCursorPosition(101, 11);
	printf("  의병과의 관계: %d", player.RRelationship);
	setCursorPosition(101, 12);
	printf("  왜군과의 관계: %d", player.WRelationship);
}

void displayEnemyStat(const Enemy* enemy)
{
	if (enemy == nullptr) {
		printf("Error: Enemy data not available.\n");
		return;
	}
	setCursorPosition(101, 14);
	printf("%-70s", enemy->name);
	setCursorPosition(101, 15);
	printf("HP: %3d", enemy->hp);
	setCursorPosition(101, 16);
	printf("attack point: %3d", enemy->attack);
	setCursorPosition(101, 17);
	printf("defense point: %3d", enemy->defense);
}

