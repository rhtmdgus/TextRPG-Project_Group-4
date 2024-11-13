#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "enemy.h"			//��(enemy)���� ��� �� ����ü ����
#include "utility.h"		//�������� ���Ǵ� ��ƿ�� �Լ� �� ���� (ex. position, situation, Ŀ����ġ ��)
#include "startscreen.h"	//���� ���� ȭ�� ��� �Լ� ����
#include "initmap.h"		//�� �ʱ�ȭ �� �� ������ �ʿ��� ��� ����
#include "battle.h"			//���� ���� ��� ����
#include "log.h"			//���� �� �Ϲ� �α� ��� �� ��� ����
#include "displaymap.h"		//�Ϲ� �ʰ� �������� ��� �� ���� �Լ� ����
#include "player.h"			//�÷��̾� ���� ��� �� ����ü ����
#include "encount.h"		//��(enemy), ������, NPC���� ���� �� ��ȣ�ۿ� ����
#include "selectmap.h"
#include "shop.h"
#include "animation.h"


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



Player player = { 10, 10, 10, 5, 2, 2, 2, 1, 0, 0, 0, 0, 4, {1, 1} };
Position previousPos = { 1, 1 };
Shop Shop1 = { "����", 99, 99, 99, 99, 99, {3, 3} };


int main()
{
	start_screen();
	initializeMap();
	updateLog("Game started.");
	displayMap();
	displayPlayerStat();
	displayLog();
	spawnEnemies();

	while (1)
	{
		eraseCursor();
		drawPlayer();
		drawShop();
		movePlayer();
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
	}

	return 0;
}
