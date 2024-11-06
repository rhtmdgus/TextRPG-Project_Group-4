#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define MAP_WIDTH 100
#define MAP_HEIGHT 30
#define PANEL_WIDTH 30

int Situation = 0;

int useShop = 0;

typedef struct
{
	int x;
	int y;
} Position;

typedef struct
{
	int hp;
	int attack;
	int defense;
	int potion;
	Position pos;
} Player;

typedef struct
{
	char name[50];
	int hp;
	int attack;
	int defense;
	Position pos;
} Enemy;

typedef struct
{
	char name[50];
	int hpPotion;
	int manaPotion;
	int strengthPotion;
	int defensePotion;
	int accuracyPotion;
	Position pos;
} Shop;


Player player = { 10, 10, 5, 2, {1, 1} };
Enemy Jap1 = { "왜군 잡졸", 10, 8, 3, {7, 10} };
Shop Shop1 = { "상인", 99, 99, 99, 99, 99, {20, 15} };


char map[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char mapBattle[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char logMessage[3][100] = { "", "", "" };
char battleLogMessage[5][100] = { "", "", "", "", "" };


void start_screen() {	//시작화면
	for (int i = 0; i < (MAP_HEIGHT - 16) / 2; i++)
		printf("\n");

	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("||                                                   ||\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("||                임  진  투  쟁  기                 ||\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("||                                                   ||\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("         Text-based RPG Game Set in the Joseon Dynasty\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("           Press [Enter] to start your adventure!\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                        |         |  |\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                      ㅡㅡㅡ \\/  ㅡㅡㅡ\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                        O    /\u005C    O\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                       /|\\  /  \\  /|\\\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                      / | \\/    \\/ | \\\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                       / \\        / \\\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                      /   \\      /   \\\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");

	getchar();  // 사용자로부터 Enter 입력 대기

}

// 커서를 특정 위치로 이동시키는 함수
void setCursorPosition(int x, int y)
{
	COORD pos = { x, y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos);
}

//커서를 지우는 함수
void eraseCursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}


void initializeMap()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{

			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
			{
				map[i][j] = '#';
			}
			else
			{
				map[i][j] = ' ';
			}
		}
		for (int j = MAP_WIDTH; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			if (i == 0 || i == MAP_HEIGHT - 1)
			{
				map[i][j] = '#';
			}
		}
	}
}

void initializeMapBattle()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{

			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
			{
				mapBattle[i][j] = '#';
			}
			else
			{
				mapBattle[i][j] = ' ';
			}
		}
		for (int j = MAP_WIDTH; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			if (i == 0 || i == MAP_HEIGHT - 1)
			{
				mapBattle[i][j] = '#';
			}
		}
	}
}

void displayMap()
{
	system("cls");
	initializeMap();
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", map[i][j]);
		}

		if (i == 1) printf("  HP: %d", player.hp);
		if (i == 2) printf("  attack point: %d", player.attack);
		if (i == 3) printf("  defense point: %d", player.defense);
		if (i == 4) printf("  healing potion: %d", player.potion);

		printf("\n");
	}
}


void displayLog()	//로그 출력 함수
{
	setCursorPosition(0, MAP_HEIGHT);
	printf("=============================== Log ===============================\n");
	for (int i = 0; i < 3; i++)
	{
		setCursorPosition(0, MAP_HEIGHT + 1 + i);
		printf("%s\n", logMessage[i]);
	}
}

void displayBattleLog()	//전투 로그 출력 함수
{
	setCursorPosition(0, MAP_HEIGHT);
	printf("=============================== Log ===============================\n");
	for (int i = 0; i < 3; i++)
	{
		setCursorPosition(0, MAP_HEIGHT + 1 + i);
		printf("%s\n", battleLogMessage[i]);
	}
}

void updateBattleLog(const char* message)
{
	for (int i = 4; i > 0; i--)
	{

		snprintf(battleLogMessage[i], sizeof(battleLogMessage[i]), "%s", battleLogMessage[i - 1]);
	}

	snprintf(battleLogMessage[0], sizeof(battleLogMessage[0]), "%s", message);
}

void drawPlayer()
{
	setCursorPosition(player.pos.x, player.pos.y);
	printf("P");
}
void erasePlayer()
{
	setCursorPosition(player.pos.x, player.pos.y);
	printf(" ");
}

void drawEnemy()
{
	setCursorPosition(Jap1.pos.x, Jap1.pos.y);
	printf("E");
}

