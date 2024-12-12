#include "questmanager.h"
#include "quest.h"
#include "player.h"
#include "displaymap.h"
#include "interaction.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#pragma warning(disable:4996)

#define MAX_QUESTS 3

QuestStatus questStatus[MAX_QUESTS];

// ����Ʈ ���� �� ����Ʈ ����� ���� �ʱ�ȭ
void acceptQuest(int questId) {

    for (int i = 0; i < MAX_QUESTS; i++) {
        if (questStatus[i].accepted != 1) {
            strcpy(questStatus[i].questName, quest[questId].description1); // ����Ʈ �̸� ����
            questStatus[i].questId = questId;

            questStatus[i].questcondition = quest[questId].questCondition;
            questStatus[i].questGoal = quest[questId].questGoal; // **����Ʈ ��ǥ ����**

            questStatus[i].killCount = 0; // ų ī��Ʈ �ʱ�ȭ
            questStatus[i].itemCount = 0; // ������ ī��Ʈ �ʱ�ȭ
            questStatus[i].isCompleted = 0; // �Ϸ� ���� �ʱ�ȭ
            questStatus[i].accepted = 1;
            return;
        }
    }
}



// ����Ʈ �����Ȳ ������Ʈ ��������
void updateQuestStatusItem(int questId) 
{
    for (int i = 0; i < MAX_QUESTS; i++) 
    {
        if (questStatus[i].questId == questId && questStatus[i].accepted) 
        {
            questStatus[i].itemCount = 1; // ������ ȹ��
            if (questStatus[i].itemCount >= questStatus[i].questGoal) 
            {
                questStatus[i].isCompleted = 1; // �Ϸ� ���� ����
            }
        }
    }
}




// ����Ʈ �����Ȳ ������Ʈ �����
void updateQuestStatusKill() 
{
    for (int i = 0; i < MAX_QUESTS; i++) 
    {
        if (questStatus[i].questcondition == 1) 
        {
            questStatus[i].killCount++; // ų ī��Ʈ ����
            if (questStatus[i].killCount >= questStatus[i].questGoal) 
            {
                questStatus[i].isCompleted = 1; // �Ϸ� ���� ����
            }
        }
    }
}



void completeQuest(int questId) {
    // �Ϸ�� ����Ʈ ����
    for (int i = 0; i < MAX_QUESTS; i++) {
        if (questStatus[i].questId == questId && questStatus[i].accepted == 1) {
            // ����Ʈ �ʱ�ȭ
            questStatus[i].accepted = 0;
            questStatus[i].questId = -1;
            questStatus[i].questName[0] = '\0'; // �̸� ����
            questStatus[i].questcondition = 0;
            questStatus[i].questGoal = 0;
            questStatus[i].killCount = 0;
            questStatus[i].itemCount = 0;
            questStatus[i].isCompleted = 0;

            // ���� ����Ʈ���� ������ ����
            for (int j = i; j < MAX_QUESTS - 1; j++) {
                questStatus[j] = questStatus[j + 1]; // �迭 ����
            }

            // ������ ����Ʈ �ʱ�ȭ (�ߺ� ����)
            questStatus[MAX_QUESTS - 1].accepted = 0;
            questStatus[MAX_QUESTS - 1].questId = -1;
            questStatus[MAX_QUESTS - 1].questName[0] = '\0';
            questStatus[MAX_QUESTS - 1].questcondition = 0;
            questStatus[MAX_QUESTS - 1].questGoal = 0;
            questStatus[MAX_QUESTS - 1].killCount = 0;
            questStatus[MAX_QUESTS - 1].itemCount = 0;
            questStatus[MAX_QUESTS - 1].isCompleted = 0;

            break; // �۾� �Ϸ� �� ���� ����
        }
    }
}




// ����Ʈ â ���
void printQuestWindow() {
    system("cls");
    initializeMap();
    displayQuestScreen();
    int cnt = 0;

    for (int i = 0, j = 0 ; i < MAX_QUESTS; i++) 
    {
        if (questStatus[i].accepted == 1) 
        {
            setCursorPosition(10, 10 + 3 * cnt);
            printf("%d �� ����Ʈ", j + 1);
            setCursorPosition(10, 11 + 3 * cnt);
            printf("����Ʈ ��ǥ: %s", questStatus[i].questName);
            setCursorPosition(10, 12 + 3 * cnt);
            if (questStatus[i].questcondition == 0) {
                printf("%d/1", questStatus[i].itemCount);
            }
            else if (questStatus[i].questcondition == 1) {
                printf("%d/5", questStatus[i].killCount);
            }
            j++;
            cnt++;
        }
        
    }

         


    updateBattleLog("Press any key to return to the main screen...");
    displayLog();
    _getch();  // ����� �Է� ���
    initializeMap(); // �� �ʱ�ȭ
    displayMap(); // �̵� �� ���
    displayPlayerStat(); //�÷��̾� ���� ǥ��
    drawPlayer(); // �÷��̾� ��ġ ���
    displayLog();
    


}