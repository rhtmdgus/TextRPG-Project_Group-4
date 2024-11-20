#pragma warning(disable:4996)
#include "currentquest.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

CurrentQuest questlist[3] = { {"", "", 0}, {"", "", 0}, {"", "", 0} };

void displayquest() {
    system("cls");
    printf("===== ���� �������� ����Ʈ =====\n");
    for (int i = 0; i < 3; i++) {
        if (strlen(questlist[i].title) > 0) {
            printf("[%d] %s (%d%% ����)\n", i + 1, questlist[i].title, questlist[i].progress);
            printf("    %s\n", questlist[i].description);
        }
    }
    printf("=============================\n");
    printf("�������� ���ư����� �ƹ� Ű�� ��������...\n");
    _getch();
}

int updatequestlist(const char* questTitle, const char* questDescription, int progress) {
    for (int i = 0; i < 3; i++) {
        if (strlen(questlist[i].title) == 0) {
            strncpy(questlist[i].title, questTitle, sizeof(questlist[i].title));
            strncpy(questlist[i].description, questDescription, sizeof(questlist[i].description));
            questlist[i].progress = progress;
            return 1; // ����Ʈ �߰� ����
        }
    }
    printf("����Ʈ�� �� �̻� ���� �� �����ϴ�. �ִ� 3���� ����Ʈ�� ������ �� �ֽ��ϴ�.\n");
    return 0; // ����Ʈ �߰� ����
}