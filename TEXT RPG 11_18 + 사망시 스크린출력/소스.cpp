#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "enemy.h"			//��(enemy)���� ��� �� ����ü ����
#include "utility.h"		//�������� ���Ǵ� ��ƿ�� �Լ� �� ���� (ex. position, situation, Ŀ����ġ ��)
#include "startscreen.h"	//���� ���� ȭ�� ��� �Լ� ����
#include "tutorialscreen.h"
#include "jobselect.h"
#include "initmap.h"		//�� �ʱ�ȭ �� �� ������ �ʿ��� ��� ����
#include "battle.h"			//���� ���� ��� ����
#include "log.h"			//���� �� �Ϲ� �α� ��� �� ��� ����
#include "displaymap.h"		//�Ϲ� �ʰ� �������� ��� �� ���� �Լ� ����
#include "player.h"			//�÷��̾� ���� ��� �� ����ü ����
#include "encount.h"		//��(enemy), ������, NPC���� ���� �� ��ȣ�ۿ� ����
#include "selectmap.h"
#include "shop.h"
#include "animation.h"
#include "npc.h"
#include "quest.h"


/*
void displayBattleMap()
{
	int damageToPlayer;
	int damageToEnemy;
	system("cls");
	printf("=========== Battle Screen ===========\n");
	printf("You encountered an enemy!\n");
	printf("Press [A] to Attack or [R] to Run.\n");

	char action = getch();
	if (action == 'a' || action == 'A')
	{
		updateLog("You decided to attack the enemy!");

		while (Jap1.hp > 0 || player.hp > 0)
		{
			printf("What would you like to do?\n");
			printf("1. Attack enemy\n");
			printf("2. Drink potion\n");
			printf("3. Run away!\n");

			char actionBattle = getch();

			switch (actionBattle)
			{
			case '1':
				printf("You tried to attack the enemy!\n");
				damageToEnemy = player.attack - Jap1.defense;
				Jap1.hp -= damageToEnemy;
				printf("Enemy got %d damage!\n", damageToEnemy);

				printf("Enemy tried to attack you!\n");
				damageToPlayer = Jap1.attack - player.defense;
				player.hp -= damageToPlayer;
				printf("You got %d damage!\n", damageToPlayer);
				break;

			case '2':
				printf("You drinked potion!\n");
				player.hp += 5;
				break;
			case '3':
				printf("You could't run away from enemy!\n");
				Sleep(10);
				printf("Enemy tried to attack you!\n");
				damageToPlayer = Jap1.attack - player.defense;
				player.hp -= damageToPlayer;
				printf("You got %d damage!\n", damageToPlayer);
				break;
			}


		}
		map[Jap1.pos.y][Jap1.pos.x] = ' ';
	}


	else if (action == 'r' || action == 'R')
	{
		updateLog("You ran away from the enemy!");
		printf("You fled from battle!\n");
	}

	printf("Press any key to return to the game.\n");
	getch();

	displayMap();
	drawPlayer();
}
*/

//situation �� 
//situation 1 = encounting enemy
//situation 2 = encounting shop
//situation 3 = displaying shop screen
//situation 4 = encounting NPC
//situation 5 = displaying NPC screen
//situation 6 = encount Quest item 1
//situation 7 = encount Quest item 2
//situation 8 = encount Quest item 3
//situation 9 = encounting portal

Player player = { 10, 10, 10, 5, 2, 2, 2, 1, 0, 0, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, {1, 1} };
Position previousPos = { 1, 1 };
Shop Shop1 = { "����", 99, 99, 99, 99, 99, {3, 3} };
QuestItem1 questitem1 = { "����", 0, {15, 5} };
QuestItem2 questitem2 = { "���� ����", 0, {17, 5} };
QuestItem3 questitem3 = { "����", 0, {19, 5} };

int main()
{
	start_screen();
	system("cls");
	tutorial_screen();
	system("cls");
	jobSelect_screen();
	initializeMap();
	initializeQuest();
	updateLog("Game started.");
	displayMap();
	displayPlayerStat();
	displayLog();
	spawnEnemies();
	initializeNpc();

	while (1)
	{
		eraseCursor();
		displayPlayerStat();
		drawPlayer();
		drawShop();
		movePlayer();
		drawPotal();
		drawNpc(npcList);
		if (questitem1.used == 0 && player.currentmap == 0)
			drawQuestItem1();
		if (questitem2.used == 0 && player.currentmap == 0)
			drawQuestItem2();
		if (questitem3.used == 0 && player.currentmap == 0)
			drawQuestItem3();
		//displayLog();

		if (encountEnemy())
		{
			updateLog("You encountered an enemy!");
			Sleep(100);
			displayLog();
			updateLog("Press [A] to Attack or [R] to Run");
			Sleep(100);
			displayLog();

			while (Situation == 1)
			{
				encountChoice();
			}
			if (currentEnemy->hp <= 0) {
				updateLog("The enemy was defeated!");

				// �ش� ���� ��ġ�� �ʱ�ȭ
				eraseEnemy(currentEnemy);  // �ش� ���� ����ϴ�
				map[currentEnemy->pos.y][currentEnemy->pos.x] = ' ';

				// ���� ���ŵ� �� ���� �ִ� ���鸸 �ٽ� �׸��ϴ�.
				for (int i = 0; i < MAX_ENEMY; i++) {
					if (currentEnemies[i].hp > 0) {
						drawEnemy(&currentEnemies[i]);
					}
				}

				// �÷��̾�� �α׸� ���� ������Ʈ�Ͽ� ������ �ּ�ȭ
				displayPlayerStat();
				displayLog();
			}
		}

		if (encountShop())
		{
			updateLog("You encountered a shop!");
			updateLog("Press [A] to use Shop or [R] to leave");
			displayLog();
			while (Situation == 2)
			{
				encountShopChoice();
			}
			if (Situation == 0) {
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}

		if (encountNpc())
		{
			updateLog("You encountered NPC!");
			updateLog("Press [A] to talk NPC or [R] to leave");
			displayLog();

			while (Situation == 4)
			{
				encountNpcChoice();
			}
			if (Situation == 0) {
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}
		if (encountQuestItem1() && questitem1.used == 0 && player.currentmap == 0)
		{
			while (Situation == 6)
			{
				interactQuestItem1();
			}
			if (Situation == 0) {
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}
		if (encountQuestItem2() && questitem2.used == 0 && player.currentmap == 0)
		{
			while (Situation == 7)
			{
				interactQuestItem2();
			}
			if (Situation == 0) {
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}
		if (encountQuestItem3() && questitem3.used == 0 && player.currentmap == 0)
		{
			while (Situation == 8)
			{
				interactQuestItem3();
			}
			if (Situation == 0) {
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}
		if (encountPotal())
		{
			updateLog("You encountered a potal!");
			updateLog("Press [A] to go next map or [R] to stay");
			displayLog();

			while (Situation == 9)
			{
				encountPotalChoice();
			}
			if (Situation == 0) {
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}
		if (player.hp <= 0)
		{

			break;
		}

	}


	system("cls");
	for (int i = 0; i < (MAP_HEIGHT - 16) / 2; i++)
		printf("\n");

	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                                                     \n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                ����� ����Ͽ����ϴ�                \n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                                                     \n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("           �ƹ� Ű�� ���� ������ �����ϼ���!\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("           Press anykey to quit your adventure!\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n\n");



	eraseCursor();




	return 0;
}
