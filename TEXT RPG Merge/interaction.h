#ifndef INTERACTION_H
#define INTERACTION_H

#include "utility.h"
#include "enemy.h"
#include "npc.h"
#include "log.h"
#include "player.h"
#include "displaymap.h"

extern int outNpcInteract;

extern NpcData* currentNPC;

void interactionNPC();
void interactShop();
void backToDialogue();
void backToMap();

void dialogueVolunArmy();
void dialogueGoverArmy();
void dialogueJapArmy();
void dialogueNobody();

#endif // ! INTERACTION_H
