
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAP_WIDTH 100
#define MAP_HEIGHT 30
#define PANEL_WIDTH 30

typedef struct
{
	int x;
	int y;
} Position;

typedef struct
{
	int hp;
	int strength;
	int endurance;
	int intelligence;
	Position pos;
} Player;

Player player = { 10, 15, 8, 5, {1, 1} };
char map[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char logMessage[3][40] = { "", "", "" };

void start_screen() {
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
	printf("                        O    /\\    O\n");
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
	map[10][10] = 'E';
}

void battlemap()
{
	// 맵 초기화
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
			{
				map[i][j] = '#'; // 테두리
			}
			else
			{
				map[i][j] = ' '; // 빈 공간
			}
		}
		for (int j = MAP_WIDTH; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			if (i == 0 || i == MAP_HEIGHT - 1)
			{
				map[i][j] = '#'; // 패널 테두리
			}
		}
	}

	// 병사 1 (플레이어)
	int playerX = MAP_WIDTH / 2 - 5; // 중앙에 위치
	int playerY = MAP_HEIGHT / 2 - 2; // 중앙에 위치
	map[playerY][playerX] = 'O';  // 머리
	map[playerY + 1][playerX-1] = '/';  // 왼팔
	map[playerY + 1][playerX ] = '|'; // 몸
	map[playerY + 2][playerX] = '|'; // 몸
	map[playerY + 1][playerX + 1] = '\\'; // 오른팔
	map[playerY + 2][playerX-1] = '/';  // 왼다리
	map[playerY + 2][playerX] = ' '; // 빈 공간
	map[playerY + 2][playerX + 1] = '\\'; // 오른다리

	// 병사 2 (적군)
	int enemyX = MAP_WIDTH / 2 + 2; // 중앙에 위치
	int enemyY = MAP_HEIGHT / 2 - 2; // 중앙에 위치
	map[enemyY][enemyX] = 'X';   // 머리
	map[enemyY + 1][enemyX-1] = '/';   // 왼팔
	map[enemyY + 1][enemyX] = '|'; // 몸
	map[enemyY + 2][enemyX] = '|'; // 몸
	map[enemyY + 1][enemyX + 1] = '\\'; // 오른팔
	map[enemyY + 3][enemyX-1] = '/';   // 왼다리
	map[enemyY + 3][enemyX] = ' '; // 빈 공간
	map[enemyY + 3][enemyX + 1] = '\\'; // 오른다리
	map[enemyY +5][enemyX]

	// 맵 출력
	system("cls"); // 화면 지우기
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
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
		if (i == 2) printf("  Strength: %d", player.strength);
		if (i == 3) printf("  Endurance: %d", player.endurance);
		if (i == 4) printf("  Intelligence: %d", player.intelligence);

		printf("\n");
	}

	printf("=========== Log ===========\n");
	for (int i = 0; i < 3; i++)
	{
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

void updateLog(const char* message)
{
	for (int i = 2; i > 0; i--)
	{
		snprintf(logMessage[i], sizeof(logMessage[i]), "%s", logMessage[i - 1]);
	}
	snprintf(logMessage[0], sizeof(logMessage[0]), "%s", message);
}

void battleScreen() {
	system("cls");
	printf("=========== Battle Screen ===========\n");
	printf("You encountered an enemy!\n");
	printf("Press [A] to Attack or [R] to Run.\n");

	char action = getch();
	if (action == 'a' || action == 'A') {
		battlemap();
		updateLog("You attacked the enemy!");

	}
	else if (action == 'r' || action == 'R') {
		updateLog("You ran away from the enemy!");
		printf("You fled from battle!\n");
	}

	printf("Press any key to return to the game.\n");
	getch();

	initializeMap();
	displayMap();
	drawPlayer();
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

	if (map[player.pos.y][player.pos.x] == 'E') {
		updateLog("You encountered an enemy!");
		battleScreen();
	}

	/*if (map[player.pos.y][player.pos.x] == 'E')
	{
		updateLog("You encountered an enemy!");
	}
	else if (map[player.pos.y][player.pos.x] == 'I')
	{
		player.hp += 5;
		updateLog("You found a potion! HP +5");
	}
	*/
	//map[player.pos.y][player.pos.x] = 'P';
}

int main()
{
	start_screen();
	initializeMap();
	updateLog("Game started.");
	displayMap();

	map[player.pos.y][player.pos.x] = 'P';

	while (1)
	{
		eraseCursor();
		drawPlayer();
		movePlayer();
	}


	return 0;
}