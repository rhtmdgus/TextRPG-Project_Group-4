#include "prologue.h"
#include <stdio.h>
#include <conio.h>

Potal_prologue potalP[4] = {

	{"P-0 -> P-1", 0, 1, {20, 28}, {20, 13}, true},
	{"P-1 -> P-2", 1, 2, {21, 28}, {20, 1}, false},
	{"P-2 -> P-3", 2, 3, {21, 28}, {20, 1}, false},
	{"P-3 -> M-3", 3, 4, {21, 28}, {1, 1}, false}
};

int mapLogShown[3] = { 0 };

NpcDataP npcListP[MAX_NPCP] = {
	{"아내", false, 1, {17, 15}, Deadbody},
	{"아들", false, 2, {10, 16}, Deadbody},
	{"창고", false, 1, {35, 19}, Storage}
};

NpcDataP* currentNPCP = nullptr;

int outNpcInteract_prologue = 0;
int checkingSpawnEnemy_P = 0;

//프롤로그 적
Enemy enemyTemplates_P[1] = {			
	{"허접한 왜군 잡졸", 7, 4, 3, {0, 0}, warrior}
};

Enemy currentEnemies_P[3];  // 배열 정의
int Enemy_PNum = 3;					//프롤로그 적 갯수

Enemy createEnemy_P(const Enemy* enemyTemplate_P, Position pos) {
	Enemy enemy_P;
	strcpy_s(enemy_P.name, sizeof(enemy_P.name), enemyTemplate_P->name);
	enemy_P.hp = enemyTemplate_P->hp;
	enemy_P.attack = enemyTemplate_P->attack;
	enemy_P.defense = enemyTemplate_P->defense;
	enemy_P.pos = pos;
	enemy_P.type = enemyTemplate_P->type;
	return enemy_P;
}

void spawnEnemies_P() {
	if(checkingSpawnEnemy_P == 1)
	{
		Position pos = { 4, 20 };
		currentEnemies_P[0] = createEnemy_P(&enemyTemplates_P[0], pos);
		drawEnemy_P(&currentEnemies_P[0]);
		pos = { 2, 20 };
		currentEnemies_P[1] = createEnemy_P(&enemyTemplates_P[0], pos);
		drawEnemy_P(&currentEnemies_P[1]);
		pos = { 6, 20 };
		currentEnemies_P[2] = createEnemy_P(&enemyTemplates_P[0], pos);
		drawEnemy_P(&currentEnemies_P[2]);
		checkingSpawnEnemy_P = 0;
	}
}

void drawEnemy_P(Enemy* enemy_P) {
	setCursorPosition(enemy_P->pos.x, enemy_P->pos.y);
	setColor(4);
	printf("E");
	setColor(7);
}

void eraseEnemy_P(Enemy* enemy_P) {
	setCursorPosition(enemy_P->pos.x, enemy_P->pos.y);
	printf(" ");
}

int encountEnemy_P()
{
	for (int i = 0; i < 3; i++) {
		if (currentEnemies_P[i].hp > 0 &&
			currentEnemies_P[i].pos.x == player.pos.x &&
			currentEnemies_P[i].pos.y == player.pos.y)
		{
			currentEnemy = &currentEnemies_P[i];
			Situation = 1;
			return 1;
		}
	}
	Situation = 0;
	currentEnemy = nullptr;
	return 0;
}

