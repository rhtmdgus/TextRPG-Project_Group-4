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
			updateLog("머리가 아프다. 근처 마을에 장사를 하러 왔더니");
			Sleep(200);
			displayLog();
			updateLog("왜구들에게 습격을 받고 잠시 기절을 한 듯 하다.");
			Sleep(200);
			displayLog();
			break;
		case 1:
			updateLog("아내를 찾아야한다.");
			Sleep(200);
			displayLog();
			break;
		case 2:
			updateLog("마을이 불타고 있다...");
			Sleep(200);
			displayLog();
			updateLog("내 자식들이 살아있는지 찾아보자");
			Sleep(200);
			displayLog();
		}
		mapLogShown[player.currentmap] = 1; // 로그 출력 완료 표시
	}
}



void showTutorial()
{
	switch (player.currentmap)
	{
	case 0:
		setCursorPosition(40, 8);
		printf("이동방식");
		setCursorPosition(40, 9);
		printf("키보드의 화살표 버튼을 눌러 이동합니다.");
		setCursorPosition(40, 10);
		printf("↑키는 위로,  →키는 오른쪽으로");
		setCursorPosition(40, 11);
		printf("←키는 왼쪽으로, ↓키는 아래로");
		setCursorPosition(40, 12);
		printf("이동합니다.");
		break;
	case 1:
		setCursorPosition(40, 8);
		printf("상호작용");
		setCursorPosition(40, 9);
		printf("플레이어를 상호작용할 오브젝트");
		setCursorPosition(40, 10);
		printf("(ex.N, S, E)위치로 이동시킵니다.");
		setCursorPosition(40, 11);
		printf("상호작용을 할 시 키보드의 A버튼");
		setCursorPosition(40, 12);
		printf("상호작용을 안 할 시 키보드의 R버튼을");
		setCursorPosition(40, 13);
		printf("누릅니다.");
		setCursorPosition(40, 15);
		printf("NPC와의 대화문");
		setCursorPosition(40, 16);
		printf("NPC와의 대화/상호작용은 넘패드로 진행됩니다.");
		setCursorPosition(40, 17);
		printf("상점 NPC도 마찬가지로 넘패드로 진행됩니다.");
		break;
	case 2:
		setCursorPosition(40, 7);
		printf("전투 방식");
		setCursorPosition(40, 8);
		printf("전투는 턴제 방식입니다.");
		setCursorPosition(40, 9);
		printf("플레이어의 직업에 따라 스킬과 모션이 다릅니다.");
		setCursorPosition(40, 10);
		printf("적(E)표시로 플레이어를 이동 시켜서");
		setCursorPosition(40, 11);
		printf("공격할지 안할지를 결정합니다.");
		setCursorPosition(40, 12);
		printf("공격 결정은 NPC상호작용과 같습니다.");
		setCursorPosition(40, 14);
		printf("전투는 A버튼과 R버튼, 넘패드로 진행됩니다.");
		setCursorPosition(40, 15);
		printf("A버튼은 공격, 숫자키 1, 2는 각각 HP와 MP 포션입니다.");
		setCursorPosition(40, 16);
		printf("스킬은 '미구현'버튼으로,");
		setCursorPosition(40, 17);
		printf(" 특정 레벨에 도달 할때마다 스킬 하나를 얻습니다.");
	}
}

