#include "startscreen.h"
#include <stdio.h>

void start_screen() {	//����ȭ��
	for (int i = 0; i < (MAP_HEIGHT - 16) / 2; i++)
		printf("\n");

	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("||                                                   ||\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("||                ��  ��  ��  ��  ��                 ||\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("||                                                   ||\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("         Text-based RPG Game Set in the Joseon Dynasty\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("           Press [Enter] to start your adventure!\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                        |         |  |\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                      �ѤѤ� \\/  �ѤѤ�\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                        O    /\u005C    O\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                       /|\\  /  \\  /|\\\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                      / | \\/    \\/ | \\\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                       / \\        / \\\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("                      /   \\      /   \\\n\n");
	for (int j = 0; j < (MAP_WIDTH - 57) / 2; j++)
		printf(" ");
	printf("=========================================================\n");

	getchar();  // ����ڷκ��� Enter �Է� ���

}