void eraseEnemy()
{
	setCursorPosition(Jap1.pos.x, Jap1.pos.y);
	printf(" ");
}

void drawShop()
{
	setCursorPosition(Shop1.pos.x, Shop1.pos.y);
	printf("S");
}

void eraseShop()
{
	setCursorPosition(Shop1.pos.x, Shop1.pos.y);
	printf(" ");
}

void updateLog(const char* message)
{
	for (int i = 2; i > 0; i--)
	{

		snprintf(logMessage[i], sizeof(logMessage[i]), "%s", logMessage[i - 1]);
	}

	snprintf(logMessage[0], sizeof(logMessage[0]), "%s", message);
}

void movePlayer()
{
	char input = getch();
	if (input == 'w' && player.pos.y > 1)
	{
		erasePlayer();
		player.pos.y--;
	}
	else if (input == 's' && player.pos.y < MAP_HEIGHT - 2)
	{
		erasePlayer();
		player.pos.y++;
	}
	else if (input == 'a' && player.pos.x > 1)
	{
		erasePlayer();
		player.pos.x--;
	}
	else if (input == 'd' && player.pos.x < MAP_WIDTH - 2)
	{
		erasePlayer();
		player.pos.x++;
	}

	/*
	else if (map[player.pos.y][player.pos.x] == 'I')
	{
		player.hp += 5;
		updateLog("You found a potion! HP +5");
	}
	*/
}

void displayBattleScreen()
{
	system("cls");
	//맵초기화
	initializeMapBattle();

	// 병사 1 (플레이어)
	int playerX = MAP_WIDTH / 2 - 5; // 중앙에 위치
	int playerY = MAP_HEIGHT / 2 - 2; // 중앙에 위치
	mapBattle[playerY][playerX] = 'P';  // 머리
	mapBattle[playerY + 1][playerX - 1] = '/';  // 왼팔
	mapBattle[playerY + 1][playerX] = '|'; // 몸
	mapBattle[playerY + 2][playerX] = '|'; // 몸
	mapBattle[playerY + 1][playerX + 1] = '\\'; // 오른팔
	mapBattle[playerY + 1][playerX + 2] = '/';//검
	mapBattle[playerY][playerX + 3] = '/';//검
	mapBattle[playerY + 2][playerX - 1] = '/';  // 왼다리
	mapBattle[playerY + 2][playerX] = ' '; // 빈 공간
	mapBattle[playerY + 2][playerX + 1] = '\\'; // 오른다리

	// 병사 2 (적군)
	int enemyX = MAP_WIDTH / 2 + 2; // 중앙에 위치
	int enemyY = MAP_HEIGHT / 2 - 2; // 중앙에 위치
	mapBattle[enemyY][enemyX] = 'E';   // 머리
	mapBattle[enemyY + 1][enemyX - 1] = '/';   // 왼팔
	mapBattle[enemyY + 1][enemyX - 2] = '\\';//검
	mapBattle[enemyY][enemyX - 3] = '\\';//검
	mapBattle[enemyY + 1][enemyX] = '|'; // 몸
	mapBattle[enemyY + 2][enemyX] = '|'; // 몸
	mapBattle[enemyY + 1][enemyX + 1] = '\\'; // 오른팔
	mapBattle[enemyY + 3][enemyX - 1] = '/';   // 왼다리
	mapBattle[enemyY + 3][enemyX] = ' '; // 빈 공간
	mapBattle[enemyY + 3][enemyX + 1] = '\\'; // 오른다리

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", mapBattle[i][j]);
		}

		if (i == 1) printf("  HP: %d", player.hp);
		if (i == 2) printf("  attack point: %d", player.attack);
		if (i == 3) printf("  defense point: %d", player.defense);
		if (i == 4) printf("  healing potion: %d", player.potion);

		printf("\n");
	}
	displayBattleLog();


	/*
	setCursorPosition(100, 0);
	printf("What would you like to do?\n");
	setCursorPosition(100, 1);
	printf("1. Attack enemy\n");
	setCursorPosition(100, 2);
	printf("2. Drink potion\n");
	setCursorPosition(100, 3);
	printf("3. Run away!\n");
	*/
}

