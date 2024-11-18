#include "log.h"
#include <stdio.h>
#include <time.h>

char logMessage[5][100] = { "", "", "" };
char battleLogMessage[5][100] = { "", "", "", "", "" };

//�Ϲݷα�//

void displayLog()	//�α� ��� �Լ�
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

//�����α�//

void displayBattleLog()	//���� �α� ��� �Լ�
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