#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "jobselect.h"
#include "player.h"
#include "log.h"


void jobSelect_screen()
{
    // ȭ�� �߾ӿ� ���߱� ���� ���� �� �߰�
    for (int i = 0; i < (MAP_HEIGHT - 20) / 2; i++)
        printf("\n");

    // �߾� ���� �� ���� �Ұ� �ؽ�Ʈ
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("====================================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                      ��  ��  ��  ��                            ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("====================================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("         ������ ��ȣ�ϴ� ���⸦ �ٷ�� ������ �����ϼ���\n\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("           ����Ű�� ������ �մϴ�\n\n");

    // ����Ű ���� ����
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("====================================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||1. �˻�                                                         ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("|| -�������� ��������, ���ݷ� ���ַ� ������ �����մϴ�            ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||2. �ü�                                                         ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||-������ ���� ��� ġ��Ÿ Ȯ���� ���� �����Դϴ�.  ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("|| 3. â��                                                        ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||-�������� ��������, �� ������ �յ��ϰ� �����մϴ�               ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("|| 4. ���к�                                                      ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||-��ȣ�� �켱���� �ϴ� ��������, ���� ���ַ� ������ �����մϴ� ||\n");
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
            printf("%-70s", "�˻縦 �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� a��ư�� �����ּ���");
            
            break;

        case '2':
            selectedJob = 2;
            setCursorPosition(23, 23);
            printf("%-70s", "�ü��� �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� A��ư�� �����ּ���");
            break;
        case '3':
            selectedJob = 3;
            setCursorPosition(23, 23);
            printf("%-70s", "â���� �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� A��ư�� �����ּ���");
            break;
        case '4':
            selectedJob = 4;
            setCursorPosition(23, 23);
            printf("%-70s", "���к��� �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� A��ư�� �����ּ���");
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
                    updateLog("�˻縦 �����ϼ̽��ϴ�.");
                    break;
                case 2:
                    player.job = 2;
                    player.attack = 5;
                    player.defense = 2;
                    player.accuracy = 3;
                    updateLog("�ü��� �����ϼ̽��ϴ�.");
                    break;
                case 3:
                    player.job = 3;
                    player.attack = 5;
                    player.defense = 3;
                    player.accuracy = 2;
                    updateLog("â���� �����ϼ̽��ϴ�.");
                    break;
                case 4:
                    player.job = 4;
                    player.attack = 4;
                    player.defense = 5;
                    player.accuracy = 1;
                    updateLog("���к��� �����ϼ̽��ϴ�.");
                    break;
                }
                return;
            }
            else
            {
                setCursorPosition(23, 23);
                printf("%-70s", "������ ���� �������ּ���");
            }
        }
    }
}