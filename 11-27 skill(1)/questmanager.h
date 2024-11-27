#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "quest.h"


// 퀘스트 진행상황을 관리하는 구조체
typedef struct QuestStatus {
    int accepted = 0;    // 퀘스트가 비어있는지 아닌지
    int questId = -1;         // 무슨 퀘스트인지
    int questcondition;  // 퀘스트 조건 type -> ==0일시 아이템형, ==1일시 사냥형
    int killCount = 0;   // 적군 킬 카운트
    int itemCount = 0;   // 아이템 획득 카운트
    int isCompleted = 0;     // 퀘스트 완료 여부
    char questName[50] = " ";
    int questGoal = 1;
} QuestStatus;



// 퀘스트 수락 함수
void acceptQuest(int questId);

// 퀘스트 진행상황을 업데이트하는 함수, 아이템형
void updateQuestStatusItem(int questId);

// 퀘스트 진행상황을 업데이트하는 함수, 아이템형
void updateQuestStatusKill();

// 퀘스트를 완료하면 퀘스트창을 업데이트하는 함수
void completeQuest(int questId);

// 퀘스트 창을 출력하는 함수
void printQuestWindow();



#endif // QUESTMANAGER_H
