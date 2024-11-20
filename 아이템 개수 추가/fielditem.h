#ifndef FIELDITEM_H
#define FIELDITEM_H

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
} Fielditem;

extern Fielditem fielditem1;

void drawFielditem();
void eraseFielditem();




#endif // FIELDITEM_H