void displayShopScreen()
{
	system("cls");
	//맵초기화
	initializeMapBattle();
	
	for (int i = 0; i < MAP_HEIGHT / 2 - 4; i++)
		printf("\n");
	for (int i = 0; i < MAP_WIDTH / 2 - 10; i++)
		printf(" ");
	printf("번호를 눌러 상품을 구매하세요.\n");
	for (int i = 0; i < MAP_WIDTH / 2 - 10; i++)
		printf(" ");
	printf("1. 체력 포션  남은 갯수: %d\n", Shop1.hpPotion);
	for (int i = 0; i < MAP_WIDTH / 2 - 10; i++)
		printf(" ");
	printf("2. 마나 포션  남은 갯수: %d\n", Shop1.manaPotion);
	for (int i = 0; i < MAP_WIDTH / 2 - 10; i++)
		printf(" ");
	printf("3. 힘 포션  남은 갯수: %d\n", Shop1.strengthPotion);
	for (int i = 0; i < MAP_WIDTH / 2 - 10; i++)
		printf(" ");
	printf("4. 명중 포션  남은 갯수: %d\n", Shop1.accuracyPotion);
	for (int i = 0; i < MAP_WIDTH / 2 - 10; i++)
		printf(" ");
	printf("5. 방어 포션  남은 갯수: %d\n", Shop1.defensePotion);
	for (int i = 0; i < MAP_WIDTH / 2 - 10; i++)
		printf(" ");
	printf("6. 상점을 떠난다.\n");
	int num = getch();
	switch (num)
	{
	case '1':
		updateLog("체력 포션 1개를 구매하였습니다.");
		player.potion += 1;
		Shop1.hpPotion -= 1;
		break;
	case '2':
		updateLog("마나 포션 1개를 구매하였습니다.");
		//player.potion += 1;
		Shop1.manaPotion -= 1;
		break;
	case '3':
		updateLog("힘 포션 1개를 구매하였습니다.");
		player.attack += 1;
		Shop1.strengthPotion -= 1;
		break;
	case '4':
		updateLog("명중 포션 1개를 구매하였습니다.");
		//player.accuracy += 1;
		Shop1.accuracyPotion -= 1;
		break;
	case '5':
		updateLog("방어 포션 1개를 구매하였습니다.");
		player.defense += 1;
		Shop1.defensePotion -= 1;
		break;
	case '6':
		updateLog("상점을 떠나는걸 선택하셨습니다.");
		useShop = 1;
		Situation = 0;
		break;
	}
	displayLog();

}


/*
void displayBattleMap()
{
	int damageToPlayer;
	int damageToEnemy;
	system("cls");
	printf("=========== Battle Screen ===========\n");
	printf("You encountered an enemy!\n");
	printf("Press [A] to Attack or [R] to Run.\n");

	char action = getch();
	if (action == 'a' || action == 'A')
	{
		updateLog("You decided to attack the enemy!");

		while (Jap1.hp > 0 || player.hp > 0)
		{
			printf("What would you like to do?\n");
			printf("1. Attack enemy\n");
			printf("2. Drink potion\n");
			printf("3. Run away!\n");

			char actionBattle = getch();

			switch (actionBattle)
			{
			case '1':
				printf("You tried to attack the enemy!\n");
				damageToEnemy = player.attack - Jap1.defense;
				Jap1.hp -= damageToEnemy;
				printf("Enemy got %d damage!\n", damageToEnemy);

				printf("Enemy tried to attack you!\n");
				damageToPlayer = Jap1.attack - player.defense;
				player.hp -= damageToPlayer;
				printf("You got %d damage!\n", damageToPlayer);
				break;

			case '2':
				printf("You drinked potion!\n");
				player.hp += 5;
				break;
			case '3':
				printf("You could't run away from enemy!\n");
				Sleep(10);
				printf("Enemy tried to attack you!\n");
				damageToPlayer = Jap1.attack - player.defense;
				player.hp -= damageToPlayer;
				printf("You got %d damage!\n", damageToPlayer);
				break;
			}


		}
		map[Jap1.pos.y][Jap1.pos.x] = ' ';
	}


	else if (action == 'r' || action == 'R')
	{
		updateLog("You ran away from the enemy!");
		printf("You fled from battle!\n");
	}

	printf("Press any key to return to the game.\n");
	getch();

	displayMap();
	drawPlayer();
}
*/

