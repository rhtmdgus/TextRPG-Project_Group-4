#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "enemy.h"
#include "utility.h"
#include "startscreen.h"
#include "initmap.h"
#include "battle.h"
#include "log.h"
#include "displaymap.h"
#include "player.h"


Player player = { 10, 10, 5, 2, {1, 1} };
Enemy Jap1 = createEnemy("왜군 잡졸", 10, 8, 3, {7, 10} );

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



int encountEnemy()
{
	if (map[player.pos.y][player.pos.x] == 'E')
	{
		Situation = 1;
		return 1;
	}
	else
	{
		Situation = 0;
		return 0;
	}
}

void encountChoice()
{
	char action = getch();

	switch (action)
	{
	default:
		updateLog("You choose the wrong key");
		updateLog("Press [A] to Attack or [R] to Run");
		break;
	case 'A':
	case 'a':
		updateLog("You decided to attack the enemy!");
		Sleep(100);
		displayBattleScreen();
		battle();
		break;
	case 'R':
	case 'r':
		updateLog("You ran away from the enemy!");
		updateLog("You fled from battle!");
		Situation = 0;
		break;
	}
	displayLog();
}



int main()
{
	start_screen();
	initializeMap();
	updateLog("Game started.");
	displayMap();
	displayLog();

	drawEnemy(&Jap1);
	map[Jap1.pos.y][Jap1.pos.x] = 'E';

	while (1)
	{
		eraseCursor();
		drawPlayer();
		movePlayer();
		displayLog();

		if (encountEnemy())
		{
			updateLog("You encountered an enemy!");
			updateLog("Press [A] to Attack or [R] to Run");
			displayLog();

			while (Situation == 1)
			{
				encountChoice();
			}
			if (Jap1.hp <= 0) {
				updateLog("The enemy was defeated!");
				initializeMap(); // 맵을 다시 초기화하여 적 제거
				displayMap();
				drawPlayer();
				displayLog();
			}
		}
	}


	return 0;
}