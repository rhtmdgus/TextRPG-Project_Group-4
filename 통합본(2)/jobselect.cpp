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
    printf("||-���Ÿ����� �����ϴ� ��������, ġ��Ÿ ���ַ� ������ �����մϴ�  ||\n");
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
    char action;
    while(1)
    {
        num = _getch();
        switch (num)
        {
        case '1':
            setCursorPosition(23, 23);
            printf("%-70s", "�˻縦 �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� a��ư�� �����ּ���");
            action = _getch();
            if (action == 'a' || action == 'A')
            {
                //�÷��̾� ���� ����
                player.job = 1;
                player.attack = 4;
                player.defense = 2;
                player.accuracy = 1;
                updateLog("�˻縦 �����ϼ̽��ϴ�.");
                return;
            }
            break;

        case '2':
            setCursorPosition(23, 23);
            printf("%-70s", "�ü��� �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� a��ư�� �����ּ���");
            action = _getch();
            if (action == 'a' || action == 'A')
            {
                //�÷��̾� ���� ����
                player.job = 2;
                player.attack = 2;
                player.defense = 2;
                player.accuracy = 3;
                updateLog("�ü��� �����ϼ̽��ϴ�.");
                return;
            }
            break;
        case '3':
            setCursorPosition(23, 23);
            printf("%-70s", "â���� �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� a��ư�� �����ּ���");
            action = _getch();
            if (action == 'a' || action == 'A')
            {
                //�÷��̾� ���� ����
                player.job = 3;
                player.attack = 2;
                player.defense = 2;
                player.accuracy = 2;
                updateLog("â���� �����ϼ̽��ϴ�.");
                return;
            }
            break;
        case '4':
            setCursorPosition(23, 23);
            printf("%-70s", "���к��� �����ϼ̽��ϴ�.");
            setCursorPosition(23, 24);
            printf("%-70s", "Ȯ���̽ø� a��ư�� �����ּ���");
            action = _getch();
            if (action == 'a' || action == 'A')
            {
                //�÷��̾� ���� ����
                player.job = 4;
                player.attack = 2;
                player.defense = 4;
                player.accuracy = 1;
                updateLog("���к��� �����ϼ̽��ϴ�.");
                return;
            }
            break;
        }
    }
}