#ifndef SHOP_H
#define SHOP_H

#include "utility.h"

typedef struct
{
	char name[50];
	int hpPotion;
	int manaPotion;
	int strengthPotion;
	int defensePotion;
	int accuracyPotion;
	Position pos;
} Shop;

extern Shop Shop1;

void drawShop();

#endif // SHOP_H