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
void VolunArmyLog_1();
void VolunArmyLog_2();
void GoverArmyLog_1();
void GoverArmyLog_2();
void JapArmyLog_1();
void JapArmyLog_2();
void NobodyLog_1();
void NobodyLog_2();

void interactionQuestItem();
void dialogueVolunQuestItem();
void dialogueGoverQuestItem();
void dialogueJapQuestItem();
void dialogueNobodyQuestItem();
void interactPrologueNpc();

#endif // ! INTERACTION_H
