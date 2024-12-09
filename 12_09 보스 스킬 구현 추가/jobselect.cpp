#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "jobselect.h"
#include "player.h"
#include "log.h"


void jobSelect_screen()
{
    // 화면 중앙에 맞추기 위해 여백 줄 추가
    for (int i = 0; i < (MAP_HEIGHT - 20) / 2; i++)
        printf("\n");

    // 중앙 정렬 및 게임 소개 텍스트
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("====================================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                      직  업  선  택                            ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("====================================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("         본인이 선호하는 무기를 다루는 직업을 선택하세요\n\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("           숫자키로 선택을 합니다\n\n");

    // 조작키 설명 섹션
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("====================================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||1. 검사                                                         ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("|| -공격적인 직업으로, 공격력 위주로 스탯이 증가합니다            ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||2. 궁수                                                         ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||-방어력이 낮은 대신 치명타 확률이 높은 직업입니다.  ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("|| 3. 창병                                                        ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||-균형잡힌 직업으로, 전 스탯이 균등하게 증가합니다               ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("|| 4. 방패병                                                      ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||-보호를 우선으로 하는 직업으로, 방어력 위주로 스탯이 증가합니다 ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("====================================================================\n");
   
    jobSelect();

}

void jobSelect()
{
    int num;
    int selectedJob = 0;
    while(1)
    {
        num = _getch();
        switch (num)
        {
        case '1':
            selectedJob = 1;
            setCursorPosition(23, 23);
            printf("%-70s", "검사를 선택하셨습니다.");
            setCursorPosition(23, 24);
            printf("%-70s", "확정이시면 a버튼을 눌러주세요");
            
            break;

        case '2':
            selectedJob = 2;
            setCursorPosition(23, 23);
            printf("%-70s", "궁수를 선택하셨습니다.");
            setCursorPosition(23, 24);
            printf("%-70s", "확정이시면 A버튼을 눌러주세요");
            break;
        case '3':
            selectedJob = 3;
            setCursorPosition(23, 23);
            printf("%-70s", "창병을 선택하셨습니다.");
            setCursorPosition(23, 24);
            printf("%-70s", "확정이시면 A버튼을 눌러주세요");
            break;
        case '4':
            selectedJob = 4;
            setCursorPosition(23, 23);
            printf("%-70s", "방패병을 선택하셨습니다.");
            setCursorPosition(23, 24);
            printf("%-70s", "확정이시면 A버튼을 눌러주세요");
            break;
        case 'a':
        case 'A':
            if (selectedJob != 0)
            {
                switch (selectedJob)
                {
                case 1:
                    player.job = 1;
                    player.attack = 6;
                    player.defense = 3;
                    player.accuracy = 1;
                    updateLog("검사를 선택하셨습니다.");
                    break;
                case 2:
                    player.job = 2;
                    player.attack = 5;
                    player.defense = 2;
                    player.accuracy = 3;
                    updateLog("궁수를 선택하셨습니다.");
                    break;
                case 3:
                    player.job = 3;
                    player.attack = 5;
                    player.defense = 3;
                    player.accuracy = 2;
                    updateLog("창병을 선택하셨습니다.");
                    break;
                case 4:
                    player.job = 4;
                    player.attack = 4;
                    player.defense = 5;
                    player.accuracy = 1;
                    updateLog("방패병을 선택하셨습니다.");
                    break;
                }
                return;
            }
            else
            {
                setCursorPosition(23, 23);
                printf("%-70s", "직업을 먼저 선택해주세요");
            }
        }
    }
}