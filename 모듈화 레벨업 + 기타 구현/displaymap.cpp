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

	// ���� �׸� �� ���� �ִ� ��� ���� �ٽ� ǥ���մϴ�.
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (currentEnemies[i].hp > 0) {
			drawEnemy(&currentEnemies[i]);
		}
	}
}


void displayBattleScreen()
{
	system("cls");
	//���ʱ�ȭ
	initializeMapBattle();

	// ���� 1 (�÷��̾�)
	int playerX = MAP_WIDTH / 2 - 5; // �߾ӿ� ��ġ
	int playerY = MAP_HEIGHT / 2 - 2; // �߾ӿ� ��ġ
	mapBattle[playerY][playerX] = 'P';  // �Ӹ�
	mapBattle[playerY + 1][playerX - 1] = '/';  // ����
	mapBattle[playerY + 1][playerX] = '|'; // ��
	mapBattle[playerY + 2][playerX] = '|'; // ��
	mapBattle[playerY + 1][playerX + 1] = '\\'; // ������
	mapBattle[playerY + 1][playerX + 2] = '/';//��
	mapBattle[playerY][playerX + 3] = '/';//��
	mapBattle[playerY + 2][playerX - 1] = '/';  // �޴ٸ�
	mapBattle[playerY + 2][playerX] = ' '; // �� ����
	mapBattle[playerY + 2][playerX + 1] = '\\'; // �����ٸ�

	// ���� 2 (����)
	int enemyX = MAP_WIDTH / 2 + 2; // �߾ӿ� ��ġ
	int enemyY = MAP_HEIGHT / 2 - 2; // �߾ӿ� ��ġ
	mapBattle[enemyY][enemyX] = 'E';   // �Ӹ�
	mapBattle[enemyY + 1][enemyX - 1] = '/';   // ����
	mapBattle[enemyY + 1][enemyX - 2] = '\\';//��
	mapBattle[enemyY][enemyX - 3] = '\\';//��
	mapBattle[enemyY + 1][enemyX] = '|'; // ��
	mapBattle[enemyY + 2][enemyX] = '|'; // ��
	mapBattle[enemyY + 1][enemyX + 1] = '\\'; // ������
	mapBattle[enemyY + 3][enemyX - 1] = '/';   // �޴ٸ�
	mapBattle[enemyY + 3][enemyX] = ' '; // �� ����
	mapBattle[enemyY + 3][enemyX + 1] = '\\'; // �����ٸ�

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
	printf("  �������� ����: %d", player.JRelationship);
	setCursorPosition(101, 11);
	printf("  �Ǻ����� ����: %d", player.RRelationship);
	setCursorPosition(101, 12);
	printf("  �ֱ����� ����: %d", player.WRelationship);
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

