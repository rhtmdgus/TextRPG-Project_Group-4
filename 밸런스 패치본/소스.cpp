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
//#include "randomencount.h"	//������ī��Ʈ ���� ���
#include "selectmap.h"
#include "shop.h"
#include "animation.h"
#include "npc.h"
#include "quest.h"
#include "prologue.h"
#include "prologuemap.h"
#include "item.h"
//������

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
//situation 10 = encounting random stuff

Player player = { 10, 10, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 1, 900, 0, 0, 0, 0, 0, 0,  -1, -1, {"����"} , {"�� ��"} , 0, 0, 0, 0, 0, 0, {20, 13} };
Position previousPos = { 1, 1 };
Shop Shop1 = { "����", 99, 99, 99, 99, 99, {3, 3} };

int main()
{
	eraseCursor();
	start_screen();
	system("cls");
	tutorial_screen();
	system("cls");
	updateLog("���� ����!");

	initializeMap();
	displayMap_Prologue();
	displayLog();

	while (1)	//���ѷα�
	{
		drawPotal_prologue();
		drawPlayer();
		spawnEnemies_P();
		drawNpc_prologue(npcListP);
		displayPlayerStat();
		movePlayer();

		if (encountPotal_prologue())		//���ѷα� ��Ż
		{
			updateLog("��Ż�� �߰��Ͽ����ϴ�.");
			Sleep(200);
			displayLog();
			updateLog("[A]Ű�� ���� ������ ������ [R]Ű�� ���� �ӹ��� �����Ͻʽÿ�.");
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

		if (encountNpc_prologue())		//���ѷα� NPC����
		{
			updateLog("NPC�� �������ϴ�!");
			updateLog("[A]Ű�� ���� ��ȭ���� [R]Ű�� ���� ������ �����Ͻʽÿ�.");
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

		if (encountEnemy_P())			//���ѷα� enemy ����
		{
			updateLog("���� �����ƽ��ϴ�!");
			Sleep(100);
			displayLog();
			updateLog("[A]Ű�� ���� �������� [R]Ű�� ���� ����ĥ�� �����Ͻʽÿ�.");
			Sleep(100);
			displayLog();

			while (Situation == 1)
			{
				encountChoice_P();
			}
			if (currentEnemy->hp <= 0) {
				updateLog("���� �����ƽ��ϴ�!");

				// �ش� ���� ��ġ�� �ʱ�ȭ
				eraseEnemy_P(currentEnemy);  // �ش� ���� ����ϴ�
				map[currentEnemy->pos.y][currentEnemy->pos.x] = ' ';

				// ���� ���ŵ� �� ���� �ִ� ���鸸 �ٽ� �׸��ϴ�.
				for (int i = 0; i < 3; i++) {
					if (currentEnemies_P[i].hp > 0) {
						drawEnemy_P(&currentEnemies_P[i]);
					}
				}

				// �÷��̾�� �α׸� ���� ������Ʈ�Ͽ� ������ �ּ�ȭ
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

	while (1)	//����
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
				printf("���� ����Ʈ�� �����ϼ̽��ϴ�!");
				updateLog("���� ����Ʈ�� �����ϼ̽��ϴ�!");
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
			updateLog("���� �����ƽ��ϴ�!");
			Sleep(100);
			displayLog();
			updateLog("[A]Ű�� ���� �������� [R]Ű�� ���� ����ĥ�� �����Ͻʽÿ�.");
			Sleep(100);
			displayLog();

			while (Situation == 1)
			{
				encountChoice();
			}
			if (currentEnemy->hp <= 0) {
				updateLog("���� �����ƽ��ϴ�!");

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
		if (encountBoss())
		{
			updateLog("�� ����� �����ƽ��ϴ�!");
			Sleep(100);
			displayLog();
			updateLog("[A]Ű�� ���� �������� [R]Ű�� ���� ����ĥ�� �����Ͻʽÿ�.");
			Sleep(100);
			displayLog();

			while (Situation == 7)
			{
				encountBossChoice();
			}
			if (currentBoss->hp <= 0) {
				updateLog("�� ����� �����ƽ��ϴ�!");

				// �ش� ������ ��ġ�� �ʱ�ȭ
				eraseBoss(currentBoss);  // �ش� ������ ����ϴ�
				map[currentBoss->pos.y][currentBoss->pos.x] = ' ';

				// ���� ���ŵ� �� ���� �ִ� ���鸸 �ٽ� �׸��ϴ�.
				for (int i = 0; i < MAX_BOSS; i++) {
					if (currentBosses[i].hp > 0) {
						drawBoss(&currentBosses[i]);
					}
				}

				// �÷��̾�� �α׸� ���� ������Ʈ�Ͽ� ������ �ּ�ȭ
				displayPlayerStat();
				displayLog();
			}
		}
		if (encountShop())
		{
			updateLog("������ �߰��߽��ϴ�!");
			updateLog("[A]Ű�� ���� ������ ���� [R]Ű�� ���� ������ �����Ͻʽÿ�.");
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
			updateLog("NPC�� �������ϴ�!");
			updateLog("[A]Ű�� ���� ��ȭ����[R]Ű�� ���� ������ �����Ͻʽÿ�.");
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
			updateLog("��Ż�� �߰��Ͽ����ϴ�!");
			updateLog("[A]Ű�� ���� ������ ������ [R]Ű�� ���� �ӹ��� �����Ͻʽÿ�.");
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
