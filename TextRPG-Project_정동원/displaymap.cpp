#include "displaymap.h"
#include <stdio.h>
#include <conio.h>

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

	// 맵을 그린 후 남아 있는 모든 적을 다시 표시합니다.
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (currentEnemies[i].hp > 0) {
			drawEnemy(&currentEnemies[i]);
		}
	}
}

void displayShopMap()
{
	system("cls");

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
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
}

void displayPlayerStat()
{
	setCursorPosition(101, 1);
	printf("  LEVEL: %d", player.level);
	setCursorPosition(101, 2);
	printf("  EXP: %3d / %3d", player.exp, EXPbar);
	setCursorPosition(101, 3);
	printf("  HP: %3d", player.hp);
	setCursorPosition(101, 4);
	printf("  MP: %3d", player.mp);
	setCursorPosition(101, 5);
	printf("  attack point: %3d", player.attack);
	setCursorPosition(101, 6);
	printf("  defense point: %3d", player.defense);
	setCursorPosition(101, 7);
	printf("  accuracy point: %3d", player.accuracy);
	setCursorPosition(101, 8);
	printf("  healing potion: %3d", player.HPpotion);
	setCursorPosition(101, 9);
	printf("  mana potion: %3d", player.MPpotion);
	setCursorPosition(101, 10);
	printf("  관군과의 관계: %3d", player.JRelationship);
	setCursorPosition(101, 11);
	printf("  의병과의 관계: %3d", player.RRelationship);
	setCursorPosition(101, 12);
	printf("  왜군과의 관계: %3d", player.WRelationship);
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

void displayShopScreen()
{

	setCursorPosition(40, 11);
	printf("번호를 눌러 상품을 구매하세요.\n");
	setCursorPosition(40, 12);
	printf("1. 체력 포션  남은 갯수: %d\n", Shop1.hpPotion);
	setCursorPosition(40, 13);
	printf("2. 마나 포션  남은 갯수: %d\n", Shop1.manaPotion);
	setCursorPosition(40, 14);
	printf("3. 힘 포션  남은 갯수: %d\n", Shop1.strengthPotion);
	setCursorPosition(40, 15);
	printf("4. 명중 포션  남은 갯수: %d\n", Shop1.accuracyPotion);
	setCursorPosition(40, 16);
	printf("5. 방어 포션  남은 갯수: %d\n", Shop1.defensePotion);
	setCursorPosition(40, 17);
	printf("6. 상점을 떠난다.\n");

	displayPlayerStat();
	
	displayLog();
	int num = _getch();
	switch (num)
	{
	case '1':
		if (Shop1.hpPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("체력 포션 1개를 구매하였습니다.");
		player.HPpotion += 1;
		Shop1.hpPotion -= 1;
		break;
	case '2':
		if (Shop1.manaPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("마나 포션 1개를 구매하였습니다.");
		player.MPpotion += 1;
		Shop1.manaPotion -= 1;
		break;
	case '3':
		if (Shop1.strengthPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("힘 포션 1개를 구매하였습니다.");
		player.attack += 1;
		Shop1.strengthPotion -= 1;
		break;
	case '4':
		if (Shop1.accuracyPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("명중 포션 1개를 구매하였습니다.");
		player.accuracy += 1;
		Shop1.accuracyPotion -= 1;
		break;
	case '5':
		if (Shop1.defensePotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("방어 포션 1개를 구매하였습니다.");
		player.defense += 1;
		Shop1.defensePotion -= 1;
		break;
	case '6':
		updateLog("상점을 떠나는걸 선택하셨습니다.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}