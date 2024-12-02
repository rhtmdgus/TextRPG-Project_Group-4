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
void VolunArmyLog_1(); // hp���� ����Ʈ, quest[5]
void VolunArmyLog_2(); // �ķ�����Ʈ, quest[1]
void GoverArmyLog_1(); // �ֱ� ���ο��� �ο� ����Ʈ, quest[6]
void GoverArmyLog_2(); // �ֱ� 5�� ���̱� ����Ʈ, quest[2]
void JapArmyLog_1(); // Ǯ��޶�� ����Ʈ, quest[7]
void JapArmyLog_2(); // �������� Ż�� ����Ʈ, quest[3]
void NobodyLog_1(); // ��Ǭ�ݼ� ����Ʈ, quest[0]
void NobodyLog_2(); // ����ġ���ֱ� ����Ʈ, quest[4]

void interactionQuestItem();
void dialogueVolunQuestItem(); // ����, 1
void dialogueGoverQuestItem();
void dialogueJapQuestItem(); // ��������, 3
void dialogueNobodyQuestItem(); // ����, 4
void interactPrologueNpc();

#endif // ! INTERACTION_H
