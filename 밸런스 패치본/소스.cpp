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
//#include "randomencount.h"	//랜덤인카운트 전용 헤더
#include "selectmap.h"
#include "shop.h"
#include "animation.h"
#include "npc.h"
#include "quest.h"
#include "prologue.h"
#include "prologuemap.h"
#include "item.h"
//ㅇㅁㅇ

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
//situation 10 = encounting random stuff

Player player = { 10, 10, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 1, 900, 0, 0, 0, 0, 0, 0,  -1, -1, {"없음"} , {"헌 옷"} , 0, 0, 0, 0, 0, 0, {20, 13} };
Position previousPos = { 1, 1 };
Shop Shop1 = { "상인", 99, 99, 99, 99, 99, {3, 3} };

int main()
{
	eraseCursor();
	start_screen();
	system("cls");
	tutorial_screen();
	system("cls");
	updateLog("게임 시작!");

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
			updateLog("포탈을 발견하였습니다.");
			Sleep(200);
			displayLog();
			updateLog("[A]키를 눌러 마을을 떠날지 [R]키를 눌러 머물지 선택하십시오.");
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
			updateLog("NPC와 만났습니다!");
			updateLog("[A]키를 눌러 대화할지 [R]키를 눌러 떠날지 선택하십시오.");
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
			updateLog("적을 마주쳤습니다!");
			Sleep(100);
			displayLog();
			updateLog("[A]키를 눌러 전투할지 [R]키를 눌러 도망칠지 선택하십시오.");
			Sleep(100);
			displayLog();

			while (Situation == 1)
			{
				encountChoice_P();
			}
			if (currentEnemy->hp <= 0) {
				updateLog("적을 물리쳤습니다!");

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

		/*
		if (player.currentmap == 2)
		{
			spawnBoss3();
			setCursorPosition(40, 11);
			printf(quest[10].title);
			setCursorPosition(40, 12);
			printf(quest[10].description1);
			int choice = _getch();
			if (choice == 'a' || choice == 'A')
			{
				clearScreen();
				setCursorPosition(40, 11);
				printf("최종 퀘스트를 수락하셨습니다!");
				updateLog("최종 퀘스트를 수락하셨습니다!");
				quest[19].take = 1;
				player.questmax++;
				acceptQuest(19);
				backToDialogue();
				break;
			}
			QuestComplete19();
		}
		*/


		if (encountEnemy())
		{
			updateLog("적과 마주쳤습니다!");
			Sleep(100);
			displayLog();
			updateLog("[A]키를 눌러 전투할지 [R]키를 눌러 도망칠지 선택하십시오.");
			Sleep(100);
			displayLog();

			while (Situation == 1)
			{
				encountChoice();
			}
			if (currentEnemy->hp <= 0) {
				updateLog("적을 물리쳤습니다!");

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
			updateLog("적 장수와 마주쳤습니다!");
			Sleep(100);
			displayLog();
			updateLog("[A]키를 눌러 전투할지 [R]키를 눌러 도망칠지 선택하십시오.");
			Sleep(100);
			displayLog();

			while (Situation == 7)
			{
				encountBossChoice();
			}
			if (currentBoss->hp <= 0) {
				updateLog("적 장수를 물리쳤습니다!");

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
			updateLog("상점을 발견했습니다!");
			updateLog("[A]키를 눌러 상점에 들어갈지 [R]키를 눌러 떠날지 선택하십시오.");
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
			updateLog("NPC와 만났습니다!");
			updateLog("[A]키를 눌러 대화할지[R]키를 눌러 떠날지 선택하십시오.");
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
			updateLog("포탈을 발견하였습니다!");
			updateLog("[A]키를 눌러 마을을 떠날지 [R]키를 눌러 머물지 선택하십시오.");
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
		/**
		if (encountRandom())
		{
			updateLog("You encountered something!");
			updateLog("Press [A] to check or [R] to stay");
			displayLog();

			while (Situation == 10)
			{
				encountRandomChoice();
			}
			if (Situation == 0) {
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}
		*/
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
