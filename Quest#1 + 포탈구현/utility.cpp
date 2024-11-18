#include "utility.h"

//������, �Ϲݸ�
char map[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char mapBattle[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char mapShop[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
int Situation = 0;

// Ŀ���� Ư�� ��ġ�� �̵���Ű�� �Լ�
void setCursorPosition(int x, int y)
{
	COORD pos = { x, y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos);
}

//Ŀ���� ����� �Լ�
void eraseCursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

//���ڿ� ���� ������ �Լ�
void setColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}