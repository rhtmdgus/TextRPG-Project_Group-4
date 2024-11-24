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
	{"�Ƴ�", false, 1, {17, 15}, Deadbody},
	{"�Ƶ�", false, 2, {10, 16}, Deadbody},
	{"â��", false, 1, {35, 19}, Storage}
};

NpcDataP* currentNPCP = nullptr;

int outNpcInteract_prologue = 0;
int checkingSpawnEnemy_P = 0;

//���ѷα� ��
Enemy enemyTemplates_P[1] = {			
	{"������ �ֱ� ����", 7, 4, 3, {0, 0}, warrior}
};

Enemy currentEnemies_P[3];  // �迭 ����
int Enemy_PNum = 3;					//���ѷα� �� ����

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
		battle_P(currentEnemy);  // currentEnemy ����
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


//���ѷα� NPC ���� �Լ�
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
			printf("�Ǹ� �긮�� �ִ� ����̴�");
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ���縦 Ȯ���Ѵ�\n");
			setCursorPosition(40, 14);
			printf("2. ���� Ȯ���Ѵ�\n");
			setCursorPosition(40, 15);
			printf("3. ����ǰ�� ������\n");
			setCursorPosition(40, 16);
			printf("4. NPC�� ������\n");
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
			printf("�㸧�� â���.");
			setCursorPosition(40, 12);
			printf("��������, ������ ���Ⱑ � �ִ�.");
			setCursorPosition(40, 13);
			printf("1. ���⸦ �����Ѵ�.\n");
			setCursorPosition(40, 14);
			printf("2. NPC�� ������\n");
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
	if (strcmp(currentNPCP->name, "�Ƴ�") == 0)
		DeadbodyLog_1();
	if (strcmp(currentNPCP->name, "�Ƶ�") == 0)
	{
		DeadbodyLog_2();
		checkingSpawnEnemy_P = 1;
	}
	if (strcmp(currentNPCP->name, "â��") == 0)
		StorageLog();
}
void DeadbodyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("���縦 Ȯ���Ѵ�");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ ������ �ý��̴�....");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. Ȯ��\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("���� Ȯ���Ѵ�");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("�� �Ƴ���....");
		setCursorPosition(40, 12);
		printf("�ֱ����� ����ġ�ٰ� ���Ѱ� ����.");
		setCursorPosition(40, 13);
		printf("���� ���� �͵�....");
		setCursorPosition(40, 14);
		printf("��ȭ��\n");
		setCursorPosition(40, 15);
		printf("1. Ȯ��\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("����ǰ�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("�ణ�� ��ȭ�� ������ �����.");
		setCursorPosition(40, 14);
		printf("��ȭ��\n");
		setCursorPosition(40, 15);
		printf("1. Ȯ��\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���߿� ���� �ͼ� �����ٸ� ���� ����帮��");
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
		updateLog("���縦 Ȯ���Ѵ�");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("������ �� �ȵ� ���� ������ �ý��̴�....");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. Ȯ��\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;

	case '2':
		updateLog("���� Ȯ���Ѵ�");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("�� �Ƶ��̴�!!");
		setCursorPosition(40, 12);
		printf("��Ƶ���� ���̴ٴ�!");
		setCursorPosition(40, 13);
		printf("�뼭���� ���Ѵ�!");
		setCursorPosition(40, 14);
		printf("��ȭ��\n");
		setCursorPosition(40, 15);
		printf("1. Ȯ��\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '3':
		updateLog("����ǰ�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("�ƹ��͵� ����");
		setCursorPosition(40, 14);
		printf("��ȭ��\n");
		setCursorPosition(40, 15);
		printf("1. Ȯ��\n");
		Sleep(150);
		updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
		backToDialogue();
		break;
	case '4':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("������ �ֱ����... �Ƴ����� ���̰� ���� �� �Ƶ���� ���̴ٴ�...");
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
		updateLog("���⸦ �����Ѵ�.");
		system("cls");
		jobSelect_screen();
		initializeMap();
		displayShopMap();
		switch (player.job)
		{
		case 1:
			setCursorPosition(40, 11);
			printf("�˻縦 �����ϼ̽��ϴ�");
			setCursorPosition(40, 14);
			printf("��ȭ��\n");
			setCursorPosition(40, 15);
			printf("1. Ȯ��\n");
			Sleep(150);
			updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
			break;
		case 2:
			setCursorPosition(40, 11);
			printf("�ü��� �����ϼ̽��ϴ�");
			setCursorPosition(40, 14);
			printf("��ȭ��\n");
			setCursorPosition(40, 15);
			printf("1. Ȯ��\n");
			Sleep(150);
			updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
			break;
		case 3:
			setCursorPosition(40, 11);
			printf("â���� �����ϼ̽��ϴ�");
			setCursorPosition(40, 14);
			printf("��ȭ��\n");
			setCursorPosition(40, 15);
			printf("1. Ȯ��\n");
			Sleep(150);
			updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
			break;
		case 4:
			setCursorPosition(40, 11);
			printf("���к��� �����ϼ̽��ϴ�");
			setCursorPosition(40, 14);
			printf("��ȭ��\n");
			setCursorPosition(40, 15);
			printf("1. Ȯ��\n");
			Sleep(150);
			updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
			break;
		}
		displayPlayerStat();
		displayLog();
		backToDialogue();
		break;
	case '2':
		updateLog("NPC�� ������");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ���� ������ �����̶��...����.");
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
			outNpcInteract_prologue = 0;  // NPC ��ȭ ��� ����
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

//���ѷα� �� ����
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

//���ѷα� ��Ż ��� �Լ�
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

//��Ż encounting �Լ�
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
//���� Ʃ�丮�� �� �̵� �Լ�
void gotoNextMapPrologue() {
	player.currentmap = potal[player.currentmap].nextmap;
	player.pos = potalP[player.currentmap].playerNextPos;
}
//Ʃ�丮�� �� ��� �Լ�
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
//Ʃ�丮�� ���� ��� �Լ�
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


void battle_P(Enemy* enemy)
{
	updateBattleLog("Battle start!!");
	int damageToEnemy;   // ������ �� ����� ����
	int damageToPlayer;  // �ݰ��� �� ����� ����
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
		case '1'://           hp���� ���
			hppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp���� ���
			mppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			// ���� ����
			playerAttackAnimation();
			enemyAttackedAnimation(enemy);
			damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
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

			// �� �ݰ�
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // ������ ������ ������ ���
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

			//���� �������� ����
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

		// ���� üũ
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
	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("Press any key to return to the main screen...");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // ����� �Է� ���

	if (player.level > OriginalLevel)
		updateLog("Level up!!");

	initializeMap(); // �� �ʱ�ȭ
	displayMap_Prologue(); // �̵� �� ���
	displayPlayerStat(); //�÷��̾� ���� ǥ��
	drawPlayer(); // �÷��̾� ��ġ ���
}