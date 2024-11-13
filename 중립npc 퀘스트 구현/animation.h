#ifndef ANIMATION_H
#define ANIMATION_H

#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include "utility.h"

void printPlayer(); // displaymap.cpp에 추가

void playerAttackAnimation(); // battle.cpp 의 case A: 에 추가

void playerAttackedAnimation();

void printEnemy();

void enemyAttackedAnimation();

void enemyAttackAnimation();

#endif // ANIMATION_H
