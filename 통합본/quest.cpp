#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"
#include "utility.h"

Quest quest[MAX_QUEST];

void initializeQuest()
{
	quest[0] = { "��Ǭ �ݼ�",
	"��� �츮�� �� ġ�� ��Ǭ�� �ֽð�",
	0, 0, "�ʹ��ϱ���", "�ڳ׵� ���� ���°ǰ�?", "���� ����! �� ������ ���������� ���� �ʰڳ�" };
	quest[1] = { "�ķ��� Ȯ���϶�",
	"�ķ��� �����ѵ� �ķ��� ���ش��ټ� �ְڳ�?",
	0, 0, "�Ǻ��� �� �ο��� ���￡�� �̱�� ���ε�..","���� �ķ��� ���ؿ��� �ʾҳ�?", "����! �ݵ�� �¸��ϰ� ���ڳ�" };
	quest[2] = { "�ֱ��� �׿���",
	"���� ��Ȳ�� �Ҹ��ϴ�. �ֱ� 5���� ���̰�.",
	0, 0, "�츮���� ����� ���ΰ�?", "���� 5���� ������ ���߳�?", "�ڳ� ���п� ���￡�� ���������ٳ�." };
	quest[3] = { "������ ���� ������ ���Ķ�",
	"������ ¬©�ϰ� ���״� ��������� ���� ������ ���Ŀ�!",
	0, 0, "�ʵ� �ᱹ�� �������̷α�!", "���� �������� ��ġ�� ���߳�?", "����! ���� �ֱ����ٴ� ������! ųųų" };
	quest[4] = { "�뵿�� �����ְ�",
	"���� ������ ���� ���Ҵµ� �����ټ� �ְڳ�?",
	0, 0, "���� �����γ��� ���� ��ƾ���..", "���� ������ ġ���� ���߳�?", "����! �������� ���� ����� ��Ź�Ұ�" };
}


void drawQuestItem1() {
	setCursorPosition(questitem1.pos.x, questitem1.pos.y);
	setColor(3);
	printf("F");
}

void drawQuestItem2() {
	setCursorPosition(questitem2.pos.x, questitem2.pos.y);
	setColor(4);
	printf("O");
}

void drawQuestItem3() {
	setCursorPosition(questitem3.pos.x, questitem3.pos.y);
	setColor(7);
	printf("R");
}

void eraseQuestItem1() {
	setCursorPosition(questitem1.pos.x, questitem1.pos.y);
	printf(" ");
}

void eraseQuestItem2() {
	setCursorPosition(questitem2.pos.x, questitem2.pos.y);
	printf(" ");
}

void eraseQuestItem3() {
	setCursorPosition(questitem3.pos.x, questitem3.pos.y);
	printf(" ");
}

void QuestComplete1() {
	if (player.money > 1)
	{
		setCursorPosition(40, 11);
		printf("���迡�� 1���� �ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. �� �� �����غ���\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[0].clear = 1;
			player.money--;
			player.RRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[0].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[0].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ��� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("���� ������ �ٽ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete2() {
	if (player.questitem1 == 1)
	{
		setCursorPosition(40, 11);
		printf("�ķ��� �ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. �� �� �����غ���\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[1].clear = 1;
			player.questitem1 = 0;
			player.RRelationship += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[1].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[1].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("�ķ��� ��� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("�ķ��� �����ϰ� �ٽ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete3() {
	if (player.killcount >= 5)
	{
		setCursorPosition(40, 11);
		printf("�������� ����Ʈ�� �Ϸ��ߴٰ� ���ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. ���Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[2].clear = 1;
			player.killcount = 0;
			player.JRelationship += 30;
			player.WRelationship -= 50;
			player.money += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[2].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �¸��ϱ� �ٶ��\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[2].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ����� ���� �ֱ��� ������ ���ߴ�.");
		setCursorPosition(40, 12);
		printf("�ֱ��� ���� �� �����ϰ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete4() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("�ֱ����� ���������� �ѱ��?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. �� �� �����غ���\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[3].clear = 1;
			player.questitem2 = 0;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.RRelationship -= 30;
			player.money += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[3].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[3].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ ��� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("���� ������ ��ġ�� �ٽ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete5() {
	if (player.questitem3 == 1)
	{
		setCursorPosition(40, 11);
		printf("�ӹ��� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� �Ϸ�����.\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[4].clear = 1;
			player.questitem3 = 0;
			player.RRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[4].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[4].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ���� ġ���� �ʾ� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("���� ġ��� �ٽ� ������ ����.");
		backToDialogue();
	}
}