void encountChoice_P()
{
	char action = _getch();

	switch (action)
	{
	default:
		updateLog("You choose the wrong key");
		Sleep(200);
		displayLog();
		updateLog("Press [A] to Attack or [R] to Run");
		Sleep(200);
		displayLog();
		break;
	case 'A':
	case 'a':
		updateLog("You decided to attack the enemy!");
		Sleep(200);
		displayLog();
		displayBattleScreen();
		battle_P(currentEnemy);  // currentEnemy 전달
		break;
	case 'R':
	case 'r':
		updateLog("You ran away from the enemy!");
		Sleep(200);
		displayLog();
		updateLog("You fled from battle!");
		Sleep(200);
		displayLog();
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	Sleep(100);
	displayLog();
}


//프롤로그 NPC 관련 함수
void drawNpc_prologue(NpcDataP* npcListP)
{
	for (int i = 0; i < MAX_NPCP; i++)
	{
		if (player.currentmap == (npcListP + i)->currentmap)
		{
			setCursorPosition((npcListP + i)->pos.x, (npcListP + i)->pos.y);
			if ((npcListP + i)->type == Deadbody)
			{
				setColor(7);
				printf("N");
			}
			else if ((npcListP + i)->type == Storage)
			{
				setColor(8);
				printf("I");
				setColor(7);
			}
		}
	}
}
int encountNpc_prologue()
{
	for (int i = 0; i < MAX_NPCP; i++) {
		if (player.pos.y == npcListP[i].pos.y && player.pos.x == npcListP[i].pos.x && player.currentmap == npcListP[i].currentmap)
		{
			currentNPCP = &npcListP[i];
			Situation = 4;
			return 4;
		}
	}
	Situation = 0;
	currentNPCP = nullptr;
	return 0;
}
void encountNpcChoice_prologue()
{
	char action = _getch();

	switch (action)
	{
	default:
		updateLog("You choose the wrong key");
		updateLog("Press [A] to talk NPC or [R] to Leave");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		updateLog("You decided to talk to NPC");
		Situation = 5;
		initializeMap();
		displayShopMap();
		while (Situation == 5)
		{
			displayNPCScreen_prologue();
		}
		break;
	case 'R':
	case 'r':
		updateLog("You decided to leave NPC");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}
void displayNPCScreen_prologue()
{
	outNpcInteract_prologue = 1;
	
	int npctypeNum;

	if (currentNPCP->type == Deadbody)
		npctypeNum = 1;
	else
		npctypeNum = 2;
	
	switch (npctypeNum)
	{
	case 1:
		while (outNpcInteract_prologue == 1)
		{
			setCursorPosition(40, 11);
			printf("피를 흘리고 있는 사람이다");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 생사를 확인한다\n");
			setCursorPosition(40, 14);
			printf("2. 얼굴을 확인한다\n");
			setCursorPosition(40, 15);
			printf("3. 소지품을 뒤진다\n");
			setCursorPosition(40, 16);
			printf("4. NPC를 떠난다\n");
			displayPlayerStat();
			displayLog();
			interactionNPC_prologue();
			clearScreen();
			displayLog();
		}
		break;
	case 2:
		while (outNpcInteract_prologue == 1)
		{
			setCursorPosition(40, 11);
			printf("허름한 창고다.");
			setCursorPosition(40, 12);
			printf("낡았지만, 쓸만한 무기가 몇개 있다.");
			setCursorPosition(40, 13);
			printf("1. 무기를 선택한다.\n");
			setCursorPosition(40, 14);
			printf("2. NPC를 떠난다\n");
			displayPlayerStat();
			displayLog();
			interactionNPC_prologue();
			clearScreen();
			displayLog();
		}
	}
}
void interactionNPC_prologue()
{
	if (strcmp(currentNPCP->name, "아내") == 0)
		DeadbodyLog_1();
	if (strcmp(currentNPCP->name, "아들") == 0)
	{
		DeadbodyLog_2();
		checkingSpawnEnemy_P = 1;
	}
	if (strcmp(currentNPCP->name, "창고") == 0)
		StorageLog();
}
void DeadbodyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("생사를 확인한다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("숨이 멎은지 오래된 시신이다....");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 확인\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("얼굴을 확인한다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("내 아내다....");
		setCursorPosition(40, 12);
		printf("왜구에게 도망치다가 당한것 같다.");
		setCursorPosition(40, 13);
		printf("죽일 놈의 것들....");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 확인\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("소지품을 뒤진다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("약간의 은화와 포션을 얻었다.");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 확인\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("나중에 필히 와서 양지바른 곳에 묻어드리오");
		potalP[player.currentmap].SpawnPotal_P = true;
		backToMap_prologue();
		break;
	}
}
void DeadbodyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("생사를 확인한다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("죽은지 얼마 안된 아직 따듯한 시신이다....");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 확인\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("얼굴을 확인한다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("내 아들이다!!");
		setCursorPosition(40, 12);
		printf("어린아들까지 죽이다니!");
		setCursorPosition(40, 13);
		printf("용서하지 못한다!");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 확인\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("소지품을 뒤진다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("아무것도 없다");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 확인\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("간악한 왜구놈들... 아내까지 죽이고 이젠 내 아들까지 죽이다니...");
		backToMap_prologue();
		break;
	}
}
void StorageLog()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("무기를 선택한다.");
		system("cls");
		jobSelect_screen();
		initializeMap();
		displayShopMap();
		switch (player.job)
		{
		case 1:
			setCursorPosition(40, 11);
			printf("검사를 선택하셨습니다");
			setCursorPosition(40, 14);
			printf("대화문\n");
			setCursorPosition(40, 15);
			printf("1. 확인\n");
			Sleep(150);
			updateLog("A키를 눌러 이전 대화로 돌아가기");
			break;
		case 2:
			setCursorPosition(40, 11);
			printf("궁수를 선택하셨습니다");
			setCursorPosition(40, 14);
			printf("대화문\n");
			setCursorPosition(40, 15);
			printf("1. 확인\n");
			Sleep(150);
			updateLog("A키를 눌러 이전 대화로 돌아가기");
			break;
		case 3:
			setCursorPosition(40, 11);
			printf("창병을 선택하셨습니다");
			setCursorPosition(40, 14);
			printf("대화문\n");
			setCursorPosition(40, 15);
			printf("1. 확인\n");
			Sleep(150);
			updateLog("A키를 눌러 이전 대화로 돌아가기");
			break;
		case 4:
			setCursorPosition(40, 11);
			printf("방패병을 선택하셨습니다");
			setCursorPosition(40, 14);
			printf("대화문\n");
			setCursorPosition(40, 15);
			printf("1. 확인\n");
			Sleep(150);
			updateLog("A키를 눌러 이전 대화로 돌아가기");
			break;
		}
		displayPlayerStat();
		displayLog();
		backToDialogue();
		break;
	case '2':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("나를 위한 마지막 선물이라니...고맙소.");
		backToMap_prologue();
		break;
	}
}
void backToMap_prologue()
{
	while (1) {
		char action = _getch();
		switch (action) {
		case 'A':
		case 'a':
			outNpcInteract_prologue = 0;  // NPC 대화 모드 종료
			Situation = 0;
			player.pos = previousPos;  // 플레이어를 이전 위치로 복귀
			return;  // 함수 종료

		default:
			updateLog("잘못된 키를 입력했습니다. A키를 눌러 맵으로 돌아가기");
			displayLog();
			break;
		}
	}
}

