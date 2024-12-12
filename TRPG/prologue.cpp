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

int check_weapon = 0;

//���ѷα� ��
Enemy enemyTemplates_P[1] = {
	{"������ �ֱ� ����", 5, 3, 1, {0, 0}, warrior}		//hp, attack, deffence
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
		updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
		Sleep(200);
		displayLog();
		updateLog("[A]Ű�� ���� �������� [R]Ű�� ���� ����ĥ�� �����Ͻʽÿ�.");
		Sleep(200);
		displayLog();
		break;
	case 'A':
	case 'a':
		updateLog("������ ������ ���۵˴ϴ�!");
		Sleep(200);
		displayLog();
		battle_P(currentEnemy);  // currentEnemy ����
		break;
	case 'R':
	case 'r':
		updateLog("�����Լ� �����ƽ��ϴ�.!");
		Sleep(200);
		displayLog();
		updateLog("�������� ������ϴ�!");
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
		updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
		updateLog("[A]Ű�� ���� NPC�� ��ȭ���� [R]Ű�� ���� ������ �����Ͻʽÿ�.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		updateLog("NPC�� ��ȭ�� �����մϴ�.");
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
		updateLog("NPC�� �����ϴ�.");
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
			printf("�Ǹ� �긮�� �ִ� ����̴�");
			setCursorPosition(35, 12);
			printf("��ȭ��\n");
			setCursorPosition(35, 13);
			printf("1. ���縦 Ȯ���Ѵ�\n");
			setCursorPosition(35, 14);
			printf("2. ���� Ȯ���Ѵ�\n");
			setCursorPosition(35, 15);
			printf("3. ����ǰ�� ������\n");
			setCursorPosition(35, 16);
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
			setCursorPosition(35, 11);
			printf("�㸧�� â���.");
			setCursorPosition(35, 12);
			printf("��������, ������ ���Ⱑ � �ִ�.");
			setCursorPosition(35, 13);
			printf("1. ���⸦ �����Ѵ�.\n");
			setCursorPosition(35, 14);
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
		setCursorPosition(35, 11);
		printf("���� ������ ������ �ý��̴�....");
		setCursorPosition(35, 12);
		printf("��ȭ��\n");
		setCursorPosition(35, 13);
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
		setCursorPosition(35, 11);
		printf("Ȯ���� �� ���� ������ �Ѽ� �Ǿ���.");
		setCursorPosition(35, 12);
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
		setCursorPosition(35, 11);
		printf("�Ƴ��� ���ϼ����� �־��� ��డ �ִ�.");
		setCursorPosition(35, 12);
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
		setCursorPosition(35, 11);
		printf("�Ƶ��� ã�ƾ��Ѵ�.");
		setCursorPosition(35, 12);
		printf("�ϴ� ���⸦ ã�ƾ��Ѵ�.");
		backToMap_prologue();
		Sleep(200);
		updateLog("â��� �ѹ� ������");
		Sleep(200);
		displayLog();
		updateLog("â��� I�� ǥ�õǾ��ִ�.");
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
		updateLog("���縦 Ȯ���Ѵ�");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(35, 11);
		printf("������ �� �ȵ� ���� ������ �ý��̴�....");
		setCursorPosition(35, 12);
		printf("��ȭ��\n");
		setCursorPosition(35, 13);
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
		setCursorPosition(35, 11);
		printf("�ǹ����̵� �Ƶ��̴�..");
		setCursorPosition(35, 12);
		printf("�̷�...�̷� ���� ���̴ٴ�...");
		setCursorPosition(35, 13);
		printf("��ȭ��\n");
		setCursorPosition(35, 14);
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
		setCursorPosition(35, 11);
		printf("�ƹ��͵� ����");
		setCursorPosition(35, 14);
		printf("��ȭ��\n");
		setCursorPosition(35, 15);
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
		setCursorPosition(35, 11);
		printf("������ �ֱ����... ���� ������ ���̴ٴ�...�뼭���� ���Ѵ�.");
		setCursorPosition(35, 12);
		printf("�̷� ���� ���� ���� ã�� �����ؾ��Ѵ�.");
		backToMap_prologue();
		Sleep(200);
		updateLog("�ֱ� �ܴ���� ��Ÿ����!");
		Sleep(200);
		displayLog();
		updateLog("�ֱ��� ��ƾ� ���� ���������� �Ѿ�� ��Ż�� �����ɰ� ����.");
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
		updateLog("���⸦ �����Ѵ�.");
		system("cls");
		jobSelect_screen();
		initializeMap();
		displayShopMap();
			switch (player.job)
			{
			case 1:
				setCursorPosition(35, 11);
				printf("�˻縦 �����ϼ̽��ϴ�");
				setCursorPosition(35, 14);
				printf("��ȭ��\n");
				setCursorPosition(35, 15);
				printf("1. Ȯ��\n");
				Sleep(150);
				updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
				weaponchange(0);
				break;
			case 2:
				setCursorPosition(35, 11);
				printf("�ü��� �����ϼ̽��ϴ�");
				setCursorPosition(35, 14);
				printf("��ȭ��\n");
				setCursorPosition(35, 15);
				printf("1. Ȯ��\n");
				Sleep(150);
				updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
				weaponchange(0);
				break;
			case 3:
				setCursorPosition(35, 11);
				printf("â���� �����ϼ̽��ϴ�");
				setCursorPosition(35, 14);
				printf("��ȭ��\n");
				setCursorPosition(35, 15);
				printf("1. Ȯ��\n");
				Sleep(150);
				updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
				weaponchange(0);
				break;
			case 4:
				setCursorPosition(35, 11);
				printf("���к��� �����ϼ̽��ϴ�");
				setCursorPosition(35, 14);
				printf("��ȭ��\n");
				setCursorPosition(35, 15);
				printf("1. Ȯ��\n");
				Sleep(150);
				updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
				weaponchange(0);
				break;
			}
			check_weapon = 1;
		}
		else
		{
			setCursorPosition(35, 11);
			printf("���⸦ �̹� �����ϼ̽��ϴ�.");
			setCursorPosition(35, 12);
			printf("                                              ");
			setCursorPosition(35, 13);
			printf("                                              ");
			setCursorPosition(35, 14);
			printf("��ȭ��\n");
			setCursorPosition(35, 15);
			printf("1. Ȯ��\n");
			Sleep(150);
			updateLog("AŰ�� ���� ���� ��ȭ�� ���ư���");
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
		setCursorPosition(35, 11);
		printf("���� �Ƶ��� ã�ƾ���.");
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
		updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
		Sleep(200);
		displayLog();
		updateLog("[A]Ű�� ���� ���� ������ ���� [R]Ű�� ���� �ӹ����� �����Ͻʽÿ�.");
		Sleep(200);
		displayLog();
		break;
	case 'A':
	case 'a':
		Sleep(100);
		updateLog("���� ������ �����ϴ�!");
		Sleep(200);
		displayLog();

		gotoNextMapPrologue();

		initializeMap();
		Situation = 0;
		break;

	case 'R':
	case 'r':
		updateLog("���� ������ �ӹ����ϴ�");
		Sleep(200);
		displayLog();
		Situation = 0;
		player.pos = previousPos;
		break;
	}

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
			updateLog("�Ƶ��� ����ִ��� ã�ƺ���");
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
		setCursorPosition(35, 8);
		printf("�̵����");
		setCursorPosition(35, 9);
		printf("Ű������ ȭ��ǥ ��ư�� ���� �̵��մϴ�.");
		setCursorPosition(35, 10);
		printf("��Ű�� ����,  ��Ű�� ����������");
		setCursorPosition(35, 11);
		printf("��Ű�� ��������, ��Ű�� �Ʒ���");
		setCursorPosition(35, 12);
		printf("�̵��մϴ�.");
		break;
	case 1:
		setCursorPosition(40, 8);
		printf("��ȣ�ۿ�");
		setCursorPosition(40, 9);
		printf("�÷��̾ ��ȣ�ۿ��� ������Ʈ");
		setCursorPosition(40, 10);
		printf("(ex.N, S, E, Q)��ġ�� �̵���ŵ�ϴ�.");
		setCursorPosition(40, 11);
		printf("��ȣ�ۿ��� �� �� Ű������ A��ư");
		setCursorPosition(40, 12);
		printf("��ȣ�ۿ��� �� �� �� Ű������ R��ư��");
		setCursorPosition(40, 13);
		printf("�����ϴ�.");
		setCursorPosition(40, 15);
		printf("NPC����");
		setCursorPosition(40, 16);
		printf("�Ĺ��� ���� NPC���� ���� �ٸ��ϴ�.");
		setCursorPosition(40, 17);
		printf("�� �Ĺ����� ���赵�� ������ ���丮 ���࿡ ������ ��Ĩ�ϴ�.");
		setCursorPosition(40, 18);
		printf("NPC���� ��ȭ/��ȣ�ۿ��� ���е�� ����˴ϴ�.");
		break;
	case 2:
		setCursorPosition(45, 7);
		printf("���� ���");
		setCursorPosition(45, 8);
		printf("������ ���� ����Դϴ�.");
		setCursorPosition(45, 9);
		printf("�÷��̾��� ������ ���� ��ų�� ����� �ٸ��ϴ�.");
		setCursorPosition(45, 10);
		printf("��(E)ǥ�÷� �÷��̾ �̵� ���Ѽ�");
		setCursorPosition(45, 11);
		printf("�������� �������� �����մϴ�.");
		setCursorPosition(45, 12);
		printf("���� ������ NPC��ȣ�ۿ�� �����ϴ�.");
		setCursorPosition(45, 14);
		printf("������ ���� Ű���, ���е�� ����˴ϴ�.");
		setCursorPosition(45, 15);
		printf("A��ư�� �Ϲ� �����̰�,ġ��Ÿ�� �߻��� �� �ֽ��ϴ�." );
		setCursorPosition(45, 16);
		printf("����Ű 1, 2�� ���� ü�¿� ��� �����Դϴ�.");
		setCursorPosition(45, 17);
		printf("��ų�� 'Z','X','C'Ű�� ����� �� ������");
		setCursorPosition(45, 18);
		printf("Ư�� ������ ���� �Ҷ����� ��ų �ϳ��� ����ϴ�.");
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
		updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
		updateLog("[A]Ű�� ���� ����ĥ�� [R]Ű�� ���� �������� ã���� �����Ͻʽÿ�.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		updateLog("���� ��ƾ���...");
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
		updateLog("���⼭ ����ĥ ���� ����.. ������ ã���� ������!");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}


void battle_P(Enemy* enemy)
{
	updateBattleLog("��������!");
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
			updateBattleLog("����:������ ���� �����ϴ�.");
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
					updateBattleLog("ġ��Ÿ����!");
					damageToEnemy *= 2;
				}
				enemy->hp -= damageToEnemy;
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("���� �����Ͽ����ϴ�!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�!");
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
			updateBattleLog("�����Լ� �����ƽ��ϴ�!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("�������� ������ϴ�!");
			break;

		default:
			updateBattleLog("�Ұ����� �ൿ! �ٽ� �������ּ���.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		// ���� üũ
		if (enemy->hp <= 0) {
			enemyDyingAnimation(enemy);
			updateBattleLog("���� �����ƽ��ϴ�!");
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
			updateBattleLog("����� �й��Ͽ����ϴ�...");
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
	}

	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("�ƹ� Ű�� ���� ������ ���ư��ʽÿ�...");
	displayPlayerStat();
	displayBattleLog();
	_getch();  // ����� �Է� ���

	initializeMap(); // �� �ʱ�ȭ
	displayMap_Prologue(); // �̵� �� ���
	displayPlayerStat(); //�÷��̾� ���� ǥ��
	drawPlayer(); // �÷��̾� ��ġ ���
}