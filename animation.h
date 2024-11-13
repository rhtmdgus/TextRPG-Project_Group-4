#ifndef ANIMATION_H
#define ANIMATION_H

#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include "utility.h"

void printPlayer(); // displaymap.cpp�� �߰�

void playerAttackAnimation(); // battle.cpp �� case A: �� �߰�

void playerAttackedAnimation();

void printEnemy();

void enemyAttackedAnimation();

void enemyAttackAnimation();

#endif // ANIMATION_H