//프롤로그 맵 선택
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

//프롤로그 포탈 출력 함수
void drawPotal_prologue()
{
	if (potalP[player.currentmap].SpawnPotal_P == true)
	{
		setCursorPosition(potalP[player.currentmap].pos.x, potalP[player.currentmap].pos.y);
		printf("T");
	}
	if (Enemy_PNum <= 0 && potalP[2].SpawnPotal_P == true)
	{
		setCursorPosition(potalP[3].pos.x, potalP[3].pos.y);
		printf("T");
	}
}

//포탈 encounting 함수
int encountPotal_prologue()
{
    if (player.pos.y == potalP[player.currentmap].pos.y && player.pos.x == potalP[player.currentmap].pos.x && potalP[player.currentmap].SpawnPotal_P == true)
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
//다음 튜토리얼 맵 이동 함수
void gotoNextMapPrologue() {
	player.currentmap = potal[player.currentmap].nextmap;
	player.pos = potalP[player.currentmap].playerNextPos;
}
//튜토리얼 맵 출력 함수
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
//튜토리얼 내역 출력 함수
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


void battle_P(Enemy* enemy)
{
	updateBattleLog("Battle start!!");
	int damageToEnemy;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수
	displayBattleScreen();
	displayPlayerStat();
	displayEnemyStat(enemy);
	displayBattleLog();

	while (enemy->hp > 0 && player.hp > 0 && Situation == 1)
	{
		char action = _getch();

		if (enemy == nullptr) {
			updateBattleLog("Error: No enemy to battle.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp포션 사용
			hppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp포션 사용
			mppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			// 공격 로직
			playerAttackAnimation();
			enemyAttackedAnimation(enemy);
			damageToEnemy = player.attack - enemy->defense; // 이전에 선언한 변수를 사용
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					updateBattleLog("Critical Attack!");
					damageToEnemy *= 2;
				}
				enemy->hp -= damageToEnemy;
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("You attacked the enemy!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("Your attack was too weak!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}

			// 적 반격
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // 이전에 선언한 변수를 사용
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("The enemy attacked you!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

			//적과 전투에서 도주
		case 'r':
		case 'R':
			updateBattleLog("You ran away from the enemy!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("You fled from battle!");
			break;

		default:
			updateBattleLog("Invalid action! Choose again.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		// 상태 체크
		if (enemy->hp <= 0) {
			updateBattleLog("You defeated the enemy!");
			player.exp += 12;
			player.money += 4;
			player.killcount++;
			Enemy_PNum--;

			if (Enemy_PNum <= 0) {
				potalP[2].SpawnPotal_P = true;
			}

			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
			updateBattleLog("You have been defeated...");
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
	}

	OriginalLevel = player.level;
	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("Press any key to return to the main screen...");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // 사용자 입력 대기

	if (player.level > OriginalLevel)
		updateLog("Level up!!");

	initializeMap(); // 맵 초기화
	displayMap_Prologue(); // 이동 맵 출력
	displayPlayerStat(); //플레이어 스탯 표시
	drawPlayer(); // 플레이어 위치 출력
}