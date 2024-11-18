#ifndef UTILITY_H
#define UTILITY_H
#include <windows.h>
#define MAP_WIDTH 100
#define MAP_HEIGHT 30
#define PANEL_WIDTH 30

extern char map[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
extern char mapBattle[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
extern char mapShop[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];

extern int Situation;	//인카운터 상황

typedef struct	//적, 플레이어 등등의 위치 구조체
{
	int x;
	int y;
} Position;

void setCursorPosition(int x, int y);
void eraseCursor();
void setColor(int color);

#endif // UTILITY_H