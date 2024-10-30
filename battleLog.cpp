#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAP_WIDTH 100
#define MAP_HEIGHT 30
#define PANEL_WIDTH 30

int Situation = 0;

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

Player player = { 10, 5, 5, 2, {1, 1} };
Enemy Jap1 = { "왜군 잡졸", 10, 8, 3, {7, 10} };


char map[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char mapBattle[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char logMessage[3][100] = { "", "", "" };

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
	printf("=========== Log ===========\n");
	for (int i = 0; i < 3; i++)
	{
		setCursorPosition(0, MAP_HEIGHT + i);
		printf("%s\n", logMessage[i]);
	}
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

void updateLog(const char* message) 
{
	for (int i = 2; i > 0; i--) 
	{
		strcpy(logMessage[i], logMessage[i - 1]);
		//snprintf(logMessage[i], sizeof(logMessage[i]), "%s", logMessage[i - 1]);
	}
	strcpy(logMessage[0], message);
	//snprintf(logMessage[0], sizeof(logMessage[0]), "%s", message);
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
	printf("=========== Battle Screen ==================================================================\n");
	printf("You encountered an enemy!\n");
	printf("Press [A] to Attack or [R] to Run.\n");
	printf("Player HP: %d	Player AP: %d	Player DP: %d\n", player.hp, player.attack, player.defense);
	printf("Enemy HP: %d	Enemy AP: %d	Enemy DP: %d\n", Jap1.hp, Jap1.attack, Jap1.defense);
	printf("============================================================================================\n");
	printf("  %s HP : %d\n", Jap1.name, Jap1.hp);
	printf("  ( 0_0)_/\n\n\n");
	printf("  Player HP : %d\n", player.hp);
	printf("  (')_(')\n");

	setCursorPosition(100, 0);
	printf("What would you like to do?\n");
	setCursorPosition(100, 1);
	printf("1. Attack enemy\n");
	setCursorPosition(100, 2);
	printf("2. Drink potion\n");
	setCursorPosition(100, 3);
	printf("3. Run away!\n");
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
	int damageToEnemy;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수

	while (Jap1.hp > 0 && player.hp > 0)
	{
		displayBattleScreen();
		char action = getch();

		switch (action)
		{
		case 'a':
		case 'A':
			// 공격 로직
			damageToEnemy = player.attack - Jap1.defense; // 이전에 선언한 변수를 사용
			if (damageToEnemy > 0) {
				Jap1.hp -= damageToEnemy;
				updateLog("You attacked the enemy!");
			}
			else {
				updateLog("Your attack was too weak!");
			}

			// 적 반격
			if (Jap1.hp > 0) {
				damageToPlayer = Jap1.attack - player.defense; // 이전에 선언한 변수를 사용
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					updateLog("The enemy attacked you!");
				}
			}
			break;

		case 'r':
		case 'R':
			updateLog("You ran away from the enemy!");
			Jap1.hp = 0; // 적 HP를 0으로 설정하여 전투 종료
			break;

		default:
			updateLog("Invalid action! Choose again.");
			break;
		}

		// 상태 체크
		if (Jap1.hp <= 0) {
			Jap1.hp = 0;
			updateLog("You defeated the enemy!");
			Situation = 0;
		}
		else if (player.hp <= 0) {
			player.hp = 0;
			updateLog("You have been defeated...");
			Situation = 0;
		}
	}
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
		updateLog("You choose the wrong key:");
		updateLog(action);
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



int main() 
{
	printf("전체화면으로 변경 후 엔터키를 누르세요");
	getchar();
	initializeMap();
	updateLog("Game started.");
	displayMap();
	displayLog();

	drawEnemy();
	map[Jap1.pos.y][Jap1.pos.x] = 'E';

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
		}
	}

	
	return 0;
}
