#ifndef BATTLE_H
#define BATTLE_H

#include "utility.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"

extern Enemy Jap1;         // �ܺο��� ����� Jap1 ���
extern Player player;      // �ܺο��� ����� player ���
extern int Situation;      // �ܺο��� ����� Situation ���

void battle();

#endif // BATTLE_H
