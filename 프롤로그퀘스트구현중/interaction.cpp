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
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ����� �屺���� ������ �Ǻ��̿�");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("������ �츮�� ������ �԰浵�� �Ѿ�ٰ� �����.");
		setCursorPosition(40, 11);
		printf("�鼺�� ������ �ڱ� ȥ�� ����ġ�ٴ�,");
		setCursorPosition(40, 12);
		printf("������ ������ ���� �� �а��� ġ���� �� ���̿�");
		setCursorPosition(40, 13);
		printf("��ȭ��\n");
		setCursorPosition(40, 14);
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
				setCursorPosition(40, 11);
				printf(quest[1].title);
				setCursorPosition(40, 12);
				printf(quest[1].description1);
				setCursorPosition(40, 13);
				printf("��ȭ��\n");
				setCursorPosition(40, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(40, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[1].take = 1;
						player.questmax++;
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[1].description2);
					setCursorPosition(40, 12);
					printf("��ȭ��\n");
					setCursorPosition(40, 13);
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
			setCursorPosition(40, 11);
			printf("�� �𸣰ڴµ�, �� ģ��鿡�� �ѹ� ����ڼ�.");
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("���� �ʹ� ���Ѱ� �ƴϿ�??");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�߰��ÿ�, �ֳ�� �����ϰ�");
		backToMap();
		break;
	}
}
void dialogueGoverArmy()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("�� ���� �𸣰ڼ�? �ֺ� ������ �� �������ݼ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�ٴٿ� �̼��� �屺�Բ��� Ȧ�� �ֱ��� ����� �ִٰ� �����.");
		setCursorPosition(40, 11);
		printf("�㳪 �� ���� �û��ϴ� �ڵ��� ���� ������");
		setCursorPosition(40, 12);
		printf("�������� ���ڸ� ��Ƶ鿩�� �Ѵٴ� ��ģ �Ҹ��� ���� �ּ�.");
		setCursorPosition(40, 13);
		printf("��ȭ��\n");
		setCursorPosition(40, 14);
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
				setCursorPosition(40, 11);
				printf(quest[2].title);
				setCursorPosition(40, 12);
				printf(quest[2].description1);
				setCursorPosition(40, 13);
				printf("��ȭ��\n");
				setCursorPosition(40, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(40, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[2].take = 1;
						player.questmax++;
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[2].description2);
					setCursorPosition(40, 12);
					printf("��ȭ��\n");
					setCursorPosition(40, 13);
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
			setCursorPosition(40, 11);
			printf("�� �𸣰ڴµ�, �屺�Բ� �ѹ� ����ڼ�.");
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("���� ���� �����ϴ� ���ΰ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�߰��ÿ�, �ֳ�� �����ϰ�");
		backToMap();
		break;
	}
}
void dialogueJapArmy()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("����� ������?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("������ �����Ϸ� �� �ƺ� ������ ����δ�.");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�� ���� ��� �����ϴ����� �𸣰ڴٸ�");
		setCursorPosition(40, 11);
		printf("�츮�� ������ �����Ϸ� �� ���� �ƴ� �ع��Ű�� �� �ſ�");
		setCursorPosition(40, 12);
		printf("�״�� �츮�� ���̷� �ϴ� �� �������̿ʹ� �ٸ��� �ٶ��");
		setCursorPosition(40, 13);
		printf("��ȭ��\n");
		setCursorPosition(40, 14);
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
				setCursorPosition(40, 11);
				printf(quest[3].title);
				setCursorPosition(40, 12);
				printf(quest[3].description1);
				setCursorPosition(40, 13);
				printf("��ȭ��\n");
				setCursorPosition(40, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(40, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[3].take = 1;
						player.questmax++;
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[3].description2);
					setCursorPosition(40, 12);
					printf("��ȭ��\n");
					setCursorPosition(40, 13);
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
			setCursorPosition(40, 11);
			printf("������ ���� ��ų���� ���� ���� �� ����.");
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("��ī�߷�!");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�ٸ� ���ó�� �ൿ���� ���ÿ�");
		backToMap();
		break;
	}
}

