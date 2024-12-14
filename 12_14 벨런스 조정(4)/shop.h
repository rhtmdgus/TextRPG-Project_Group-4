#ifndef SHOP_H
#define SHOP_H

#include "utility.h"

#define hpPotionPrice 2
#define manaPotionPrice 2
#define strengthPotionPrice 15
#define defensePotionPrice 15
#define accuracyPotionPrice 15

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