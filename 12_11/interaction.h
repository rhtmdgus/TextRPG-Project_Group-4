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
void VolunArmyLog_3(); // quest[10]
void VolunArmyLog_4(); // quest[11]
void VolunArmyLog_5(); // quest[12]
void GoverArmyLog_1(); // �ֱ� ���ο��� �ο� ����Ʈ, quest[6]
void GoverArmyLog_2(); // �ֱ� 5�� ���̱� ����Ʈ, quest[2]
void GoverArmyLog_3(); // quest[13]
void GoverArmyLog_4(); // quest[14]
void GoverArmyLog_5(); // quest[15]
void JapArmyLog_1(); // Ǯ��޶�� ����Ʈ, quest[7]
void JapArmyLog_2(); // �������� Ż�� ����Ʈ, quest[3]
void JapArmyLog_3(); // quest[16]
void JapArmyLog_4(); // quest[17]
void JapArmyLog_5(); // quest[18]
void NobodyLog_1(); // ��Ǭ�ݼ� ����Ʈ, quest[0]
void NobodyLog_2(); // ����ġ���ֱ� ����Ʈ, quest[4]
void NobodyLog_3(); // �� �ֱ� ����Ʈ, quest[8]
void NobodyLog_4(); // �� ��Ȯ ����Ʈ, quest[9]
void NobodyLog_5(); // ���� ����Ʈ

void interactionQuestItem();
void dialogueVolunQuestItem(); // ����, 1
void dialogueGoverQuestItem();
void dialogueJapQuestItem(); // ��������, 3
void dialogueNobodyQuestItem(); // ����, 4
void interactPrologueNpc();
void VolunItemLog_1();
void VolunItemLog_2();
void JapItemLog_1();
void JapItemLog_2();
void NobodyItemLog_1();
void NobodyItemLog_2();

#endif // ! INTERACTION_H
