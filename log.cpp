#include "log.h"
#include <stdio.h>

char logMessage[3][100] = { "", "", "" };
char battleLogMessage[5][100] = { "", "", "", "", "" };

//일반로그//

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

void updateLog(const char* message)
{
	for (int i = 2; i > 0; i--)
	{

		snprintf(logMessage[i], sizeof(logMessage[i]), "%s", logMessage[i - 1]);
	}

	snprintf(logMessage[0], sizeof(logMessage[0]), "%s", message);
}

//전투로그//

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