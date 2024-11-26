#ifndef INTERACTION_H
#define INTERACTION_H

#include "utility.h"
#include "enemy.h"
#include "npc.h"
#include "log.h"
#include "player.h"
#include "displaymap.h"
#include "questmanager.h"
#include "potal.h"

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
void VolunArmyLog_1(); // hp포션 퀘스트, quest[5]
void VolunArmyLog_2(); // 식량퀘스트, quest[1]
void GoverArmyLog_1(); // 왜구 간부와의 싸움 퀘스트, quest[6]
void GoverArmyLog_2(); // 왜구 5명 죽이기 퀘스트, quest[2]
void JapArmyLog_1(); // 풀어달라는 퀘스트, quest[7]
void JapArmyLog_2(); // 작전서류 탈취 퀘스트, quest[3]
void NobodyLog_1(); // 한푼줍쇼 퀘스트, quest[0]
void NobodyLog_2(); // 바위치워주기 퀘스트, quest[4]

void interactionQuestItem();
void dialogueVolunQuestItem(); // 군량, 1
void dialogueGoverQuestItem();
void dialogueJapQuestItem(); // 작전서류, 3
void dialogueNobodyQuestItem(); // 바위, 4
void interactPrologueNpc();

#endif // ! INTERACTION_H
