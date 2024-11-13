#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "interaction.h"

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
	else
		dialogueNobody();
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
		setCursorPosition(40, 11);
		if (currentNPC->hasQuest == false)
			printf("�� �𸣰ڴµ�, �� ģ��鿡�� �ѹ� ����ڼ�.");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �˰ڼ�\n");
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
		setCursorPosition(40, 11);
		if (currentNPC->hasQuest == false)
			printf("�� �𸣰ڴµ�, �屺�Բ� �ѹ� ���庸�ڼ�.");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �˰ڼ�\n");
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
		setCursorPosition(40, 11);
		if (currentNPC->hasQuest == false)
			printf("������ ���� ��ų���� ���� ���� �� ����.");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �˰ڼ�\n");
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
		setCursorPosition(40, 11);
		if (currentNPC->hasQuest == false)
			printf("�� �𸣰ڴµ�, ���ƿ� ���� ����ÿ�.");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �˰ڼ�\n");
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