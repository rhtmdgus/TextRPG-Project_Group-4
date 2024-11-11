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

	// ���� �׸� �� ���� �ִ� ��� ���� �ٽ� ǥ���մϴ�.
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
	printf("  �������� ����: %3d", player.JRelationship);
	setCursorPosition(101, 11);
	printf("  �Ǻ����� ����: %3d", player.RRelationship);
	setCursorPosition(101, 12);
	printf("  �ֱ����� ����: %3d", player.WRelationship);
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
	printf("��ȣ�� ���� ��ǰ�� �����ϼ���.\n");
	setCursorPosition(40, 12);
	printf("1. ü�� ����  ���� ����: %d\n", Shop1.hpPotion);
	setCursorPosition(40, 13);
	printf("2. ���� ����  ���� ����: %d\n", Shop1.manaPotion);
	setCursorPosition(40, 14);
	printf("3. �� ����  ���� ����: %d\n", Shop1.strengthPotion);
	setCursorPosition(40, 15);
	printf("4. ���� ����  ���� ����: %d\n", Shop1.accuracyPotion);
	setCursorPosition(40, 16);
	printf("5. ��� ����  ���� ����: %d\n", Shop1.defensePotion);
	setCursorPosition(40, 17);
	printf("6. ������ ������.\n");

	displayPlayerStat();
	
	displayLog();
	int num = _getch();
	switch (num)
	{
	case '1':
		if (Shop1.hpPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		updateLog("ü�� ���� 1���� �����Ͽ����ϴ�.");
		player.HPpotion += 1;
		Shop1.hpPotion -= 1;
		break;
	case '2':
		if (Shop1.manaPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		updateLog("���� ���� 1���� �����Ͽ����ϴ�.");
		player.MPpotion += 1;
		Shop1.manaPotion -= 1;
		break;
	case '3':
		if (Shop1.strengthPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		updateLog("�� ���� 1���� �����Ͽ����ϴ�.");
		player.attack += 1;
		Shop1.strengthPotion -= 1;
		break;
	case '4':
		if (Shop1.accuracyPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		updateLog("���� ���� 1���� �����Ͽ����ϴ�.");
		player.accuracy += 1;
		Shop1.accuracyPotion -= 1;
		break;
	case '5':
		if (Shop1.defensePotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		updateLog("��� ���� 1���� �����Ͽ����ϴ�.");
		player.defense += 1;
		Shop1.defensePotion -= 1;
		break;
	case '6':
		updateLog("������ �����°� �����ϼ̽��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}