#ifndef ENCOUNT_H
#define ENCOUNT_H

#include "utility.h"
#include "enemy.h"
#include "potal.h"

extern Enemy* currentEnemy;

int encountEnemy();
void encountChoice();
int encountShop();
void encountShopChoice();
int encountPotal();
void encountPotalChoice();

#endif	//ENCOUNT_H