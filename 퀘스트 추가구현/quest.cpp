#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"
#include "utility.h"

Quest quest[MAX_QUEST];
PrologueQuest prologuequest; //���ѷα� ����Ʈ

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
	quest[5]  = {"�λ���� �Ǻ�",
	"�ű� ���� �ֳ�? ���ļ� �����ϼ��� ���µ� �� �����ְ�",
	0, 0, "(�Ǻ��� ����Ͽ���)", " ", "�Ǻ�: ���п� ��Ҵٳ�, �Ǻ����� ���״� ��������� ������ �ʰڳ�?" };
	quest[6] = {"���� �屺���� ����",
	"�ű� �ڳ�, �ֱ� ���ο� �ο�� �ִµ� �� �����ټ� �ְڳ�?",
	0, 0, "�ο��� ���ϳ� ����.. �˰ڳ�", "�� ���� �ִ°�?", "����! �ڳ� ���� �¸��Ҽ� �־���, �ڳ� ���� �� ������" };
	quest[7] = {"�ֱ� ���ο��� ����",
	"�̺� �ڳ�! �� Ǯ���ָ� �ڳ��� ������ �����ְڳ�",
	0, 0, "��ȸ�ϰ� �ɰž�", "�� �ٹ��Ÿ��� �ž�?", "Ź���� �����̳�" };
}

void initializePrologueQuest()
{
	prologuequest = { "������ ����",
	"�Ӹ��� ������. �ֱ������� ������ �ް� �����߾��� ����.",
	"�Ƴ���, �ֱ����� ���ѵ��ϴ�", "�ֱ��� �뼭�� �� ����. ������ �Ϸ�����" };
}

void drawQuestItem1() {
	setCursorPosition(questitem1.pos.x, questitem1.pos.y);
	setColor(3);
	printf("F");
	setColor(7);
}

void drawQuestItem2() {
	setCursorPosition(questitem2.pos.x, questitem2.pos.y);
	setColor(4);
	printf("O");
	setColor(7);
}

void drawQuestItem3() {
	setCursorPosition(questitem3.pos.x, questitem3.pos.y);
	setColor(7);
	printf("R");
	setColor(7);
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
			Sleep(200);
			displayLog();
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
			Sleep(200);
			displayLog();
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
			Sleep(200);
			displayLog();
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
			Sleep(200);
			displayLog();
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
			Sleep(200);
			displayLog();
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

void QuestComplete6() {
	if (//player.questitem1 == 1
		true)
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
			quest[6].clear = 1;
			player.questitem1 = 0;
			player.JRelationship += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[6].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �����̿�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			Sleep(200);
			displayLog();
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[6].description3);
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
		printf("���� �ֱ� ���θ� ���� ���Ͽ���.");
		setCursorPosition(40, 12);
		printf("�ֱ� ����� ��� �ٽ� ������ ����.");
		backToDialogue();
	}
}

void QuestComplete7() {
	if (//player.questitem2 == 1
		true)
	{
		setCursorPosition(40, 11);
		printf("�ֱ� ����� Ǯ���ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� �Ϸ�����.\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[7].clear = 1;
			//player.questitem2 = 0;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[7].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ���� ���ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			Sleep(200);
			displayLog();
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[7].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ��ٷ����ÿ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� �ֱ� ����� Ǯ���� ������ ì���� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("������ ì��� �ٽ� ������ ����.");
		backToDialogue();
	}
}
