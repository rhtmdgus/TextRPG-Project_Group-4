#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "quest.h"


// ����Ʈ �����Ȳ�� �����ϴ� ����ü
typedef struct QuestStatus {
    int accepted = 0;    // ����Ʈ�� ����ִ��� �ƴ���
    int questId = -1;         // ���� ����Ʈ����
    int questcondition;  // ����Ʈ ���� type -> ==0�Ͻ� ��������, ==1�Ͻ� �����
    int killCount = 0;   // ���� ų ī��Ʈ
    int itemCount = 0;   // ������ ȹ�� ī��Ʈ
    int isCompleted = 0;     // ����Ʈ �Ϸ� ����
    char questName[30] = " ";
    int questGoal = 1;
} QuestStatus;

// ����Ʈ ���� �Լ�
void acceptQuest(int questId);

// ����Ʈ �����Ȳ�� ������Ʈ�ϴ� �Լ�, ��������
void updateQuestStatusItem(int questId);

// ����Ʈ �����Ȳ�� ������Ʈ�ϴ� �Լ�, ��������
void updateQuestStatusKill(int questId);

// ����Ʈ�� �Ϸ��ϸ� ����Ʈâ�� ������Ʈ�ϴ� �Լ�
void complitQuest(int questId);

// ����Ʈ â�� ����ϴ� �Լ�
void printQuestWindow();

// ����Ʈ �����Ȳ �ʱ�ȭ �Լ�
void initializeQuestStatus();

#endif // QUESTMANAGER_H
