#include "tutorialscreen.h"
#include <stdio.h>

void tutorial_screen()
{
    // 화면 중앙에 맞추기 위해 여백 줄 추가
    for (int i = 0; i < (MAP_HEIGHT - 20) / 2; i++)
        printf("\n");

    // 중앙 정렬 및 게임 소개 텍스트
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("=========================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                                                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                  진  행  방  식                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                                                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("=========================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("         Text-based RPG Game Set in the Joseon Dynasty\n\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("           Press [Enter] to start your adventure!\n\n");

    // 조작키 설명 섹션
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("=========================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                  조  작  방  법                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                                                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||   [방향키] : 이동                                   ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||   [A] 또는 [R] : NPC와 상호작용 및 전투 선택        ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||   [번호키] : 상점에서 물건 구매 및 NPC와 대화       ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                                                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("=========================================================\n");

    getchar();  // 사용자로부터 Enter 입력 대기
}
