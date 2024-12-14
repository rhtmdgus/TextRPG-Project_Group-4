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
#include "randevent.h"	//������ī��Ʈ ���� ���
#include "selectmap.h"
#include "shop.h"
#include "animation.h"
#include "npc.h"
#include "quest.h"
#include "prologue.h"
#include "prologuemap.h"
#include "item.h"
#include "ending.h"
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
//54
//situation 11 = prologue run ending
//situation 12 = prologue run ending choice

Player player = { 10, 10, 99, 2, 2, 2, 2, 20, 0, 0, 0, 0, 1, 30, 0, 0, 0, 0, 0, 0,  -1, -1, { "����" } , {"�� ��"} , 0, 0, 0, 0, 0, 0, 0, { 20, 13 } };
Position previousPos = { 1, 1 };
Shop Shop1 = { "����", 99, 99, 99, 99, 20, {3, 3} };

int main()
{
	eraseCursor();
	start_screen();
	system("cls");
	tutorial_screen();
	system("cls");
	startscene(); // �߰�
	system("cls");
	updateLog("���� ����!");
	/*
	initializeMap();
	printWakeUp();
	system("cls");

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
		if (encountRun())
		{
			updateLog("�������� �߰��߽��ϴ�!");
			displayLog();
			Sleep(100);
			updateLog("[A]Ű�� ���� ����ĥ�� [R]Ű�� ���� �������� ã���� �����Ͻʽÿ�.");
			displayLog();
			while (Situation == 11)
			{
				encountRunChoice();
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
		if (player.ending == 7)
			break;
	}

	if (player.ending == 7 && player.hp == 0) {
		runEnding();
	}
	*/
	
	initializeMap();
	initializeQuest();
	displayMap();
	displayPlayerStat();
	displayLog();
	spawnEnemies();
	spawnEvents();
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
		if (player.currentmap == 2 && quest[19].take == 0)
		{
			initializeMap();
			displayShopMap();
			displayPlayerStat();
			displayLog();
			NobodyLog_5();
			displayLog();
		}
		if (player.currentmap == 2 && checkboss3 == 1)
			QuestComplete19();
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

		//������ī��Ʈ
		if (encountRandom())
		{
			updateLog("�������� ������ ����� �����ϴ�!");
			updateLog("Ȯ���Ϸ��� [A]Ű��, �ƴϸ� [R]Ű�� ��������.");
			displayLog();

			while (Situation == 10)
			{
				encountRandomChoice();
			}
			if (Situation == 0) {

				// ���� ��ī���� �� ����
				for (int i = 0; i < MAX_EVENT; i++) {
					if (currentEvents[i].check != 0) {
						drawEvent(&currentEvents[i]);
					}
				}
				displayMap();
				displayPlayerStat();
				displayLog();
			}
		}

		if (encountHidden())
		{
			setColor(2);
			setCursorPosition(45, 14);
			printf("N");
			setCursorPosition(43, 17);
			printf("N");
			setCursorPosition(48, 16);
			printf("N");
			setCursorPosition(51, 13);
			printf("N");
			setCursorPosition(55, 18);
			printf("N");
			setCursorPosition(50, 19);
			printf("N");
			setColor(7);
			Sleep(500);
			updateLog("���������� �ѷ��׿�����.");
			displayLog();
			Sleep(500);
			updateLog("���� A: ������ �ݿ��ڴ�!");
			displayLog();
			Sleep(500);
			updateLog("���� B: �׾��! �����!!");
			displayLog();
			Sleep(500);
			updateLog("���� C: �뼭���� �ʰڴ�!");
			displayLog();
			Sleep(500);
			player.ending = 6;

			player.hp -= 9999;
		}

		if (player.hp <= 0)
		{
			break;
		}
		if (player.ending == 5) {
			potionEnding();
		}
		else if (player.ending == 6) {
			exeEnding();
		}
		else if (player.ending == 7) {
			runEnding();
		}


	}
	Sleep(500);

	system("cls");

	if (player.ending == 4) {
		deadEnding();
	}
	else if (player.ending == 5) {
		potionEnding();
	}
	else if (player.ending == 6) {
		exeEnding();
	}
	else if (player.ending == 7) {
		runEnding();
	}





	eraseCursor();




	return 0;
}
