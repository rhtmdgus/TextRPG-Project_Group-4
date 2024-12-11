#ifndef SHOP_H
#define SHOP_H

#include "utility.h"

#define hpPotionPrice 2
#define manaPotionPrice 2
#define strengthPotionPrice 10
#define defensePotionPrice 10
#define accuracyPotionPrice 10

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
void eraseShop();

#endif // SHOP_H