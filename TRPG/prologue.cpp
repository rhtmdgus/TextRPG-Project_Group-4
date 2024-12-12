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

int check_weapon = 0;

//프롤로그 적
Enemy enemyTemplates_P[1] = {
	{"허접한 왜군 잡졸", 5, 3, 1, {0, 0}, warrior}		//hp, attack, deffence
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
	if (checkingSpawnEnemy_P == 1)
	{
		Position pos = { 12, 15 };
		currentEnemies_P[0] = createEnemy_P(&enemyTemplates_P[0], pos);
		drawEnemy_P(&currentEnemies_P[0]);
		pos = { 4, 20 };
		currentEnemies_P[1] = createEnemy_P(&enemyTemplates_P[0], pos);
		drawEnemy_P(&currentEnemies_P[1]);
		pos = { 8, 18 };
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
		updateLog("잘못된 키를 입력하였습니다.");
		Sleep(200);
		displayLog();
		updateLog("[A]키를 눌러 전투할지 [R]키를 눌러 도망칠지 선택하십시오.");
		Sleep(200);
		displayLog();
		break;
	case 'A':
	case 'a':
		updateLog("적과의 전투가 시작됩니다!");
		Sleep(200);
		displayLog();
		battle_P(currentEnemy);  // currentEnemy 전달
		break;
	case 'R':
	case 'r':
		updateLog("적에게서 도망쳤습니다.!");
		Sleep(200);
		displayLog();
		updateLog("전투에서 벗어낫습니다!");
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
		updateLog("잘못된 키를 입력하였습니다.");
		updateLog("[A]키를 눌러 NPC와 대화할지 [R]키를 눌러 떠날지 선택하십시오.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		updateLog("NPC와 대화를 시작합니다.");
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
		updateLog("NPC를 떠납니다.");
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
			setCursorPosition(35, 11);
			printf("피를 흘리고 있는 사람이다");
			setCursorPosition(35, 12);
			printf("대화문\n");
			setCursorPosition(35, 13);
			printf("1. 생사를 확인한다\n");
			setCursorPosition(35, 14);
			printf("2. 얼굴을 확인한다\n");
			setCursorPosition(35, 15);
			printf("3. 소지품을 뒤진다\n");
			setCursorPosition(35, 16);
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
			setCursorPosition(35, 11);
			printf("허름한 창고다.");
			setCursorPosition(35, 12);
			printf("낡았지만, 쓸만한 무기가 몇개 있다.");
			setCursorPosition(35, 13);
			printf("1. 무기를 선택한다.\n");
			setCursorPosition(35, 14);
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
		setCursorPosition(35, 11);
		printf("숨이 멎은지 오래된 시신이다....");
		setCursorPosition(35, 12);
		printf("대화문\n");
		setCursorPosition(35, 13);
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
		setCursorPosition(35, 11);
		printf("확인할 수 없을 정도로 훼손 되었다.");
		setCursorPosition(35, 12);
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
		setCursorPosition(35, 11);
		printf("아내의 생일선물에 주었던 비녀가 있다.");
		setCursorPosition(35, 12);
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
		setCursorPosition(35, 11);
		printf("아들을 찾아야한다.");
		setCursorPosition(35, 12);
		printf("일단 무기를 찾아야한다.");
		backToMap_prologue();
		Sleep(200);
		updateLog("창고로 한번 가보자");
		Sleep(200);
		displayLog();
		updateLog("창고는 I로 표시되어있다.");
		Sleep(200);
		displayLog();
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
		setCursorPosition(35, 11);
		printf("죽은지 얼마 안된 아직 따듯한 시신이다....");
		setCursorPosition(35, 12);
		printf("대화문\n");
		setCursorPosition(35, 13);
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
		setCursorPosition(35, 11);
		printf("피범벅이된 아들이다..");
		setCursorPosition(35, 12);
		printf("이런...이런 짓을 벌이다니...");
		setCursorPosition(35, 13);
		printf("대화문\n");
		setCursorPosition(35, 14);
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
		setCursorPosition(35, 11);
		printf("아무것도 없다");
		setCursorPosition(35, 14);
		printf("대화문\n");
		setCursorPosition(35, 15);
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
		setCursorPosition(35, 11);
		printf("간악한 왜구놈들... 나의 가족을 죽이다니...용서하지 못한다.");
		setCursorPosition(35, 12);
		printf("이런 짓을 벌인 놈을 찾아 복수해야한다.");
		backToMap_prologue();
		Sleep(200);
		updateLog("왜군 잔당들이 나타났다!");
		Sleep(200);
		displayLog();
		updateLog("왜군을 잡아야 다음 스테이지로 넘어가는 포탈이 생성될것 같다.");
		break;
	}
}
void StorageLog()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		if (check_weapon == 0)
		{
		updateLog("무기를 선택한다.");
		system("cls");
		jobSelect_screen();
		initializeMap();
		displayShopMap();
			switch (player.job)
			{
			case 1:
				setCursorPosition(35, 11);
				printf("검사를 선택하셨습니다");
				setCursorPosition(35, 14);
				printf("대화문\n");
				setCursorPosition(35, 15);
				printf("1. 확인\n");
				Sleep(150);
				updateLog("A키를 눌러 이전 대화로 돌아가기");
				weaponchange(0);
				break;
			case 2:
				setCursorPosition(35, 11);
				printf("궁수를 선택하셨습니다");
				setCursorPosition(35, 14);
				printf("대화문\n");
				setCursorPosition(35, 15);
				printf("1. 확인\n");
				Sleep(150);
				updateLog("A키를 눌러 이전 대화로 돌아가기");
				weaponchange(0);
				break;
			case 3:
				setCursorPosition(35, 11);
				printf("창병을 선택하셨습니다");
				setCursorPosition(35, 14);
				printf("대화문\n");
				setCursorPosition(35, 15);
				printf("1. 확인\n");
				Sleep(150);
				updateLog("A키를 눌러 이전 대화로 돌아가기");
				weaponchange(0);
				break;
			case 4:
				setCursorPosition(35, 11);
				printf("방패병을 선택하셨습니다");
				setCursorPosition(35, 14);
				printf("대화문\n");
				setCursorPosition(35, 15);
				printf("1. 확인\n");
				Sleep(150);
				updateLog("A키를 눌러 이전 대화로 돌아가기");
				weaponchange(0);
				break;
			}
			check_weapon = 1;
		}
		else
		{
			setCursorPosition(35, 11);
			printf("무기를 이미 선택하셨습니다.");
			setCursorPosition(35, 12);
			printf("                                              ");
			setCursorPosition(35, 13);
			printf("                                              ");
			setCursorPosition(35, 14);
			printf("대화문\n");
			setCursorPosition(35, 15);
			printf("1. 확인\n");
			Sleep(150);
			updateLog("A키를 눌러 이전 대화로 돌아가기");
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
		setCursorPosition(35, 11);
		printf("빨리 아들을 찾아야해.");
		potalP[player.currentmap].SpawnPotal_P = true;
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
		updateLog("잘못된 키를 입력하였습니다.");
		Sleep(200);
		displayLog();
		updateLog("[A]키를 눌러 다음 마을로 갈지 [R]키를 눌러 머무를지 선택하십시오.");
		Sleep(200);
		displayLog();
		break;
	case 'A':
	case 'a':
		Sleep(100);
		updateLog("다음 마을로 떠납니다!");
		Sleep(200);
		displayLog();

		gotoNextMapPrologue();

		initializeMap();
		Situation = 0;
		break;

	case 'R':
	case 'r':
		updateLog("현재 마을에 머무릅니다");
		Sleep(200);
		displayLog();
		Situation = 0;
		player.pos = previousPos;
		break;
	}

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
			updateLog("아들이 살아있는지 찾아보자");
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
		setCursorPosition(35, 8);
		printf("이동방식");
		setCursorPosition(35, 9);
		printf("키보드의 화살표 버튼을 눌러 이동합니다.");
		setCursorPosition(35, 10);
		printf("↑키는 위로,  →키는 오른쪽으로");
		setCursorPosition(35, 11);
		printf("←키는 왼쪽으로, ↓키는 아래로");
		setCursorPosition(35, 12);
		printf("이동합니다.");
		break;
	case 1:
		setCursorPosition(40, 8);
		printf("상호작용");
		setCursorPosition(40, 9);
		printf("플레이어를 상호작용할 오브젝트");
		setCursorPosition(40, 10);
		printf("(ex.N, S, E, Q)위치로 이동시킵니다.");
		setCursorPosition(40, 11);
		printf("상호작용을 할 시 키보드의 A버튼");
		setCursorPosition(40, 12);
		printf("상호작용을 안 할 시 키보드의 R버튼을");
		setCursorPosition(40, 13);
		printf("누릅니다.");
		setCursorPosition(40, 15);
		printf("NPC설명");
		setCursorPosition(40, 16);
		printf("파벌에 따라 NPC들의 색이 다릅니다.");
		setCursorPosition(40, 17);
		printf("각 파벌과의 관계도는 엔딩과 스토리 진행에 영향을 미칩니다.");
		setCursorPosition(40, 18);
		printf("NPC와의 대화/상호작용은 넘패드로 진행됩니다.");
		break;
	case 2:
		setCursorPosition(45, 7);
		printf("전투 방식");
		setCursorPosition(45, 8);
		printf("전투는 턴제 방식입니다.");
		setCursorPosition(45, 9);
		printf("플레이어의 직업에 따라 스킬과 모션이 다릅니다.");
		setCursorPosition(45, 10);
		printf("적(E)표시로 플레이어를 이동 시켜서");
		setCursorPosition(45, 11);
		printf("공격할지 안할지를 결정합니다.");
		setCursorPosition(45, 12);
		printf("공격 결정은 NPC상호작용과 같습니다.");
		setCursorPosition(45, 14);
		printf("전투는 여러 키들과, 넘패드로 진행됩니다.");
		setCursorPosition(45, 15);
		printf("A버튼은 일반 공격이고,치명타가 발생할 수 있습니다." );
		setCursorPosition(45, 16);
		printf("숫자키 1, 2는 각각 체력와 기력 포션입니다.");
		setCursorPosition(45, 17);
		printf("스킬은 'Z','X','C'키로 사용할 수 있으며");
		setCursorPosition(45, 18);
		printf("특정 레벨에 도달 할때마다 스킬 하나를 얻습니다.");
	}
}

