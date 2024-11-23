#include "prologue.h"
#include <stdio.h>
#include <conio.h>

Potal_prologue potal[4] = {

	{"P-0 -> P-1", 0, 1, {20, 28}, {20, 13}},
	{"P-1 -> P-2", 1, 2, {21, 28}, {20, 1}},
	{"P-2 -> P-3", 2, 3, {21, 28}, {20, 1}},
	{"P-2 -> M-3", 3, 4, {21, 28}, {1, 1}}
};

int mapLogShown[3] = { 0 };

void selectPrologueMap() {
	if (player.currentmap == 0) 
	{
		p_map0();
	}

	else if (player.currentmap == 1) 
	{
		p_map1();
	}
	else if (player.currentmap == 2)
	{
		p_map2();
	}
	else if (player.currentmap == 3)
	{
		return;
	}
}

void drawPotal_prologue()
{
	setCursorPosition(potal[player.currentmap].pos.x, potal[player.currentmap].pos.y);
	printf("T");
}

int encountPotal_prologue()
{
    if (player.pos.y == potal[player.currentmap].pos.y && player.pos.x == potal[player.currentmap].pos.x)
    {
        Situation = 9;
        return 1;

    }
    else
    {
        Situation = 0;
        return 0;
    }
}

void encountPotal_prologueChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("You choose the wrong key");
		Sleep(200);
		displayLog();
        updateLog("Press [A] to go next map or [R] to stay");
		Sleep(200);
		displayLog();
        break;
    case 'A':
    case 'a':
        Sleep(100);
        updateLog("You decided to go next map!");
		Sleep(200);
		displayLog();
  
		gotoNextMapPrologue();
  
		initializeMap();
        Situation = 0;
        break;

    case 'R':
    case 'r':
        updateLog("You decided to stay");
		Sleep(200);
		displayLog();
		Situation = 0;
        player.pos = previousPos;
        break;
    }
    displayLog();
}

void gotoNextMapPrologue() {
	player.currentmap = potal[player.currentmap].nextmap;
	player.pos = potal[player.currentmap].playerNextPos;
}


void displayMap_Prologue()
{
	system("cls");

	selectPrologueMap();

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

	showTutorial();


	if (!mapLogShown[player.currentmap]) {
		switch (player.currentmap) {
		case 0:
			updateLog("�Ӹ��� ������. ��ó ������ ��縦 �Ϸ� �Դ���");
			Sleep(200);
			displayLog();
			updateLog("�ֱ��鿡�� ������ �ް� ��� ������ �� �� �ϴ�.");
			Sleep(200);
			displayLog();
			break;
		case 1:
			updateLog("�Ƴ��� ã�ƾ��Ѵ�.");
			Sleep(200);
			displayLog();
			break;
		case 2:
			updateLog("������ ��Ÿ�� �ִ�...");
			Sleep(200);
			displayLog();
			updateLog("�� �ڽĵ��� ����ִ��� ã�ƺ���");
			Sleep(200);
			displayLog();
		}
		mapLogShown[player.currentmap] = 1; // �α� ��� �Ϸ� ǥ��
	}
}



void showTutorial()
{
	switch (player.currentmap)
	{
	case 0:
		setCursorPosition(40, 8);
		printf("�̵����");
		setCursorPosition(40, 9);
		printf("Ű������ ȭ��ǥ ��ư�� ���� �̵��մϴ�.");
		setCursorPosition(40, 10);
		printf("��Ű�� ����,  ��Ű�� ����������");
		setCursorPosition(40, 11);
		printf("��Ű�� ��������, ��Ű�� �Ʒ���");
		setCursorPosition(40, 12);
		printf("�̵��մϴ�.");
		break;
	case 1:
		setCursorPosition(40, 8);
		printf("��ȣ�ۿ�");
		setCursorPosition(40, 9);
		printf("�÷��̾ ��ȣ�ۿ��� ������Ʈ");
		setCursorPosition(40, 10);
		printf("(ex.N, S, E)��ġ�� �̵���ŵ�ϴ�.");
		setCursorPosition(40, 11);
		printf("��ȣ�ۿ��� �� �� Ű������ A��ư");
		setCursorPosition(40, 12);
		printf("��ȣ�ۿ��� �� �� �� Ű������ R��ư��");
		setCursorPosition(40, 13);
		printf("�����ϴ�.");
		setCursorPosition(40, 15);
		printf("NPC���� ��ȭ��");
		setCursorPosition(40, 16);
		printf("NPC���� ��ȭ/��ȣ�ۿ��� ���е�� ����˴ϴ�.");
		setCursorPosition(40, 17);
		printf("���� NPC�� ���������� ���е�� ����˴ϴ�.");
		break;
	case 2:
		setCursorPosition(40, 7);
		printf("���� ���");
		setCursorPosition(40, 8);
		printf("������ ���� ����Դϴ�.");
		setCursorPosition(40, 9);
		printf("�÷��̾��� ������ ���� ��ų�� ����� �ٸ��ϴ�.");
		setCursorPosition(40, 10);
		printf("��(E)ǥ�÷� �÷��̾ �̵� ���Ѽ�");
		setCursorPosition(40, 11);
		printf("�������� �������� �����մϴ�.");
		setCursorPosition(40, 12);
		printf("���� ������ NPC��ȣ�ۿ�� �����ϴ�.");
		setCursorPosition(40, 14);
		printf("������ A��ư�� R��ư, ���е�� ����˴ϴ�.");
		setCursorPosition(40, 15);
		printf("A��ư�� ����, ����Ű 1, 2�� ���� HP�� MP �����Դϴ�.");
		setCursorPosition(40, 16);
		printf("��ų�� '�̱���'��ư����,");
		setCursorPosition(40, 17);
		printf(" Ư�� ������ ���� �Ҷ����� ��ų �ϳ��� ����ϴ�.");
	}
}

