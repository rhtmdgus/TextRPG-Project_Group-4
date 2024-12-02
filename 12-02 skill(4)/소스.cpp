#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "enemy.h"			//적(enemy)관련 기능 및 구조체 정의
#include "utility.h"		//공통으로 사용되는 유틸성 함수 및 변수 (ex. position, situation, 커서위치 등)
#include "startscreen.h"	//게임 시작 화면 출력 함수 정의
#include "tutorialscreen.h"
#include "jobselect.h"
#include "initmap.h"		//맵 초기화 및 맵 구성에 필요한 상수 정의
#include "battle.h"			//전투 관련 기능 정의
#include "log.h"			//전투 및 일반 로그 기록 및 출력 관리
#include "displaymap.h"		//일반 맵과 전투맵의 출력 및 갱신 함수 정의
#include "player.h"			//플레이어 관련 기능 및 구조체 정의
#include "encount.h"		//적(enemy), 아이템, NPC와의 조우 및 상호작용 정의
#include "selectmap.h"
#include "shop.h"
#include "animation.h"
#include "npc.h"
#include "quest.h"
#include "prologue.h"
#include "prologuemap.h"
#include "item.h"


//situation 명 
//situation 1 = encounting enemy
//situation 2 = encounting shop
//situation 3 = displaying shop screen
//situation 4 = encounting NPC
//situation 5 = displaying NPC screen
//situation 6 = encount Quest item 1
//situation 7 = encount Quest item 2
//situation 8 = encount Quest item 3
//situation 9 = encounting portal

Player player = { 100, 100, 6, 5, 2, 2, 2, 20, 0, 0, 0, 0, 1, 100, 0, 0, 0, 0, 0, 0,  -1, -1, {"없음"} , {"헌 옷"} , 0, 0, 0, 0, 0, 0, {20, 13} };
Position previousPos = { 1, 1 };
Shop Shop1 = { "상인", 99, 99, 99, 99, 99, {3, 3} };

int main()
{
	eraseCursor();
	start_screen();
	system("cls");
	tutorial_screen();
	system("cls");
	updateLog("Game started.");

	initializeMap();
	displayMap_Prologue();
	displayLog();

	while (1)	//프롤로그
	{
		drawPotal_prologue();
		drawPlayer();
		spawnEnemies_P();
		drawNpc_prologue(npcListP);
		displayPlayerStat();
		movePlayer();

		if (encountPotal_prologue())		//프롤로그 포탈
		{
			updateLog("You encountered a potal!");
			Sleep(200);
			displayLog();
			updateLog("Press [A] to go next map or [R] to stay");
			Sleep(200);
			displayLog();

			while (Situation == 9)
			{
				encountPotal_prologueChoice();
			}
			if (Situation == 0) {
				displayMap_Prologue();
				displayPlayerStat();
				displayLog();
			}
		}

		if (encountNpc_prologue())		//프롤로그 NPC조우
		{
			updateLog("You encountered NPC!");
			updateLog("Press [A] to talk NPC or [R] to leave");
			displayLog();

			while (Situation == 4)
			{
				encountNpcChoice_prologue();
			}
			if (Situation == 0) {
				displayMap_Prologue();
				displayPlayerStat();
				displayLog();
			}
		}

		if (encountEnemy_P())			//프롤로그 enemy 조우
		{
			updateLog("You encountered an enemy!");
			Sleep(100);
			displayLog();
			updateLog("Press [A] to Attack or [R] to Run");
			Sleep(100);
			displayLog();

			while (Situation == 1)
			{
				encountChoice_P();
			}
			if (currentEnemy->hp <= 0) {
				updateLog("The enemy was defeated!");

				// 해당 적의 위치를 초기화
				eraseEnemy_P(currentEnemy);  // 해당 적만 지웁니다
				map[currentEnemy->pos.y][currentEnemy->pos.x] = ' ';

				// 적이 제거된 후 남아 있는 적들만 다시 그립니다.
				for (int i = 0; i < 3; i++) {
					if (currentEnemies_P[i].hp > 0) {
						drawEnemy_P(&currentEnemies_P[i]);
					}
				}

				// 플레이어와 로그를 개별 업데이트하여 깜빡임 최소화
				displayPlayerStat();
				displayLog();
			}
		}



		if (player.currentmap == 3)
		{
			player.currentmap = 0;
			system("cls");
			break;
		}
	}

	initializeMap();
	initializeQuest();
	displayMap();
	displayPlayerStat();
	displayLog();
	spawnEnemies();
	initializeNpc();
	initializeQuestItem();

	while (1)	//본편
	{
		eraseCursor();
		displayPlayerStat();
		drawPlayer();
		drawShop();
		movePlayer();
		drawPotal();
		drawNpc(npcList);
		drawQuestItem(QuestItemList);
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
		if (encountBoss())
		{
			updateLog("You encountered an boss!");
			Sleep(100);
			displayLog();
			updateLog("Press [A] to Attack or [R] to Run");
			Sleep(100);
			displayLog();

			while (Situation == 7)
			{
				encountBossChoice();
			}
			if (currentBoss->hp <= 0) {
				updateLog("The boss was defeated!");

				// 해당 보스의 위치를 초기화
				eraseBoss(currentBoss);  // 해당 보스만 지웁니다
				map[currentBoss->pos.y][currentBoss->pos.x] = ' ';

				// 적이 제거된 후 남아 있는 적들만 다시 그립니다.
				for (int i = 0; i < MAX_BOSS; i++) {
					if (currentBosses[i].hp > 0) {
						drawBoss(&currentBosses[i]);
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
		if (encountQuestItem())
		{
			while (Situation == 6)
			{
				interactionQuestItem();
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
	printf("                당신은 사망하였습니다                \n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                                                     \n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("           아무 키나 눌러 게임을 종료하세요!\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("           Press anykey to quit your adventure!\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n\n");



	eraseCursor();




	return 0;
}
