#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "enemy.h"			//적(enemy)관련 기능 및 구조체 정의
#include "utility.h"		//공통으로 사용되는 유틸성 함수 및 변수 (ex. position, situation, 커서위치 등)
#include "startscreen.h"	//게임 시작 화면 출력 함수 정의
#include "initmap.h"		//맵 초기화 및 맵 구성에 필요한 상수 정의
#include "battle.h"			//전투 관련 기능 정의
#include "log.h"			//전투 및 일반 로그 기록 및 출력 관리
#include "displaymap.h"		//일반 맵과 전투맵의 출력 및 갱신 함수 정의
#include "player.h"			//플레이어 관련 기능 및 구조체 정의
#include "encount.h"		//적(enemy), 아이템, NPC와의 조우 및 상호작용 정의
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
Shop Shop1 = { "상인", 99, 99, 99, 99, 99, {3, 3} };


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

				// 해당 적의 위치를 초기화
				eraseEnemy(currentEnemy);  // 해당 적만 지웁니다
				map[currentEnemy->pos.y][currentEnemy->pos.x] = ' ';

				// 적이 제거된 후 남아 있는 적들만 다시 그립니다.
				for (int i = 0; i < MAX_ENEMY; i++) {
					if (currentEnemies[i].hp > 0) {
						drawEnemy(&currentEnemies[i]);
					}
				}

				// 플레이어와 로그를 개별 업데이트하여 깜빡임 최소화
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