// 전투 함수
void battle()
{
	updateBattleLog("Battle start!!");
	int damageToEnemy;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수

	while (Jap1.hp > 0 && player.hp > 0)
	{
		displayBattleScreen();
		char action = getch();

		switch (action)
		{
		case 'a':
		case 1:
			// 공격 로직
			damageToEnemy = player.attack - Jap1.defense; // 이전에 선언한 변수를 사용
			if (damageToEnemy > 0) {
				Jap1.hp -= damageToEnemy;
				updateBattleLog("You attacked the enemy!");
			}
			else {
				updateBattleLog("Your attack was too weak!");
			}

			// 적 반격
			if (Jap1.hp > 0) {
				damageToPlayer = Jap1.attack - player.defense; // 이전에 선언한 변수를 사용
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					updateBattleLog("The enemy attacked you!");
				}
			}
			break;
		case 2:
			updateBattleLog("회복 포션 사용!");
			player.potion -= 1;
			player.hp += 5;
			break;
		case 3:
			updateBattleLog("도주하였습니다!");
			Jap1.hp = 0; // 적 HP를 0으로 설정하여 전투 종료
			break;

		case 'r':
		case 'R':
			updateBattleLog("You ran away from the enemy!");
			Jap1.hp = 0; // 적 HP를 0으로 설정하여 전투 종료
			break;

		default:
			updateBattleLog("Invalid action! Choose again.");
			break;
		}

		// 상태 체크
		if (Jap1.hp <= 0) {
			Jap1.hp = 0;
			updateBattleLog("You defeated the enemy!");
			Situation = 0;
		}
		else if (player.hp <= 0) {
			player.hp = 0;
			updateBattleLog("You have been defeated...");
			Situation = 0;
		}
	}

	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("Press any key to return to the main screen...");
	displayBattleScreen();
	getch();  // 사용자 입력 대기

	initializeMap(); // 맵 초기화
	displayMap(); // 이동 맵 출력
	drawPlayer(); // 플레이어 위치 출력
}

int encountEnemy()
{
	if (map[player.pos.y][player.pos.x] == 'E')
	{
		Situation = 1;
		return 1;
	}
	else
	{
		Situation = 0;
		return 0;
	}
}

void encountChoice()
{
	char action = getch();

	switch (action)
	{
	default:
		updateLog("You choose the wrong key");
		updateLog("Press [A] to Attack or [R] to Run");
		break;
	case 'A':
	case 'a':
		updateLog("You decided to attack the enemy!");
		Sleep(100);
		displayBattleScreen();
		battle();
		break;
	case 'R':
	case 'r':
		updateLog("You ran away from the enemy!");
		updateLog("You fled from battle!");
		Situation = 0;
		break;
	}
	displayLog();
}

int encountShop()
{
	if (map[player.pos.y][player.pos.x] == 'S')
	{
		Situation = 2;
		return 2;
	}
	else
	{
		Situation = 0;
		return 0;
	}
}

void encountShopChoice()
{
	char action = getch();

	switch (action)
	{
	default:
		updateLog("You choose the wrong key");
		updateLog("Press [A] to use Shop or [R] to Leave");
		break;
	case 'A':
	case 'a':
		updateLog("You decided to use Shop!");
		Sleep(100);
		displayShopScreen();
		break;
	case 'R':
	case 'r':
		updateLog("You decided to leave Shop");
		Situation = 0;
		break;
	}
	displayLog();
}


int main()
{
	start_screen();
	initializeMap();
	updateLog("Game started.");
	displayMap();
	displayLog();

	drawEnemy();
	drawShop();
	map[Jap1.pos.y][Jap1.pos.x] = 'E';
	map[Shop1.pos.y][Shop1.pos.x] = 'S';

	while (1)
	{
		eraseCursor();
		drawPlayer();
		movePlayer();
		displayLog();

		if (encountEnemy())
		{
			updateLog("You encountered an enemy!");
			updateLog("Press [A] to Attack or [R] to Run");
			displayLog();

			while (Situation == 1)
			{
				encountChoice();
			}
			if (Jap1.hp <= 0) {
				updateLog("The enemy was defeated!");
				initializeMap(); // 맵을 다시 초기화하여 적 제거
				displayMap();
				drawPlayer();
				displayLog();
			}
		}
		if (encountShop())
		{
			updateLog("You encountered a shop!");
			updateLog("Press [A] to use Shop or [R] to leave");
			displayLog();

			while (Situation == 2)
			{
				encountShopChoice();
			}
			if (useShop == 1) {
				initializeMap(); // 맵을 다시 초기화하여 적 제거
				displayMap();
				drawPlayer();
				displayLog();
			}
		}
	}


	return 0;
}