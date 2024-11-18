#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"

Quest quest[MAX_QUEST];

void initializeQuest()
{
	quest[0] = { "��Ǭ �ݼ�",
	"��� �츮�� �� ġ�� ��Ǭ�� �ֽð�",
	0, 0, "�ʹ��ϱ���", "�ڳ׵� ���� ���°ǰ�?", "���� ����! �� ������ ���������� ���� �ʰڳ�"};
	quest[1] = { "�ķ��� Ȯ���϶�", 
	"�Ǻ����� ������ ���ϰ� �ִµ� �ķ��� �����ϴٳ�\n �ķ��� ���ش��ټ� �ְڳ�?",
	0, 0, "�Ǻ��� �� �ο��� ���￡�� �̱�� ���ε�..","���� �ķ��� ���ؿ��� �ʾұ�.", "����! �ݵ�� �¸��ϰ� ���ڳ�"};
	quest[2] = { "�ֱ��� �׿���",
	"���� �ֱ��� ��������� �������� ���̶� ������ �Ҹ��� ��Ȳ�̴�.\n�ֱ� 5���� ���̰� ���ƿͶ�.",
	0, 0, "�츮���� ����� ���ΰ�?", "���� 5���� ������ ���ߴ�!", "�ڳ� ���п� ���￡�� ���������ٳ�."};
	quest[3] = { "������ �������� ���Ķ�",
	"������ ¬©�ϰ� ���״� ��������� �������� ���Ŀ�!",
	0, 0, "�ʵ� �ᱹ�� �������̷α�!", "���� �������� ��ġ�� ���߱�!", "����! ���� �ֱ����ٴ� ������! ųųų"};
	quest[4] = { "�뵿�� �����ְ�",
	"���� ������ ���� ���Ƽ� �����ٴϱⰡ ���� ��Ȳ�̳�\n �� �� �����ټ� �ְڳ�?",
	0, 0, "���� �����γ��� ���� ��ƾ���..", "���� ������ ġ���� ���߾�", "����! �������� ���� ����� ��Ź�Ұ�"};
}

void QuestComplete1() {
	if (player.money > 1)
	{
		setCursorPosition(40, 11);
		printf("���迡�� 1���� �ٱ�?");
		int num = _getch();
		if (num == 'a')
		{
			quest[0].clear = 1;
			player.money--;
			player.RRelationship += 10;
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
