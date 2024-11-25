#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "interaction.h"
#include "quest.h"

/*
setCursorPosition(40, 13);
	printf("1. 당신은 누구요?\n");
	setCursorPosition(40, 14);
	printf("2.주변의 소문은 없소이까?\n");
	setCursorPosition(40, 15);
	printf("3. 할만한 의뢰는 있소이까?\n");
	setCursorPosition(40, 16);
	printf("4. 싸우자\n");
	setCursorPosition(40, 17);
	printf("6. NPC을 떠난다.\n");*/

int outNpcInteract = 0;

void interactionNPC()
{
	if (currentNPC->type == VolunArmy)
		dialogueVolunArmy();
	else if (currentNPC->type == GoverArmy)
		dialogueGoverArmy();
	else if (currentNPC->type == JapArmy)
		dialogueJapArmy();
	else if (currentNPC->type == Nobody)
		dialogueNobody();
}

void interactShop() {
	int num = _getch();
	switch (num)
	{
	case '1':
		if (player.money - hpPotionPrice < 0)
		{
			updateLog("가지고 있는 엽전 갯수가 부족합니다.");
			break;
		}
		else if (Shop1.hpPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		else
		{
			updateLog("체력 포션 1개를 구매하였습니다.");
			player.HPpotion += 1;
			Shop1.hpPotion -= 1;
			player.money -= hpPotionPrice;
		}
		break;
	case '2':
		if (player.money - manaPotionPrice < 0)
		{
			updateLog("가지고 있는 엽전 갯수가 부족합니다.");
			break;
		}
		else if (Shop1.manaPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		else
		{
			updateLog("마나 포션 1개를 구매하였습니다.");
			player.MPpotion += 1;
			Shop1.manaPotion -= 1;
			player.money -= manaPotionPrice;
		}
		break;
	case '3':
		if (player.money - strengthPotionPrice < 0)
		{
			updateLog("가지고 있는 엽전 갯수가 부족합니다.");
			break;
		}
		else if (Shop1.strengthPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		else
		{
			updateLog("힘 포션 1개를 구매하였습니다.");
			player.attack += 1;
			Shop1.strengthPotion -= 1;
			player.money -= strengthPotionPrice;
		}
		break;
	case '4':
		if (player.money - defensePotionPrice < 0)
		{
			updateLog("가지고 있는 엽전 갯수가 부족합니다.");
			break;
		}
		else if (Shop1.accuracyPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		else
		{
			updateLog("방어 포션 1개를 구매하였습니다.");
			player.defense += 1;
			Shop1.defensePotion -= 1;
			player.money -= defensePotionPrice;
		}
		break;
	case '5':
		if (player.money - accuracyPotionPrice < 0)
		{
			updateLog("가지고 있는 엽전 갯수가 부족합니다.");
			break;
		}
		else if (Shop1.accuracyPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		else
		{
			updateLog("명중 포션 1개를 구매하였습니다.");
			player.accuracy += 1;
			Shop1.accuracyPotion -= 1;
			player.money -= accuracyPotionPrice;
		}
		break;
	case '6':
		updateLog("상점을 떠나는걸 선택하셨습니다.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}

void backToDialogue()
{
	while (1) {
		char action = _getch();
		switch (action) {
		case 'A':
		case 'a':
			return;  // 'A'나 'a' 키를 누르면 함수 종료하여 이전 대화로 돌아가기

		default:
			updateLog("잘못된 키를 입력했습니다. A키를 눌러 이전 대화로 돌아가기");
			displayLog();
			break;
		}
	}
}

void backToMap()
{
	while (1) {
        char action = _getch();
        switch (action) {
            case 'A':
            case 'a':
                outNpcInteract = 0;  // NPC 대화 모드 종료
                Situation = 0;
                player.pos = previousPos;  // 플레이어를 이전 위치로 복귀
                return;  // 함수 종료

            default:
                updateLog("잘못된 키를 입력했습니다. A키를 눌러 맵으로 돌아가기");
                displayLog();
                break;
        }
    }
}

void dialogueVolunArmy()
{
	if (strcmp(currentNPC->name, "이정재") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_1();
	if (strcmp(currentNPC->name, "김두환") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_2();
}

void VolunArmyLog_1()
{
	Sleep(100);
	clearScreen();
	if (currentNPC->hasQuest == true && quest[5].clear == 0 && currentNPC->isActive == 1)
	{
		setCursorPosition(40, 11);
		printf(quest[5].title);
		setCursorPosition(40, 12);
		printf(quest[5].description1);
		setCursorPosition(40, 13);
		printf("대화문\n");
		setCursorPosition(40, 14);
		printf("1. 부상당한 의병한테 HP포션 하나를 준다.\n");
		setCursorPosition(40, 15);
		printf("2. 부상당한 의병을 돕지 않는다.\n");
		int choice = _getch();
		if (choice == 'a')
		{
			if (player.HPpotion < 1)
			{
				clearScreen();
				updateLog("가지고 있는 HP포션이 부족합니다.");
				Sleep(200);
				displayLog();
				setCursorPosition(40, 11);
				printf(quest[5].description2);
				setCursorPosition(40, 12);
				printf("미안하오\n");
				quest[5].clear = 2;
				npcList[5].isActive = 0;
				backToMap();
			}
			else
			{
				clearScreen();
				updateLog("부상당한 의병에게 HP포션을 주었습니다.");
				Sleep(200);
				displayLog();
				player.RRelationship += 20;
				player.HPpotion--;
				setCursorPosition(30, 11);
				printf(quest[5].description4);
				quest[5].clear = 1;
				backToMap();
			}
		}
		else if (choice == 'r')
		{
			clearScreen();
			updateLog("부상당한 의병에게 HP포션을 주지 않기로 하였습니다.");
			Sleep(200);
			displayLog();
			setCursorPosition(40, 11);
			printf(quest[5].description2);
			setCursorPosition(40, 12);
			printf("미안하오\n");
			quest[5].clear = 2;
			npcList[5].isActive = 0;
			backToMap();
		}
	}
	else if (quest[5].clear == 1 && currentNPC->isActive == 1)
	{
		clearScreen();
		setCursorPosition(40, 11);
		printf("의병이 쉬고있다. 건드리지 말자.");
		backToMap();
	}
	Sleep(150);
	backToMap();
}

void VolunArmyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("나는 곽재우 장군님을 따르는 의병이오");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("조정이 우리를 버리고 함경도로 넘어갔다고 들었소.");
		setCursorPosition(40, 11);
		printf("백성을 버리고 자기 혼자 도망치다니,");
		setCursorPosition(40, 12);
		printf("전쟁이 끝나면 필히 그 죗값을 치르게 할 것이오");
		setCursorPosition(40, 13);
		printf("대화문\n");
		setCursorPosition(40, 14);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("할만한 일은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[1].clear == 0)
		{
			if (quest[1].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[1].title);
				setCursorPosition(40, 12);
				printf(quest[1].description1);
				setCursorPosition(40, 13);
				printf("대화문\n");
				setCursorPosition(40, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(40, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[1].take = 1;
						player.questmax++;
						acceptQuest(1);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[1].description2);
					setCursorPosition(40, 12);
					printf("대화문\n");
					setCursorPosition(40, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[1].take == 1)
			{
				QuestComplete2();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[1].clear == 1) {
			setCursorPosition(40, 11);
			printf("잘 모르겠는데, 내 친우들에게 한번 물어보겠소.");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 알겠소\n");
		}
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("싸우자");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("농이 너무 심한거 아니오??");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("잘가시오, 왜놈들 조심하고");
		backToMap();
		break;
	}
}
void dialogueGoverArmy()
{
	if (strcmp(currentNPC->name, "장택상") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_1();
	if (strcmp(currentNPC->name, "조병옥") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_2();
}

void GoverArmyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("딱 보면 모르겠소? 왜병 잡으러 온 관군이잖소?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("바다에 이순신 장군님께서 홀로 왜군을 무찌르고 있다고 들었소.");
		setCursorPosition(40, 12);
		printf("허나 그 분을 시샘하는 자들이 많은 것인지");
		setCursorPosition(40, 13);
		printf("조정에서 그자를 잡아들여야 한다는 미친 소리가 돌고 있소.");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("할만한 일은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[6].clear == 0)
		{
			if (quest[6].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[6].title);
				setCursorPosition(40, 12);
				printf(quest[6].description1);
				setCursorPosition(40, 13);
				printf("대화문\n");
				setCursorPosition(40, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(40, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[6].take = 1;
						player.questmax++;
						acceptQuest(6);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[6].description2);
					setCursorPosition(40, 12);
					printf("대화문\n");
					setCursorPosition(40, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[6].take == 1)
			{
				QuestComplete6();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[6].clear == 1) {
			setCursorPosition(40, 11);
			printf("잘 모르겠는데, 장군님께 한번 물어보겠소.");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 알겠소\n");
		}
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("싸우자");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("지금 군을 무시하는 것인가?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("잘가시오, 왜놈들 조심하고");
		backToMap();
		break;
	}
}

void GoverArmyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("딱 보면 모르겠소? 왜병 잡으러 온 관군이잖소?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("바다에 이순신 장군님께서 홀로 왜군을 무찌르고 있다고 들었소.");
		setCursorPosition(40, 12);
		printf("허나 그 분을 시샘하는 자들이 많은 것인지");
		setCursorPosition(40, 13);
		printf("조정에서 그자를 잡아들여야 한다는 미친 소리가 돌고 있소.");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("할만한 일은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[2].clear == 0)
		{
			if (quest[2].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[2].title);
				setCursorPosition(40, 12);
				printf(quest[2].description1);
				setCursorPosition(40, 13);
				printf("대화문\n");
				setCursorPosition(40, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(40, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[2].take = 1;
						player.questmax++;
						acceptQuest(2);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[2].description2);
					setCursorPosition(40, 12);
					printf("대화문\n");
					setCursorPosition(40, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[2].take == 1)
			{
				QuestComplete3();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[2].clear == 1) {
			setCursorPosition(40, 11);
			printf("잘 모르겠는데, 장군님께 한번 물어보겠소.");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 알겠소\n");
		}
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("싸우자");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("지금 군을 무시하는 것인가?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("잘가시오, 왜놈들 조심하고");
		backToMap();
		break;
	}
}

void dialogueJapArmy()
{
	if (strcmp(currentNPC->name, "미와 와사부로") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_1();
	if (strcmp(currentNPC->name, "나까무라") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_2();
}

void JapArmyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("네놈이 잡은 왜군 장수 마와 와사부로다");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("내 말을 어떻게 이해하는지는 모르겠다만");
		setCursorPosition(40, 12);
		printf("우리는 조선을 점령하러 온 것이 아닌 해방시키러 온 거다");
		setCursorPosition(40, 13);
		printf("그러니 풀어주는게 서로 좋을거다");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("원하는 것이 있소?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[7].clear == 0)
		{
			if (quest[7].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[7].title);
				setCursorPosition(40, 12);
				printf(quest[7].description1);
				setCursorPosition(40, 13);
				printf("대화문\n");
				setCursorPosition(40, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(40, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[7].take = 1;
						player.questmax++;
						acceptQuest(7);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[7].description2);
					setCursorPosition(40, 12);
					printf("대화문\n");
					setCursorPosition(40, 13);
					printf("1. 그럴거 같지는 않소\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[7].take == 1)
			{
				QuestComplete7();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[7].clear == 1) {
			//break;
			setCursorPosition(40, 11);
			printf(" ");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 알겠소\n");
		}
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("싸우자");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("바카야로!");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("다른 놈들처럼 행동하지 마시오");
		backToMap();
		break;
	}
}

void JapArmyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("조선을 정벌하러 온 아베 가문의 무사로다.");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("내 말을 어떻게 이해하는지는 모르겠다만");
		setCursorPosition(40, 12);
		printf("우리는 조선을 점령하러 온 것이 아닌 해방시키러 온 거요");
		setCursorPosition(40, 13);
		printf("그대는 우리를 죽이려 하는 저 무지렁이와는 다르길 바라오");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("할만한 일은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[3].clear == 0)
		{
			if (quest[3].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[3].title);
				setCursorPosition(40, 12);
				printf(quest[3].description1);
				setCursorPosition(40, 13);
				printf("대화문\n");
				setCursorPosition(40, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(40, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[3].take = 1;
						player.questmax++;
						acceptQuest(3);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[3].description2);
					setCursorPosition(40, 12);
					printf("대화문\n");
					setCursorPosition(40, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[3].take == 1)
			{
				QuestComplete4();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[3].clear == 1) {
			setCursorPosition(40, 11);
			printf("지금은 딱히 시킬만한 일은 없는 것 같소.");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 알겠소\n");
		}
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("싸우자");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("바카야로!");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("다른 놈들처럼 행동하지 마시오");
		backToMap();
		break;
	}
}
void dialogueNobody()
{
	if (strcmp(currentNPC->name, "장 돌쇠") == 0 && currentNPC->hasQuest == true)
		NobodyLog_1();
	if (strcmp(currentNPC->name, "김 아무개") == 0 && currentNPC->hasQuest == true)
		NobodyLog_2();
}


//퀘스트 없는 무소속 NPC 로그
void NobodyLog_1()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("나는 그냥 평범한 농민이오");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("왜군들이 이동네 저동네를 약탈한다고 들었소.");
		setCursorPosition(40, 12);
		printf("관군이 빨리 와서 우리 좀 지켜줬으면 하는데,");
		setCursorPosition(40, 13);
		printf("아직도 안온거 보면, 소식이 조정까지 전해지지 못했나보오.");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[0].clear == 0)
		{
			if (quest[0].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[0].title);
				setCursorPosition(40, 12);
				printf(quest[0].description1);
				setCursorPosition(40, 13);
				printf("대화문\n");
				setCursorPosition(40, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(40, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[0].take = 1;
						player.questmax++;
						acceptQuest(0);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[0].description2);
					setCursorPosition(40, 12);
					printf("대화문\n");
					setCursorPosition(40, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[0].take == 1)
			{
				QuestComplete1();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[0].clear == 1) {
			setCursorPosition(40, 11);
			printf("잘 모르겠는데, 관아에 가서 물어보시오.");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 알겠소\n");
		}
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("싸우자");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("왜군한테 대가리라도 깨지셨소??");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("잘가시오, 왜놈들 조심하고");
		backToMap();
		break;
	}
}//퀘스트 없는 NPC//
//퀘스트 있는 무소속 NPC 로그
void NobodyLog_2()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("나는 그냥 평범한 농민이오");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;

	case '2':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("왜군들이 이동네 저동네를 약탈한다고 들었소.");
		setCursorPosition(40, 12);
		printf("관군이 빨리 와서 우리 좀 지켜줬으면 하는데,");
		setCursorPosition(40, 13);
		printf("아직도 안온거 보면, 소식이 조정까지 전해지지 못했나보오.");
		setCursorPosition(40, 14);
		printf("대화문\n");
		setCursorPosition(40, 15);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '3':
		updateLog("주변의 소문은 없소이까?");
		displayLog();
		Sleep(100);
		clearScreen();
		if (currentNPC->hasQuest == true && quest[4].clear == 0)
		{
			if (quest[4].take == 0)
			{
				setCursorPosition(40, 11);
				printf(quest[4].title);
				setCursorPosition(40, 12);
				printf(quest[4].description1);
				setCursorPosition(40, 13);
				printf("대화문\n");
				setCursorPosition(40, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(40, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == 'a')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[4].take = 1;
						player.questmax++;
						acceptQuest(4);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(40, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == 'r')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf(quest[4].description2);
					setCursorPosition(40, 12);
					printf("대화문\n");
					setCursorPosition(40, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[4].take == 1)
			{
				QuestComplete5();
				
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[4].clear == 1) {
			setCursorPosition(40, 11);
			printf("잘 모르겠는데, 관아에 가서 물어보시오.");
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 알겠소\n");
		}
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '4':
		updateLog("싸우자");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("왜군한테 대가리라도 깨지셨소??");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
		Sleep(150);
		updateLog("A키를 눌러 이전 대화로 돌아가기");
		backToDialogue();
		break;
	case '6':
		updateLog("NPC을 떠난다");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("잘가시오, 왜놈들 조심하고");
		backToMap();
		break;
	}
}

void interactionQuestItem()
{
	if (currentQuestItem->type == VolunArmy && currentQuestItem->isActive == 1)
		dialogueVolunQuestItem();
	else if (currentQuestItem->type == GoverArmy && currentQuestItem->isActive == 1)
		dialogueGoverQuestItem();
	else if (currentQuestItem->type == JapArmy && currentQuestItem->isActive == 1)
		dialogueJapQuestItem();
	else if (currentQuestItem->type == Nobody && currentQuestItem->isActive == 1)
		dialogueNobodyQuestItem();
}

void dialogueVolunQuestItem()
{
	updateLog("군량을 발견하였습니다.");
	updateLog("[A]를 눌러 획득하거나 [R]을 눌러 맵으로 돌아가세요.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("버튼을 잘못 입력하셨습니다.");
		updateLog("[A]를 눌러 획득하거나 [R]을 눌러 맵으로 돌아가세요.");
		break;
	case 'A':
	case 'a':
		updateLog("군량을 획득하였습니다.");
		QuestItemList[0].isActive = 0;
		player.questitem1 = 1;
		updateLog("맵으로 돌아갑니다.");
		updateQuestStatusItem(1);
		player.pos = previousPos;
		Situation = 0;
		break;
	case 'R':
	case 'r':
		updateLog("맵으로 돌아갑니다.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}

void dialogueGoverQuestItem()
{

}

void dialogueJapQuestItem()
{
	updateLog("작전 서류를 발견하였습니다.");
	updateLog("[A]를 눌러 훔치거나 [R]을 눌러 맵으로 돌아가세요.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("버튼을 잘못 입력하셨습니다.");
		updateLog("[A]를 눌러 훔치거나 [R]을 눌러 맵으로 돌아가세요.");
		break;
	case 'A':
	case 'a':
		updateLog("작전 서류를 훔쳤습니다.");
		QuestItemList[1].isActive = 0;
		player.questitem2 = 1;
		updateLog("맵으로 돌아갑니다.");
		updateQuestStatusItem(3);
		player.pos = previousPos;
		Situation = 0;
		break;
	case 'R':
	case 'r':
		updateLog("맵으로 돌아갑니다.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}

void dialogueNobodyQuestItem()
{
	updateLog("바위를 발견하였습니다.");
	updateLog("[A]를 눌러 치우거나 [R]을 눌러 맵으로 돌아가세요.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("버튼을 잘못 입력하셨습니다.");
		updateLog("[A]를 눌러 치우거나 [R]을 눌러 맵으로 돌아가세요.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		if (player.hp > 1)
		{
			updateLog("바위를 치웠습니다. HP가 1 소모되었습니다.");
			QuestItemList[2].isActive = 0;
			player.questitem3 = 1;
			player.hp--;
			updateLog("맵으로 돌아갑니다.");
			updateQuestStatusItem(4);
			player.pos = previousPos;
			Situation = 0;
			break;
		}
		else
		{
			updateLog("HP가 2 이상이어야 치울수 있습니다.");
			player.pos = previousPos;
			Situation = 0;
			break;
		}
	case 'R':
	case 'r':
		updateLog("맵으로 돌아갑니다.");
		Situation = 0;
		player.pos = previousPos;
		break;
	}
	displayLog();
}

/* 프롤로그 쪽 함수
void interactPrologueNpc()
{
	Sleep(100);
	clearScreen();
	setCursorPosition(40, 11);
	printf(prologuequest.title);
	setCursorPosition(40, 12);
	printf(prologuequest.description1);
	//if (encountPrologueNpc1())
	setCursorPosition(40, 11);
	printf(prologuequest.description2);
	//if (encountPrologueNpc2())
	setCursorPosition(40, 11);
	printf(prologuequest.description3);
}
 */