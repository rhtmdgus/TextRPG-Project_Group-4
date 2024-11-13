#ifndef LOG_H
#define LOG_H

#include "utility.h"

extern char logMessage[5][100];
extern char battleLogMessage[5][100];

void displayLog();
void displayBattleLog();
void updateBattleLog(const char* message);
void updateLog(const char* message);

#endif // LOG_H
