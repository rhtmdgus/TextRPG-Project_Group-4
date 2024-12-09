#include "displaymap.h"
#include "npc.h"
#include "player.h"
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
	for (int i = 0; i < MAX_BOSS; i++) {
		if (currentBosses[i].hp > 0) {
			drawBoss(&currentBosses[i]);
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


	printEnemy(currentEnemy);


}

void displayQuestScreen() {
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
}

void displayBossBattleScreen()
{
	system("cls");
	//���ʱ�ȭ
	initializeMapBattle();

	setColor(4);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", mapBattle[i][j]);
		}
		printf("\n");
	}
	setColor(7);
	printPlayer();


	printBoss(currentBoss);

}

void displayPlayerStat()
{
	setCursorPosition(101, 1);
	printf("  ����: %d", player.level);
	setCursorPosition(101, 2);
	printf("  ����ġ: %3d / %3d ����: %3d", player.exp, EXPbar, player.money);
	setCursorPosition(101, 3);
	printf("  ü��: %3d / %3d", player.hp, maxhp);
	setCursorPosition(101, 4);
	printf("  ���: %3d / %3d", player.mp, maxmp);
	setCursorPosition(101, 5);
	printf("  ü�� ����: %3d", player.HPpotion);
	setCursorPosition(101, 6);
	printf("  ��� ����: %3d", player.MPpotion);
	setCursorPosition(101, 7);
	printf("  ���ݷ�: %3d", player.attack);
	setCursorPosition(101, 8);
	printf("  ����: %3d", player.defense);
	setCursorPosition(101, 9);
	printf("  ���߷�: %3d", player.accuracy);
	setCursorPosition(101, 10);
	printf("  �������� ����: %3d", player.JRelationship);
	setCursorPosition(101, 11);
	printf("  �Ǻ����� ����: %3d", player.RRelationship);
	setCursorPosition(101, 12);
	printf("  �ֱ����� ����: %3d", player.WRelationship);

	setCursorPosition(101, 20);
	printf("  ����: %-15s", player.currentweaponName);
	setCursorPosition(101, 21);
	printf("  ���: %-15s", player.currentequipmentName);
}

void displayEnemyStat(const Enemy* enemy)
{
	if (enemy == nullptr) {
		printf("����: �� �����Ͱ� �����ϴ�.\n");
		return;
	}
	setCursorPosition(101, 14);
	printf("%-70s", enemy->name);
	setCursorPosition(101, 15);
	printf("ü��: %3d", enemy->hp);
	setCursorPosition(101, 16);
	printf("���ݷ�: %3d", enemy->attack);
	setCursorPosition(101, 17);
	printf("����: %3d", enemy->defense);
}

void displayBossStat(const Enemy* boss)
{
	if (boss == nullptr) {
		printf("����: �� �����Ͱ� �����ϴ�.\n");
		return;
	}
	setCursorPosition(101, 14);
	printf("%-70s", boss->name);
	setCursorPosition(101, 15);
	printf("ü��: %3d", boss->hp);
	setCursorPosition(101, 16);
	printf("���ݷ�: %3d", boss->attack);
	setCursorPosition(101, 17);
	printf("����: %3d", boss->defense);
}

void displayShopScreen()
{
	setCursorPosition(40, 11);
	printf("��ȣ�� ���� ��ǰ�� �����ϼ���.\n");
	setCursorPosition(40, 12);
	printf("1. ü�� ���� 2�� ���� ����: %d\n", Shop1.hpPotion);
	setCursorPosition(40, 13);
	printf("2. ��� ���� 2�� ���� ����: %d\n", Shop1.manaPotion);
	setCursorPosition(40, 14);
	printf("3. ���ݷ� ���� 10�� ���� ����: %d\n", Shop1.strengthPotion);
	setCursorPosition(40, 15);
	printf("4. ���� ���� 10�� ���� ����: %d\n", Shop1.defensePotion);
	setCursorPosition(40, 16);
	printf("5. ���߷� ���� 10�� ���� ����: %d\n", Shop1.accuracyPotion);
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
	if (strcmp(currentNPC->name, "������") == 0)
	{
		displayPlayerStat();
		displayLog();
		interactionNPC();
		clearScreen();
		displayLog();
	}
	else
	{
		outNpcInteract = 1;
		while (outNpcInteract == 1)
		{
			setCursorPosition(40, 11);
			printf("�� �̸��� %s.\n", currentNPC->name);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ����� ������?\n");
			setCursorPosition(40, 14);
			printf("2. �ֺ��� �ҹ��� �����̱�?\n");
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
}
void clearScreen()
{
	for (int i = 1; i < MAP_HEIGHT - 1; i++) 
	{
		setCursorPosition(35, i);
		for(int j = 35; j < MAP_WIDTH -1; j++)
			printf(" ");
	}
}