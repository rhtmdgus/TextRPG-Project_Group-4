#ifndef ANIMATION_H
#define ANIMATION_H

#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include "utility.h"

void printPlayer(); // displaymap.cpp�� �߰�

void playerAttackAnimation(); // battle.cpp �� case A: �� �߰�

void playerCritAnimation();

void playerAttackedAnimation();

void playerDyingAnimation();

void printEnemy(Enemy* enemy);

void printBoss(Enemy* boss);

void enemyAttackedAnimation(Enemy* enemy);

void enemyAttackAnimation(Enemy* enemy);

void enemyDyingAnimation(Enemy* enemy);

void BossAttack(Enemy* boss);

void BossDamaged(Enemy* boss);

void BossDying(Enemy* boss);

#endif // ANIMATION_H
