#ifndef ANIMATION_H
#define ANIMATION_H

#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include "utility.h"

void printPlayer(); // displaymap.cpp�� �߰�

void playerAttackAnimation(); // battle.cpp �� case A: �� �߰�

void playerAttackedAnimation();

void printEnemy(Enemy* enemy);

void printBoss(Enemy* boss);

void enemyAttackedAnimation(Enemy* enemy);

void enemyAttackAnimation(Enemy* enemy);

#endif // ANIMATION_H
