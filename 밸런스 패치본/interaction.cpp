#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "interaction.h"
#include "quest.h"

/*
setCursorPosition(40, 13);
	printf("1. ����� ������?\n");
	setCursorPosition(40, 14);
	printf("2.�ֺ��� �ҹ��� �����̱�?\n");
	setCursorPosition(40, 15);
	printf("3. �Ҹ��� �Ƿڴ� �ּ��̱�?\n");
	setCursorPosition(40, 16);
	printf("4. �ο���\n");
	setCursorPosition(40, 17);
	printf("6. NPC�� ������.\n");*/

int outNpcInteract = 0;

void interactionNPC()
{
	if (currentNPC->type == VolunArmy)
		dialogueVolunArmy();
	else if (currentNPC->type == GoverArmy)
		dialogueGoverArmy();
	else if (currentNPC->type == JapArmy)
		dialogueJapArmy();
	else if (currentNPC->type == Nobody)
		dialogueNobody();
}

void interactShop() {
	int num = _getch();
	switch (num)
	{
	case '1':
		if (player.money - hpPotionPrice < 0)
		{
			updateLog("������ �ִ� ���� ������ �����մϴ�.");
			break;
		}
		else if (Shop1.hpPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		else
		{
			updateLog("ü�� ���� 1���� �����Ͽ����ϴ�.");
			player.HPpotion += 1;
			Shop1.hpPotion -= 1;
			player.money -= hpPotionPrice;
		}
		break;
	case '2':
		if (player.money - manaPotionPrice < 0)
		{
			updateLog("������ �ִ� ���� ������ �����մϴ�.");
			break;
		}
		else if (Shop1.manaPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		else
		{
			updateLog("���� ���� 1���� �����Ͽ����ϴ�.");
			player.MPpotion += 1;
			Shop1.manaPotion -= 1;
			player.money -= manaPotionPrice;
		}
		break;
	case '3':
		if (player.money - strengthPotionPrice < 0)
		{
			updateLog("������ �ִ� ���� ������ �����մϴ�.");
			break;
		}
		else if (Shop1.strengthPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		else
		{
			updateLog("�� ���� 1���� �����Ͽ����ϴ�.");
			player.attack += 1;
			Shop1.strengthPotion -= 1;
			player.money -= strengthPotionPrice;
		}
		break;
	case '4':
		if (player.money - defensePotionPrice < 0)
		{
			updateLog("������ �ִ� ���� ������ �����մϴ�.");
			break;
		}
		else if (Shop1.accuracyPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		else
		{
			updateLog("��� ���� 1���� �����Ͽ����ϴ�.");
			player.defense += 1;
			Shop1.defensePotion -= 1;
			player.money -= defensePotionPrice;
		}
		break;
	case '5':
		if (player.money - accuracyPotionPrice < 0)
		{
			updateLog("������ �ִ� ���� ������ �����մϴ�.");
			break;
		}
		else if (Shop1.accuracyPotion <= 0)
		{
			updateLog("��ǰ ������ �����մϴ�.");
			break;
		}
		else
		{
			updateLog("���� ���� 1���� �����Ͽ����ϴ�.");
			player.accuracy += 1;
			Shop1.accuracyPotion -= 1;
			player.money -= accuracyPotionPrice;
		}
		break;
	case '6':
		updateLog("������ �����°� �����ϼ̽��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}

void backToDialogue()
{
	while (1) {
		char action = _getch();
		switch (action) {
		case 'A':
		case 'a':
			return;  // 'A'�� 'a' Ű�� ������ �Լ� �����Ͽ� ���� ��ȭ�� ���ư���

		default:
			updateLog("�߸��� Ű�� �Է��߽��ϴ�. AŰ�� ���� ���� ��ȭ�� ���ư���");
			displayLog();
			break;
		}
	}
}

void backToMap()
{
	while (1) {
        char action = _getch();
        switch (action) {
            case 'A':
            case 'a':
                outNpcInteract = 0;  // NPC ��ȭ ��� ����
                Situation = 0;
                player.pos = previousPos;  // �÷��̾ ���� ��ġ�� ����
                return;  // �Լ� ����

            default:
                updateLog("�߸��� Ű�� �Է��߽��ϴ�. AŰ�� ���� ������ ���ư���");
                displayLog();
                break;
        }
    }
}

void dialogueVolunArmy()
{
	if (strcmp(currentNPC->name, "������") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_1();
	if (strcmp(currentNPC->name, "���ȯ") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_2();
	if (strcmp(currentNPC->name, "�迵��") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_3();
	if (strcmp(currentNPC->name, "�蹫��") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_4();
	if (strcmp(currentNPC->name, "����ö") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_5();
}

void VolunArmyLog_1()
{
	Sleep(100);
	clearScreen();
	if (currentNPC->hasQuest == true && quest[5].clear == 0 && currentNPC->isActive == 1)
	{
		setCursorPosition(30, 11);
		printf(quest[5].title);
		setCursorPosition(30, 12);
		printf(quest[5].description1);
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �λ���� �Ǻ����� ü�¹��� �ϳ��� �ش�.\n");
		setCursorPosition(30, 15);
		printf("2. �λ���� �Ǻ��� ���� �ʴ´�.\n");
		int choice = _getch();
		if (choice == '1')
		{
			if (player.HPpotion < 1)
			{
				clearScreen();
				updateLog("������ �ִ� ü�¹����� �����մϴ�.");
				Sleep(200);
				displayLog();
				setCursorPosition(30, 11);
				printf(quest[5].description2);
				setCursorPosition(30, 12);
				printf("�̾��Ͽ�\n");
				quest[5].clear = 2;
				npcList[5].isActive = 0;
				backToMap();
			}
			else
			{
				clearScreen();
				updateLog("�λ���� �Ǻ����� ü�¹����� �־����ϴ�.");
				Sleep(200);
				displayLog();
				player.RRelationship += 20;
				player.HPpotion--;
				setCursorPosition(30, 11);
				printf(quest[5].description4);
				quest[5].clear = 1;
				backToMap();
			}
		}
		else if (choice == '2')
		{
			clearScreen();
			updateLog("�λ���� �Ǻ����� ü�¹����� ���� �ʱ�� �Ͽ����ϴ�.");
			Sleep(200);
			displayLog();
			setCursorPosition(30, 11);
			printf(quest[5].description2);
			setCursorPosition(30, 12);
			printf("�̾��Ͽ�\n");
			quest[5].clear = 2;
			npcList[5].isActive = 0;
			backToMap();
		}
	}
	else if (quest[5].clear == 1 && currentNPC->isActive == 1)
	{
		clearScreen();
		setCursorPosition(30, 11);
		printf("�Ǻ��� �����ִ�. �ǵ帮�� ����.");
		backToMap();
	}
	Sleep(150);
	backToMap();
}

void VolunArmyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �� ������ �Ǻ��̴�.");
		setCursorPosition(30, 12);
		printf("�������� ���� ������ �����ϸ� ������� ����");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�鸮�� ���δ� ������ ��ó ������ ��Ż�ϰ� �ִٴ���.");
		setCursorPosition(30, 12);
		printf("�����ϴ� �� ���� �ž�,");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[1].clear == 0)
		{
			if (quest[1].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[1].title);
				setCursorPosition(30, 12);
				printf(quest[1].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[1].take = 1;
						player.questmax++;
						acceptQuest(1);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[1].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[1].take == 1)
			{
				QuestComplete2();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[1].clear == 1) {
			clearScreen();
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �� ģ��鿡�� �ѹ� ����ڼ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� ���� �峭�ϴ� �ǰ�? ���� ����");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰���, �ֳ�� �����ϰ�");
		backToMap();
		break;
	}
}
void VolunArmyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("��? �׳� ������� ����ε�,");
		setCursorPosition(30, 12);
		printf("�����뿡 ����ĥ ���� ���� ���� ����");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("������ ���� �������� �����ϰ� �ִٴ� �ҹ��� �־�.");
		setCursorPosition(30, 12);
		printf("��� �ܴ��� �ؾ߰ھ�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[10].clear == 0)
		{
			if (quest[10].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[10].title);
				setCursorPosition(30, 12);
				printf(quest[10].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[10].take = 1;
						player.questmax++;
						acceptQuest(10);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[10].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[10].take == 1)
			{
				QuestComplete10();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[10].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�? ģ�������� �ѹ� �����.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("��� ���� ����̱�");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰�, �� �����ϰ�");
		backToMap();
		break;
	}
}
void VolunArmyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���忡�� ������ �� �μ��� �Ǻ��̴�.");
		setCursorPosition(30, 12);
		printf("���� ���� ������ ���� ����.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�屺���� ���ο� ������ ������ ��Ŵٴ���,");
		setCursorPosition(30, 12);
		printf("�ʵ� ������ �� ���� �ֳ�?");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[11].clear == 0)
		{
			if (quest[11].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[11].title);
				setCursorPosition(30, 12);
				printf(quest[11].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[11].take = 1;
						player.questmax++;
						acceptQuest(11);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[11].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[11].take == 1)
			{
				QuestComplete11();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[11].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �ٸ� ����鲲 �ѹ� ����ڼ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �ʹ� ���Ѱ� �ƴѰ�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ð�, �ֳ�� �����ϰ�");
		backToMap();
		break;
	}
}
void VolunArmyLog_5()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �������� �߿�ġ �ʾ�,");
		setCursorPosition(30, 12);
		printf("�� ���� ���� �ο�� �Ǻ��� ���̴�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ҹ��̾� ����, ������ ���� ���¸� �˰� �ʹٸ�,");
		setCursorPosition(30, 12);
		printf("���¥�⿡ �ִ� �������� ã�ƺ�");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[12].clear == 0)
		{
			if (quest[12].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[12].title);
				setCursorPosition(30, 12);
				printf(quest[12].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[12].take = 1;
						player.questmax++;
						acceptQuest(12);
						backToDialogue();
						spawnBoss2();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[12].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[12].take == 1)
			{
				QuestComplete12();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[12].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �ٸ� �屺�鿡�� �ѹ� ����ڼ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� ���᳢�� �̷����?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ÿ�, �� �����ϰ�");
		backToMap();
		break;
	}
}
void dialogueGoverArmy()
{
	if (strcmp(currentNPC->name, "���û�") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_1();
	if (strcmp(currentNPC->name, "������") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_2();
	if (strcmp(currentNPC->name, "������") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_3();
	if (strcmp(currentNPC->name, "������") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_4();
	if (strcmp(currentNPC->name, "��â��") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_5();
}

void GoverArmyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� ���� �����̴�.");
		setCursorPosition(30, 12);
		printf("�� ���￡�� ���� ��Ű�� �� �� �ӹ���.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ֱ��� ����� �ؾȰ��� ���� �ƴٴ� ������ ���Դ�.");
		setCursorPosition(30, 12);
		printf("�� ������ ��� �����ϰ� �־�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[6].clear == 0)
		{
			if (quest[6].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[6].title);
				setCursorPosition(30, 12);
				printf(quest[6].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[6].take = 1;
						player.questmax++;
						acceptQuest(6);
						backToDialogue();
						spawnBoss1();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[6].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[6].take == 1)
			{
				QuestComplete6();			
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[6].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �屺�Բ� �ѹ� ����ڼ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� ���� �����ϴ� ���ΰ�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰���, �ֳ�� �����ϰ�");
		backToMap();
		break;
	}
}

void GoverArmyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("������ ���� �޾� �̰��� ��Ű�� �ִ�.");
		setCursorPosition(30, 12);
		printf("���� ����ġ�� ���� �ο�� �����.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("��ó���� �Ǻ���� ������ ������ ����� �ִٰ� ��,");
		setCursorPosition(30, 12);
		printf("������ ������ ���� ��ȹ�̶� ������ �ʿ������� �𸣰ڱ�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[2].clear == 0)
		{
			if (quest[2].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[2].title);
				setCursorPosition(30, 12);
				printf(quest[2].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[2].take = 1;
						player.questmax++;
						acceptQuest(2);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[2].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[2].take == 1)
			{
				QuestComplete3();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[2].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �ٸ� �屺�鲲 �ѹ� �����.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �ݶ��� �� �����ΰ�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ð�, �� �����ϰ�");
		backToMap();
		break;
	}
}
void GoverArmyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �� ������ ����ϴ� ���� �屳��.");
		setCursorPosition(30, 12);
		printf("���� ������ ������ �� ���ΰ�?");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("������ ���� ���� �ð� �ִٴ� �ҹ��� �ִ�.");
		setCursorPosition(30, 12);
		printf("���� �غ�� ö���� �ؾ� �� ���̴�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[13].clear == 0)
		{
			if (quest[13].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[13].title);
				setCursorPosition(30, 12);
				printf(quest[13].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[13].take = 1;
						player.questmax++;
						acceptQuest(13);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[13].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[13].take == 1)
			{
				QuestComplete13();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[13].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �ٸ� �屺���� �ѹ� �����.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("��� ������ �׸��ϰ�");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ð�, �ֱ��� �����ϰ�");
		backToMap();
		break;
	}
}
void GoverArmyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�������� �ñ��� �ϴ� ������ �ֳ�?");
		setCursorPosition(30, 12);
		printf("�� ���� ���� ���� �ο�� ���� ���̾�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("����� ���¥�⿡�� �ǹ��� �������� ���� �Ǿ��ٰ� �Ѵ�.");
		setCursorPosition(30, 12);
		printf("�ֱ��� ø������, �Ǻ������� ���� �˼��� ����.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[14].clear == 0)
		{
			if (quest[14].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[14].title);
				setCursorPosition(30, 12);
				printf(quest[14].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[14].take = 1;
						player.questmax++;
						acceptQuest(14);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[14].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[14].take == 1)
			{
				QuestComplete14();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[14].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �������� �ѹ� ����ڼ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �ֱ��� ���� ��� ���ΰ�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰�, �� �����ϰ�");
		backToMap();
		break;
	}
}
void GoverArmyLog_5()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�� ���� �𸣰ڼ�? �ֺ� ������ �� �������ݼ�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ٴٿ� �̼��� �屺�Բ��� Ȧ�� �ֱ��� ����� �ִٰ� �����.");
		setCursorPosition(30, 12);
		printf("�㳪 �� ���� �û��ϴ� �ڵ��� ���� ������");
		setCursorPosition(30, 13);
		printf("�������� ���ڸ� ��Ƶ鿩�� �Ѵٴ� ��ģ �Ҹ��� ���� �ּ�.");
		setCursorPosition(30, 14);
		printf("��ȭ��\n");
		setCursorPosition(30, 15);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[15].clear == 0)
		{
			if (quest[15].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[15].title);
				setCursorPosition(30, 12);
				printf(quest[15].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[15].take = 1;
						player.questmax++;
						acceptQuest(15);
						backToDialogue();
						spawnBoss2();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[15].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[15].take == 1)
			{
				QuestComplete15();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[15].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, ������ �ѹ� ����ڼ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� ���� �ϴ� ���ΰ�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ÿ�, ȥ���� �ô��̴� �� �����ϰ�.");
		backToMap();
		break;
	}
}

void dialogueJapArmy()
{
	if (strcmp(currentNPC->name, "�̿� �ͻ�η�") == 0 && currentNPC->hasQuest == true && currentNPC->isActive == 1)
		JapArmyLog_1();
	if (strcmp(currentNPC->name, "�����") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_2();
	if (strcmp(currentNPC->name, "������") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_3();
	if (strcmp(currentNPC->name, "�ƻ��") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_4();
	if (strcmp(currentNPC->name, "������") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_5();
}

void JapArmyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�׳��� ���� �ֱ� ��� ���� �ͻ�ηδ�");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�� ���� ��� �����ϴ����� �𸣰ڴٸ�");
		setCursorPosition(30, 12);
		printf("�츮�� ������ �����Ϸ� �� ���� �ƴ� �ع��Ű�� �� �Ŵ�");
		setCursorPosition(30, 13);
		printf("�׷��� Ǯ���ִ°� ���� �����Ŵ�");
		setCursorPosition(30, 14);
		printf("��ȭ��\n");
		setCursorPosition(30, 15);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("���ϴ� ���� �ּ�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[7].clear == 0)
		{
			if (quest[7].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[7].title);
				setCursorPosition(30, 12);
				printf(quest[7].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[7].take = 1;
						player.questmax++;
						acceptQuest(7);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[7].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �׷��� ������ �ʼ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[7].take == 1)
			{
				QuestComplete7();
				if (currentNPC->isActive == 0)
				{
					backToMap();
					break;
				}
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[7].clear == 1) {
			//break;
			setCursorPosition(30, 11);
			printf(" ");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�� �Ҹ��� �ϴ°ž�!");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("������� ��.");
		backToMap();
		break;
	}
}

void JapArmyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �Ϻ� �뱺�� �Ͽ��̴�.");
		setCursorPosition(30, 12);
		printf("�츮 ���� ������ �� �˰� �� ���̴�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�鸮�� �ҹ����δ� ������ ������ �����ϰ� �ִٴ���,");
		setCursorPosition(30, 12);
		printf("���� �׳��� �� �ҹ��� �ٲܼ� ������?");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[3].clear == 0)
		{
			if (quest[3].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[3].title);
				setCursorPosition(30, 12);
				printf(quest[3].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[3].take = 1;
						player.questmax++;
						acceptQuest(3);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[3].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[3].take == 1)
			{
				QuestComplete4();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[3].clear == 1) {
			setCursorPosition(30, 11);
			printf("������ ���� ��ų���� ���� ���� �� ������?");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("��ī�߷�!");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ٸ� ���ó�� �ൿ���� ����");
		backToMap();
		break;
	}
}
void JapArmyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �ֱ��� �������.");
		setCursorPosition(30, 12);
		printf("������ �츮 �� �ؿ��� ����� ����̴�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("������ �Ǻ��̶�..");
		setCursorPosition(30, 12);
		printf("��ε��� ��� �Ͼ�� �ѵ�,");
		setCursorPosition(30, 13);
		printf("�츮 ������ �ƹ��� ������ ���� �ʴ´�.");
		setCursorPosition(30, 14);
		printf("��ȭ��\n");
		setCursorPosition(30, 15);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[16].clear == 0)
		{
			if (quest[16].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[16].title);
				setCursorPosition(30, 12);
				printf(quest[16].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[16].take = 1;
						player.questmax++;
						acceptQuest(16);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[16].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[16].take == 1)
			{
				QuestComplete16();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[16].clear == 1) {
			setCursorPosition(30, 11);
			printf("������ ���� ��ų���� ���� ����.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���ڱ� ���� ��Ҹ���?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�� ���Գ�");
		backToMap();
		break;
	}
}
void JapArmyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�׷��� �� ���°���?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�������� ���ο� ������ �����ϰ� �ִٴ���,");
		setCursorPosition(30, 12);
		printf("������ �츮���� ���� ���ο� ���հ��� ���̾�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[17].clear == 0)
		{
			if (quest[17].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[17].title);
				setCursorPosition(30, 12);
				printf(quest[17].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[17].take = 1;
						player.questmax++;
						acceptQuest(17);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[17].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[17].take == 1)
			{
				QuestComplete17();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[17].clear == 1) {
			setCursorPosition(30, 11);
			printf("��? ���� ���µ� �ѹ� ã�ƺ���.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���ڱ� ���̷�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� ������ ������ �����ϰ� �ͱ���");
		backToMap();
		break;
	}
}
void JapArmyLog_5()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("��������� ó�μ� �Ϻ��� �屺�̴�.");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ҹ�? ���￡�� �ҹ� ���ٴ� ��������.");
		setCursorPosition(30, 12);
		printf("���� �츮 �Ϻ����� ���� �����.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[18].clear == 0)
		{
			if (quest[18].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[18].title);
				setCursorPosition(30, 12);
				printf(quest[18].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[18].take = 1;
						player.questmax++;
						acceptQuest(18);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[18].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[18].take == 1)
			{
				QuestComplete18();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[18].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �� ���� ����.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�����̳�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�츮 �ֱ��� ������ �������� �����ʾҴ�.");
		backToMap();
		break;
	}
}
void dialogueNobody()
{
	if (strcmp(currentNPC->name, "�� ����") == 0 && currentNPC->hasQuest == true)
		NobodyLog_1();
	if (strcmp(currentNPC->name, "�� �ƹ���") == 0 && currentNPC->hasQuest == true)
		NobodyLog_2();
	if (strcmp(currentNPC->name, "���ϵ�") == 0 && currentNPC->hasQuest == true)
		NobodyLog_3();
	if (strcmp(currentNPC->name, "����") == 0 && currentNPC->hasQuest == true)
		NobodyLog_4();
}


//����Ʈ ���� ���Ҽ� NPC �α�
void NobodyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �׳� ����� ����̿�.");
		setCursorPosition(30, 12);
		printf("���ﶧ���� ���� ��Ⱑ ���鱺..");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ֱ����� �̵��� �����׸� ��Ż�Ѵٰ� �����.");
		setCursorPosition(30, 12);
		printf("������ ���� �ͼ� �츮 �� ���������� �ϴµ�,");
		setCursorPosition(30, 13);
		printf("������ �ȿ°� ����, �ҽ��� �������� �������� ���߳�����.");
		setCursorPosition(30, 14);
		printf("��ȭ��\n");
		setCursorPosition(30, 15);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[0].clear == 0)
		{
			if (quest[0].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[0].title);
				setCursorPosition(30, 12);
				printf(quest[0].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[0].take = 1;
						player.questmax++;
						acceptQuest(0);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[0].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[0].take == 1)
			{
				QuestComplete1();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[0].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, ���ƿ� ���� ����ÿ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ֱ����� �밡���� �����̼�??");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ÿ�, �ֳ�� �����ϰ�");
		backToMap();
		break;
	}
}//����Ʈ ���� NPC//
//����Ʈ �ִ� ���Ҽ� NPC �α�
void NobodyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� ���� ����� ����� ���̳�,");
		setCursorPosition(30, 12);
		printf("�����뿡 �� �� �ʹ����� ����.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �ϴ��� �ҹ��� ���� ƴ�� ���ٳ�.");
		setCursorPosition(30, 12);
		printf("��ó ��ݵ��� ���δ� �ǳ��� ��������.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[4].clear == 0)
		{
			if (quest[4].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[4].title);
				setCursorPosition(30, 12);
				printf(quest[4].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[4].take = 1;
						player.questmax++;
						acceptQuest(4);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[4].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[4].take == 1)
			{
				QuestComplete5();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[4].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڴµ�, �������� �����°� ���?");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("����� �װڴµ� �׷� �峭 ���� ���ÿ�.");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ÿ�, �� �����ϰ�");
		backToMap();
		break;
	}
}
void NobodyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("���� �׳� ����� ����̿�.");
		setCursorPosition(30, 12);
		printf("�� ���￡�� ��Ƴ������� ����ϴ� ����ϼ�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ֱ����� ��û���� ��Ż�� �ش�� �ִٳ�.");
		setCursorPosition(30, 12);
		printf("�ڳ׵� �����Ͻð�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�Ҹ��� ���� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[8].clear == 0)
		{
			if (quest[8].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[8].title);
				setCursorPosition(30, 12);
				printf(quest[8].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[8].take = 1;
						player.questmax++;
						acceptQuest(8);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[8].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[8].take == 1)
			{
				QuestComplete8();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[8].clear == 1) {
			setCursorPosition(30, 11);
			printf("���� ���� �� ����.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�ڳױ��� �� �̷��°�?");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰���, ������ �ô��.");
		backToMap();
		break;
	}
}

void NobodyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�Ϸ� ���� �Ϸ� �԰��� ����̿�.");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("������ ��Ȳ�� �������� ���� �ʴ� �Ͽ�.");
		setCursorPosition(30, 12);
		printf("�׷��� �ٴٿ��� �̼����̶� �屺�� Ȱ���ϰ� �ִ� �Ͽ�.");
		setCursorPosition(30, 13);
		printf("��ȭ��\n");
		setCursorPosition(30, 14);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("�ֺ��� �ҹ��� �����̱�?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[9].clear == 0)
		{
			if (quest[9].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[9].title);
				setCursorPosition(30, 12);
				printf(quest[9].description1);
				setCursorPosition(30, 13);
				printf("��ȭ��\n");
				setCursorPosition(30, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(30, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[9].take = 1;
						player.questmax++;
						acceptQuest(9);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[9].description2);
					setCursorPosition(30, 12);
					printf("��ȭ��\n");
					setCursorPosition(30, 13);
					printf("1. �̾��Ͽ�\n");
					updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
					backToDialogue();
					break;
				}
			}
			else if (quest[9].take == 1)
			{
				QuestComplete9();
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[9].clear == 1) {
			setCursorPosition(30, 11);
			printf("�� �𸣰ڼ�.");
			setCursorPosition(30, 12);
			printf("��ȭ��\n");
			setCursorPosition(30, 13);
			printf("1. �˰ڼ�\n");
		}
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("�ο���");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�峭ġ�� �����ּ����� �Ͽ�.");
		setCursorPosition(30, 12);
		printf("��ȭ��\n");
		setCursorPosition(30, 13);
		printf("1. �˰ڼ�\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("�߰��ÿ�, �� �����ϰ�");
		backToMap();
		break;
	}
}
void interactionQuestItem()
{
	if (currentQuestItem->type == VolunArmyQ && currentQuestItem->isActive == 1)
		dialogueVolunQuestItem();
	else if (currentQuestItem->type == GoverArmyQ && currentQuestItem->isActive == 1)
		dialogueGoverQuestItem();
	else if (currentQuestItem->type == JapArmyQ && currentQuestItem->isActive == 1)
		dialogueJapQuestItem();
	else if (currentQuestItem->type == NobodyQ && currentQuestItem->isActive == 1)
		dialogueNobodyQuestItem();
}

void dialogueVolunQuestItem()
{
	if (strcmp(currentQuestItem->name, "����") == 0)
		VolunItemLog_1();
	if (strcmp(currentQuestItem->name, "�ֱ� �ķ� â��") == 0)
		VolunItemLog_2();
}
void VolunItemLog_1()
{
	updateLog("������ �߰��Ͽ����ϴ�.");
	updateLog("[A]�� ���� ȹ���ϰų� [R]�� ���� ������ ���ư�����.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("��ư�� �߸� �Է��ϼ̽��ϴ�.");
		updateLog("[A]�� ���� ȹ���ϰų� [R]�� ���� ������ ���ư�����.");
		break;
	case 'A':
	case 'a':
		updateLog("������ ȹ���Ͽ����ϴ�.");
		QuestItemList[0].isActive = 0;
		player.questitem1 = 1;
		updateLog("������ ���ư��ϴ�.");
		updateQuestStatusItem(1); // quest[1] ����Ʈ ������
		player.pos = previousPos;
		Situation = 0;
		break;
	case 'R':
	case 'r':
		updateLog("������ ���ư��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}
void VolunItemLog_2()
{
	updateLog("�ֱ� �ķ� â�� �߰��Ͽ����ϴ�.");
	updateLog("[A]�� ���� ���¿�ų� [R]�� ���� ������ ���ư�����.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("��ư�� �߸� �Է��ϼ̽��ϴ�.");
		updateLog("[A]�� ���� ���¿�ų� [R]�� ���� ������ ���ư�����.");
		break;
	case 'A':
	case 'a':
		updateLog("�ֱ� �ķ� â�� ���¿����ϴ�.");
		QuestItemList[3].isActive = 0;
		player.questitem2 = 1;
		updateLog("������ ���ư��ϴ�.");
		updateQuestStatusItem(11); // quest[11] ����Ʈ ������
		player.pos = previousPos;
		Situation = 0;
		break;
	case 'R':
	case 'r':
		updateLog("������ ���ư��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}


void dialogueGoverQuestItem()
{
	updateLog("�������ڸ� �߰��Ͽ����ϴ�.");
	updateLog("[A]�� ���� ȹ���ϰų� [R]�� ���� ������ ���ư�����.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("��ư�� �߸� �Է��ϼ̽��ϴ�.");
		updateLog("[A]�� ���� ȹ���ϰų� [R]�� ���� ������ ���ư�����.");
		break;
	case 'A':
	case 'a':
		updateLog("������ ȹ���Ͽ����ϴ�.");
		QuestItemList[5].isActive = 0;
		player.questitem2 = 1;
		updateLog("������ ���ư��ϴ�.");
		updateQuestStatusItem(14); // quest[14] ����Ʈ ������
		player.pos = previousPos;
		Situation = 0;
		break;
	case 'R':
	case 'r':
		updateLog("������ ���ư��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}

void dialogueJapQuestItem()
{
	if (strcmp(currentQuestItem->name, "���� ����") == 0)
		JapItemLog_1();
	if (strcmp(currentQuestItem->name, "��Ż�� ��ǰ") == 0)
		JapItemLog_2();
}

void JapItemLog_1()
{
	updateLog("���� ������ �߰��Ͽ����ϴ�.");
	updateLog("[A]�� ���� ��ġ�ų� [R]�� ���� ������ ���ư�����.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("��ư�� �߸� �Է��ϼ̽��ϴ�.");
		updateLog("[A]�� ���� ��ġ�ų� [R]�� ���� ������ ���ư�����.");
		break;
	case 'A':
	case 'a':
		updateLog("���� ������ ���ƽ��ϴ�.");
		QuestItemList[1].isActive = 0;
		player.questitem2 = 1;
		updateLog("������ ���ư��ϴ�.");
		updateQuestStatusItem(3);  // quest[3] ����Ʈ ������
		player.pos = previousPos;
		Situation = 0;
		break;
	case 'R':
	case 'r':
		updateLog("������ ���ư��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}
void JapItemLog_2()
{
	updateLog("��Ż�� ��ǰ�� �߰��Ͽ����ϴ�.");
	updateLog("[A]�� ���� ì��ų� [R]�� ���� ������ ���ư�����.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("��ư�� �߸� �Է��ϼ̽��ϴ�.");
		updateLog("[A]�� ���� ì��ų� [R]�� ���� ������ ���ư�����.");
		break;
	case 'A':
	case 'a':
		updateLog("��Ż�� ��ǰ�� ì����ϴ�.");
		QuestItemList[4].isActive = 0;
		player.questitem2 = 1;
		updateLog("������ ���ư��ϴ�.");
		updateQuestStatusItem(17); // quest[17] ����Ʈ ������
		player.pos = previousPos;
		Situation = 0;
		break;
	case 'R':
	case 'r':
		updateLog("������ ���ư��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}
void dialogueNobodyQuestItem()
{
	if (strcmp(currentQuestItem->name, "����") == 0)
		NobodyItemLog_1();
	if (strcmp(currentQuestItem->name, "��") == 0)
		NobodyItemLog_2();
}
void NobodyItemLog_1()
{
	updateLog("������ �߰��Ͽ����ϴ�.");
	updateLog("[A]�� ���� ġ��ų� [R]�� ���� ������ ���ư�����.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("��ư�� �߸� �Է��ϼ̽��ϴ�.");
		updateLog("[A]�� ���� ġ��ų� [R]�� ���� ������ ���ư�����.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		if (player.hp > 1)
		{
			updateLog("������ ġ�����ϴ�. HP�� 1 �Ҹ�Ǿ����ϴ�.");
			QuestItemList[2].isActive = 0;
			player.questitem3 = 1;
			player.hp--;
			updateLog("������ ���ư��ϴ�.");
			updateQuestStatusItem(4); // quest[4] ����Ʈ ������
			player.pos = previousPos;
			Situation = 0;
			break;
		}
		else
		{
			updateLog("HP�� 2 �̻��̾�� ġ��� �ֽ��ϴ�.");
			player.pos = previousPos;
			Situation = 0;
			break;
		}
	case 'R':
	case 'r':
		updateLog("������ ���ư��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}
void NobodyItemLog_2()
{
	updateLog("���� �߰��Ͽ����ϴ�.");
	updateLog("[A]�� ���� ��Ȯ�ϰų� [R]�� ���� ������ ���ư�����.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("��ư�� �߸� �Է��ϼ̽��ϴ�.");
		updateLog("[A]�� ���� ��Ȯ�ϰų� [R]�� ���� ������ ���ư�����.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		if (player.hp > 2)
		{
			updateLog("���� ��Ȯ�Ͽ����ϴ�. HP�� 2 �Ҹ�Ǿ����ϴ�.");
			QuestItemList[6].isActive = 0;
			player.questitem1 = 1;
			player.hp -= 2;
			updateLog("������ ���ư��ϴ�.");
			updateQuestStatusItem(9); // quest[9] ����Ʈ ������
			player.pos = previousPos;
			Situation = 0;
			break;
		}
		else
		{
			updateLog("HP�� 3 �̻��̾�� ġ��� �ֽ��ϴ�.");
			player.pos = previousPos;
			Situation = 0;
			break;
		}
	case 'R':
	case 'r':
		updateLog("������ ���ư��ϴ�.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}

/* ���ѷα� �� �Լ�
void interactPrologueNpc()
{
	Sleep(100);
	clearScreen();
	setCursorPosition(40, 11);
	printf(prologuequest.title);
	setCursorPosition(40, 12);
	printf(prologuequest.description1);
	//if (encountPrologueNpc1())
	setCursorPosition(40, 11);
	printf(prologuequest.description2);
	//if (encountPrologueNpc2())
	setCursorPosition(40, 11);
	printf(prologuequest.description3);
}
 */