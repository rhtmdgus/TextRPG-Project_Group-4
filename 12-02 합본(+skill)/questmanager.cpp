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

// 퀘스트 수락 시 퀘스트 내용과 상태 초기화
void acceptQuest(int questId) {

    for (int i = 0; i < MAX_QUESTS; i++) {
        if (questStatus[i].accepted != 1) {
            strcpy(questStatus[i].questName, quest[questId].description1); // 퀘스트 이름 저장
            questStatus[i].questId = questId;

            questStatus[i].questcondition = quest[questId].questCondition;
            questStatus[i].questGoal = quest[questId].questGoal; // **퀘스트 목표 설정**

            questStatus[i].killCount = 0; // 킬 카운트 초기화
            questStatus[i].itemCount = 0; // 아이템 카운트 초기화
            questStatus[i].isCompleted = 0; // 완료 상태 초기화
            questStatus[i].accepted = 1;
            return;
        }
    }
}



// 퀘스트 진행상황 업데이트 아이템형
void updateQuestStatusItem(int questId) 
{
    for (int i = 0; i < MAX_QUESTS; i++) 
    {
        if (questStatus[i].questId == questId && questStatus[i].accepted) 
        {
            questStatus[i].itemCount = 1; // 아이템 획득
            if (questStatus[i].itemCount >= questStatus[i].questGoal) 
            {
                questStatus[i].isCompleted = 1; // 완료 상태 설정
            }
        }
    }
}




// 퀘스트 진행상황 업데이트 사냥형
void updateQuestStatusKill() 
{
    for (int i = 0; i < MAX_QUESTS; i++) 
    {
        if (questStatus[i].questcondition == 1) 
        {
            questStatus[i].killCount++; // 킬 카운트 증가
            if (questStatus[i].killCount >= questStatus[i].questGoal) 
            {
                questStatus[i].isCompleted = 1; // 완료 상태 설정
            }
        }
    }
}



void completeQuest(int questId) {
    // 완료된 퀘스트 제거
    for (int i = 0; i < MAX_QUESTS; i++) {
        if (questStatus[i].questId == questId && questStatus[i].accepted == 1) {
            // 퀘스트 초기화
            questStatus[i].accepted = 0;
            questStatus[i].questId = -1;
            questStatus[i].questName[0] = '\0'; // 이름 비우기
            questStatus[i].questcondition = 0;
            questStatus[i].questGoal = 0;
            questStatus[i].killCount = 0;
            questStatus[i].itemCount = 0;
            questStatus[i].isCompleted = 0;

            // 이후 퀘스트들을 앞으로 당기기
            for (int j = i; j < MAX_QUESTS - 1; j++) {
                questStatus[j] = questStatus[j + 1]; // 배열 복사
            }

            // 마지막 퀘스트 초기화 (중복 제거)
            questStatus[MAX_QUESTS - 1].accepted = 0;
            questStatus[MAX_QUESTS - 1].questId = -1;
            questStatus[MAX_QUESTS - 1].questName[0] = '\0';
            questStatus[MAX_QUESTS - 1].questcondition = 0;
            questStatus[MAX_QUESTS - 1].questGoal = 0;
            questStatus[MAX_QUESTS - 1].killCount = 0;
            questStatus[MAX_QUESTS - 1].itemCount = 0;
            questStatus[MAX_QUESTS - 1].isCompleted = 0;

            break; // 작업 완료 후 루프 종료
        }
    }
}




// 퀘스트 창 출력
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
            printf("%d 번 퀘스트", j + 1);
            setCursorPosition(10, 11 + 3 * cnt);
            printf("퀘스트 목표: %s", questStatus[i].questName);
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
    _getch();  // 사용자 입력 대기
    initializeMap(); // 맵 초기화
    displayMap(); // 이동 맵 출력
    displayPlayerStat(); //플레이어 스탯 표시
    drawPlayer(); // 플레이어 위치 출력
    displayLog();
    


}