#include "tutorialscreen.h"
#include <stdio.h>

void tutorial_screen()
{
    // ȭ�� �߾ӿ� ���߱� ���� ���� �� �߰�
    for (int i = 0; i < (MAP_HEIGHT - 20) / 2; i++)
        printf("\n");

    // �߾� ���� �� ���� �Ұ� �ؽ�Ʈ
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("=========================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                                                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                  ��  ��  ��  ��                     ||\n");
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

    // ����Ű ���� ����
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("=========================================================\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                  ��  ��  ��  ��                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                                                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||   [����Ű] : �̵�                                   ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||   [A] �Ǵ� [R] : NPC�� ��ȣ�ۿ� �� ���� ����        ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||   [��ȣŰ] : �������� ���� ���� �� NPC�� ��ȭ       ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("||                                                     ||\n");
    for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
        printf(" ");
    printf("=========================================================\n");

    getchar();  // ����ڷκ��� Enter �Է� ���
}
