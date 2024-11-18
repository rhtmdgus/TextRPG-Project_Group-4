#include "log.h"
#include <stdio.h>
#include <time.h>

char logMessage[5][100] = { "", "", "" };
char battleLogMessage[5][100] = { "", "", "", "", "" };

//일반로그//

void displayLog()	//로그 출력 함수
{
	setCursorPosition(0, MAP_HEIGHT);
	printf("=============================== Log ===============================\n");
	for (int i = 0; i < 5; i++)
	{
		setCursorPosition(0, MAP_HEIGHT + 1 + i);
		printf("%-70s\n", logMessage[i]);
	}
}

void updateLog(const char* message)
{
	for (int i = 4; i > 0; i--)
	{
		Sleep(30);
		snprintf(logMessage[i], sizeof(logMessage[i]), "%s", logMessage[i - 1]);
	}

	snprintf(logMessage[0], sizeof(logMessage[0]), "%s", message);
}

//전투로그//

void displayBattleLog()	//전투 로그 출력 함수
{
	setCursorPosition(0, MAP_HEIGHT);
	printf("=============================== Log ===============================\n");
	for (int i = 0; i < 5; i++)
	{
		Sleep(30);
		setCursorPosition(0, MAP_HEIGHT + 1 + i);
		printf("%-70s\n", battleLogMessage[i]);
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