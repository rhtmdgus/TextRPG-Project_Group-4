#ifndef ITEM_H
#define ITEM_H

#include "player.h"


typedef struct
{
    char name[50];
    int attackpoint;
    int defensepoint;
    int weaponTier;

} weapon;




typedef struct
{
    char name[50];
    int attackpoint;
    int defensepoint;
    int equipmentTier;

} equipment;



extern weapon weapons[5][10];

extern equipment equipments[5];


void weaponchange(int i);

void equipmentchange(int i);


#endif // ITEM_H