int encountRun()
{
	if (player.pos.x == 11 && player.pos.y == 12 && player.currentmap == 0) {
		Situation = 11;
		return 1;
	}
	Situation = 0;
	return 0;
}

void encountRunChoice()
{
	char action = _getch();

	switch (action)
	{
	default:
		updateLog("잘못된 키를 입력하였습니다.");
		updateLog("[A]키를 눌러 도망칠지 [R]키를 눌러 가족들을 찾을지 선택하십시오.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		updateLog("나라도 살아야지...");
		//Situation = 3;
		//initializeMap();
		//displayShopMap();
		player.ending = 7;
		player.hp = 0;
		Situation = 0;
		player.pos = previousPos;
		break;
	case 'R':
	case 'r':
		updateLog("여기서 도망칠 수는 없어.. 가족을 찾으러 가야해!");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}


void battle_P(Enemy* enemy)
{
	updateBattleLog("전투시작!");
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
			updateBattleLog("오류:전투에 적이 없습니다.");
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
					updateBattleLog("치명타공격!");
					damageToEnemy *= 2;
				}
				enemy->hp -= damageToEnemy;
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("적을 공격하였습니다!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("당신의 공격이 너무 약합니다!");
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
					updateBattleLog("적에게 공격당하였습니다!");
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
			updateBattleLog("적에게서 도망쳤습니다!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("전투에서 벗어났습니다!");
			break;

		default:
			updateBattleLog("불가능한 행동! 다시 선택해주세요.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		// 상태 체크
		if (enemy->hp <= 0) {
			enemyDyingAnimation(enemy);
			updateBattleLog("적을 물리쳤습니다!");
			//player.exp += 12;
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
			playerDyingAnimation();
			updateBattleLog("당신은 패배하엿습니다...");
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
	}

	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("아무 키를 눌러 맵으로 돌아가십시오...");
	displayPlayerStat();
	displayBattleLog();
	_getch();  // 사용자 입력 대기

	initializeMap(); // 맵 초기화
	displayMap_Prologue(); // 이동 맵 출력
	displayPlayerStat(); //플레이어 스탯 표시
	drawPlayer(); // 플레이어 위치 출력
}