#pragma warning(disable:4996)
#include "currentquest.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

CurrentQuest questlist[3] = { {"", "", 0}, {"", "", 0}, {"", "", 0} };

void displayquest() {
    system("cls");
    printf("===== 현재 진행중인 퀘스트 =====\n");
    for (int i = 0; i < 3; i++) {
        if (strlen(questlist[i].title) > 0) {
            printf("[%d] %s (%d%% 진행)\n", i + 1, questlist[i].title, questlist[i].progress);
            printf("    %s\n", questlist[i].description);
        }
    }
    printf("=============================\n");
    printf("게임으로 돌아가려면 아무 키나 누르세요...\n");
    _getch();
}

int updatequestlist(const char* questTitle, const char* questDescription, int progress) {
    for (int i = 0; i < 3; i++) {
        if (strlen(questlist[i].title) == 0) {
            strncpy(questlist[i].title, questTitle, sizeof(questlist[i].title));
            strncpy(questlist[i].description, questDescription, sizeof(questlist[i].description));
            questlist[i].progress = progress;
            return 1; // 퀘스트 추가 성공
        }
    }
    printf("퀘스트를 더 이상 받을 수 없습니다. 최대 3개의 퀘스트만 수락할 수 있습니다.\n");
    return 0; // 퀘스트 추가 실패
}