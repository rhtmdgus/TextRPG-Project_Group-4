#include "displaymap.h"
#include "npc.h"
#include "player.h"
#include <stdio.h>
#include <conio.h>

void displayMap()
{
	system("cls");

	selectmap();

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

	// 맵을 그린 후 남아 있는 모든 적을 다시 표시합니다.
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (currentEnemies[i].hp > 0) {
			drawEnemy(&currentEnemies[i]);
		}
	}
}

void displayShopMap()
{
	system("cls");

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

void displayBattleScreen()
{
	system("cls");
	//맵초기화
	initializeMapBattle();


	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			printf("%c", mapBattle[i][j]);
		}
		printf("\n");
	}

	printPlayer();


	printEnemy(currentEnemy);


}

void displayPlayerStat()
{
	setCursorPosition(101, 1);
	printf("  LEVEL: %d", player.level);
	setCursorPosition(101, 2);
	printf("  EXP: %3d / %3d 엽전: %3d", player.exp, EXPbar, player.money);
	setCursorPosition(101, 3);
	printf("  HP: %3d / %3d", player.hp, maxhp);
	setCursorPosition(101, 4);
	printf("  MP: %3d / %3d", player.mp, maxmp);
	setCursorPosition(101, 5);
	printf("  healing potion: %3d", player.HPpotion);
	setCursorPosition(101, 6);
	printf("  mana potion: %3d", player.MPpotion);
	setCursorPosition(101, 7);
	printf("  attack point: %3d", player.attack);
	setCursorPosition(101, 8);
	printf("  defense point: %3d", player.defense);
	setCursorPosition(101, 9);
	printf("  accuracy point: %3d", player.accuracy);
	setCursorPosition(101, 10);
	printf("  관군과의 관계: %3d", player.JRelationship);
	setCursorPosition(101, 11);
	printf("  의병과의 관계: %3d", player.RRelationship);
	setCursorPosition(101, 12);
	printf("  왜군과의 관계: %3d", player.WRelationship);

	setCursorPosition(101, 15);
	printf("  무기: %s", player.currentweaponName);
	setCursorPosition(101, 17);
	printf("  장비: %s", player.currentequipmentName);
}

void displayEnemyStat(const Enemy* enemy)
{
	if (enemy == nullptr) {
		printf("Error: Enemy data not available.\n");
		return;
	}
	setCursorPosition(101, 14);
	printf("%-70s", enemy->name);
	setCursorPosition(101, 15);
	printf("HP: %3d", enemy->hp);
	setCursorPosition(101, 16);
	printf("attack point: %3d", enemy->attack);
	setCursorPosition(101, 17);
	printf("defense point: %3d", enemy->defense);
}

void displayShopScreen()
{
	setCursorPosition(40, 11);
	printf("번호를 눌러 상품을 구매하세요.\n");
	setCursorPosition(40, 12);
	printf("1. 체력 포션 2원 남은 갯수: %d\n", Shop1.hpPotion);
	setCursorPosition(40, 13);
	printf("2. 마나 포션 2원 남은 갯수: %d\n", Shop1.manaPotion);
	setCursorPosition(40, 14);
	printf("3. 힘 포션 10원 남은 갯수: %d\n", Shop1.strengthPotion);
	setCursorPosition(40, 15);
	printf("4. 방어 포션 10원 남은 갯수: %d\n", Shop1.defensePotion);
	setCursorPosition(40, 16);
	printf("5. 명중 포션 10원 남은 갯수: %d\n", Shop1.accuracyPotion);
	setCursorPosition(40, 17);
	printf("6. 상점을 떠난다.\n");

	displayPlayerStat();
	displayLog();
	interactShop();
	clearScreen();
	displayLog();
}

void displayNPCScreen()
{
	outNpcInteract = 1;
	while(outNpcInteract == 1)
	{
		setCursorPosition(40, 11);
		printf("내 이름은 %s.\n", currentNPC->name);
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 당신은 누구요?\n");
		setCursorPosition(40, 14);
		printf("2.주변의 소문은 없소이까?\n");
		setCursorPosition(40, 15);
		printf("3. 할만한 의뢰는 있소이까?\n");
		setCursorPosition(40, 16);
		printf("4. 싸우자\n");
		setCursorPosition(40, 17);
		printf("6. NPC을 떠난다.\n");
		displayPlayerStat();
		displayLog();
		interactionNPC();
		clearScreen();
		displayLog();
	}
}

void clearScreen()
{
	for (int i = 1; i < MAP_HEIGHT - 1; i++) 
	{
		setCursorPosition(40, i);
		for(int j = 40; j < MAP_WIDTH -1; j++)
			printf(" ");
	}
}