void dialogueNobody()
{
	if (strcmp(currentNPC->name,"�� ����") == 0 && currentNPC->hasQuest == true)
		NobodyLog_1();
	if (strcmp(currentNPC->name, "�� �ƹ���") == 0 && currentNPC->hasQuest == true)
		NobodyLog_2();
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
		setCursorPosition(40, 11);
		printf("���� �׳� ����� ����̿�");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�ֱ����� �̵��� �����׸� ��Ż�Ѵٰ� �����.");
		setCursorPosition(40, 11);
		printf("������ ���� �ͼ� �츮 �� ���������� �ϴµ�,");
		setCursorPosition(40, 12);
		printf("������ �ȿ°� ����, �ҽ��� �������� �������� ���߳�����.");
		setCursorPosition(40, 13);
		printf("��ȭ��\n");
		setCursorPosition(40, 14);
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
		if (currentNPC->hasQuest == true && quest[0].clear == 0)
		{
			if (quest[0].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[0].title);
				setCursorPosition(40, 12);
				printf(quest[0].description1);
				setCursorPosition(40, 13);
				printf("��ȭ��\n");
				setCursorPosition(40, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(40, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[0].take = 1;
						player.questmax++;
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[0].description2);
					setCursorPosition(40, 12);
					printf("��ȭ��\n");
					setCursorPosition(40, 13);
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
			setCursorPosition(40, 11);
			printf("�� �𸣰ڴµ�, ���ƿ� ���� ����ÿ�.");
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�ֱ����� �밡���� �����̼�??");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
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
		setCursorPosition(40, 11);
		printf("���� �׳� ����� ����̿�");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�ֱ����� �̵��� �����׸� ��Ż�Ѵٰ� �����.");
		setCursorPosition(40, 11);
		printf("������ ���� �ͼ� �츮 �� ���������� �ϴµ�,");
		setCursorPosition(40, 12);
		printf("������ �ȿ°� ����, �ҽ��� �������� �������� ���߳�����.");
		setCursorPosition(40, 13);
		printf("��ȭ��\n");
		setCursorPosition(40, 14);
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
		if (currentNPC->hasQuest == true && quest[4].clear == 0)
		{
			if (quest[4].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[4].title);
				setCursorPosition(40, 12);
				printf(quest[4].description1);
				setCursorPosition(40, 13);
				printf("��ȭ��\n");
				setCursorPosition(40, 14);
				printf("1. �����Ѵ�.\n");
				setCursorPosition(40, 15);
				printf("2. �����Ѵ�.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �����ϼ̽��ϴ�!");
						updateLog("����Ʈ�� �����ϼ̽��ϴ�!");
						quest[4].take = 1;
						player.questmax++;
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						updateLog("����Ʈ�� �ѹ��� �ִ� 3������ ���� �����մϴ�!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[4].description2);
					setCursorPosition(40, 12);
					printf("��ȭ��\n");
					setCursorPosition(40, 13);
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
			setCursorPosition(40, 11);
			printf("�� �𸣰ڴµ�, ���ƿ� ���� ����ÿ�.");
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�ֱ����� �밡���� �����̼�??");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
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
		setCursorPosition(40, 11);
		printf("�߰��ÿ�, �ֳ�� �����ϰ�");
		backToMap();
		break;
	}
}


void interactQuestItem1()
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
		questitem1.used = 1;
		updateLog("������ ȹ���Ͽ����ϴ�.");
		player.questitem1 = 1;
		eraseQuestItem1();
		updateLog("������ ���ư��ϴ�.");
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

void interactQuestItem2()
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
		questitem2.used = 1;
		updateLog("���� ������ ���ƽ��ϴ�.");
		player.questitem2 = 1;
		eraseQuestItem2();
		updateLog("������ ���ư��ϴ�.");
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

void interactQuestItem3()
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
			questitem3.used = 1;
			updateLog("������ ġ�����ϴ�. HP�� 1 �Ҹ�Ǿ����ϴ�.");
			player.questitem3 = 1;
			player.hp--;
			eraseQuestItem3();
			updateLog("������ ���ư��ϴ�.");
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