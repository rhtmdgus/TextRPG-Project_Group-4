#include "displaymap.h"
#include "npc.h"
#include <stdio.h>
#include <conio.h>

void displayMap()
{
	system("cls");

	selectmap();

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


	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", mapBattle[i][j]);
		}
		printf("\n");
	}

	printPlayer();


	printEnemy();


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
	interactShop();
	clearScreen();
	displayLog();
}

void displayNPCScreen()
{
	outNpcInteract = 1;
	while(outNpcInteract == 1)
	{
		setCursorPosition(40, 11);
		printf("�� �̸��� %s.\n", currentNPC->name);
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. ����� ������?\n");
		setCursorPosition(40, 14);
		printf("2.�ֺ��� �ҹ��� �����̱�?\n");
		setCursorPosition(40, 15);
		printf("3. �Ҹ��� �Ƿڴ� �ּ��̱�?\n");
		setCursorPosition(40, 16);
		printf("4. �ο���\n");
		setCursorPosition(40, 17);
		printf("6. NPC�� ������.\n");
		displayPlayerStat();
		displayLog();
		interactionNPC();
		clearScreen();
		displayLog();
	}
}

void clearScreen()
{
	for (int i = 1; i < MAP_HEIGHT - 1; i++) 
	{
		setCursorPosition(40, i);
		for(int j = 40; j < MAP_WIDTH -1; j++)
			printf(" ");
	}
}