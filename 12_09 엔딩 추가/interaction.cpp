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
	if (strcmp(currentNPC->name, "김영태") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_3();
	if (strcmp(currentNPC->name, "김무옥") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_4();
	if (strcmp(currentNPC->name, "문영철") == 0 && currentNPC->hasQuest == true)
		VolunArmyLog_5();
}

void VolunArmyLog_1()
{
	Sleep(100);
	clearScreen();
	if (currentNPC->hasQuest == true && quest[5].clear == 0 && currentNPC->isActive == 1)
	{
		setCursorPosition(30, 11);
		printf(quest[5].title);
		setCursorPosition(30, 12);
		printf(quest[5].description1);
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
		printf("1. 부상당한 의병한테 체력물약 하나를 준다.\n");
		setCursorPosition(30, 15);
		printf("2. 부상당한 의병을 돕지 않는다.\n");
		int choice = _getch();
		if (choice == '1')
		{
			if (player.HPpotion < 1)
			{
				clearScreen();
				updateLog("가지고 있는 체력물약이 부족합니다.");
				Sleep(200);
				displayLog();
				setCursorPosition(30, 11);
				printf(quest[5].description2);
				setCursorPosition(30, 12);
				printf("미안하오\n");
				quest[5].clear = 2;
				npcList[5].isActive = 0;
				backToMap();
			}
			else
			{
				clearScreen();
				updateLog("부상당한 의병에게 체력물약을 주었습니다.");
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
		else if (choice == '2')
		{
			clearScreen();
			updateLog("부상당한 의병에게 체력물약을 주지 않기로 하였습니다.");
			Sleep(200);
			displayLog();
			setCursorPosition(30, 11);
			printf(quest[5].description2);
			setCursorPosition(30, 12);
			printf("미안하오\n");
			quest[5].clear = 2;
			npcList[5].isActive = 0;
			backToMap();
		}
	}
	else if (quest[5].clear == 1 && currentNPC->isActive == 1)
	{
		clearScreen();
		setCursorPosition(30, 11);
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
		setCursorPosition(30, 11);
		printf("나는 이 고을의 의병이다.");
		setCursorPosition(30, 12);
		printf("왜적에게 죽은 가족을 생각하며 여기까지 왔지");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("들리는 말로는 적군이 근처 마을을 약탈하고 있다더군.");
		setCursorPosition(30, 12);
		printf("조심하는 게 좋을 거야,");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
				setCursorPosition(30, 11);
				printf(quest[1].title);
				setCursorPosition(30, 12);
				printf(quest[1].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
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
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[1].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
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
			clearScreen();
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 내 친우들에게 한번 물어보겠소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("지금 나랑 장난하는 건가? 저리 가게");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가게, 왜놈들 조심하고");
		backToMap();
		break;
	}
}
void VolunArmyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("나? 그냥 농사짓던 사람인데,");
		setCursorPosition(30, 12);
		printf("전쟁통에 도망칠 곳도 없어 여기 왔지");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("왜적이 점점 북쪽으로 진격하고 있다는 소문이 있어.");
		setCursorPosition(30, 12);
		printf("방비를 단단히 해야겠어.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[10].clear == 0)
		{
			if (quest[10].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[10].title);
				setCursorPosition(30, 12);
				printf(quest[10].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[10].take = 1;
						player.questmax++;
						acceptQuest(10);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[10].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[10].take == 1)
			{
				QuestComplete10();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[10].clear == 1) {
			setCursorPosition(30, 11);
			printf("잘 모르겠는데? 친구들한테 한번 물어볼께.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("재미 없는 농담이군");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가, 몸 조심하고");
		backToMap();
		break;
	}
}
void VolunArmyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("전장에서 왜적을 쳐 부수는 의병이다.");
		setCursorPosition(30, 12);
		printf("이제 더는 물러설 곳이 없다.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("장군께서 새로운 병력을 모으고 계신다던데,");
		setCursorPosition(30, 12);
		printf("너도 참여해 볼 생각 있나?");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[11].clear == 0)
		{
			if (quest[11].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[11].title);
				setCursorPosition(30, 12);
				printf(quest[11].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[11].take = 1;
						player.questmax++;
						acceptQuest(11);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[11].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[11].take == 1)
			{
				QuestComplete11();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[11].clear == 1) {
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 다른 동료들께 한번 물어보겠소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("농이 너무 심한거 아닌가?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가시게, 왜놈들 조심하고");
		backToMap();
		break;
	}
}
void VolunArmyLog_5()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("내가 누군지는 중요치 않아,");
		setCursorPosition(30, 12);
		printf("이 나라를 위해 싸우는 의병일 뿐이다.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("소문이야 많지, 하지만 적의 동태를 알고 싶다면,");
		setCursorPosition(30, 12);
		printf("산골짜기에 있는 정찰병을 찾아봐");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[12].clear == 0)
		{
			if (quest[12].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[12].title);
				setCursorPosition(30, 12);
				printf(quest[12].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[12].take = 1;
						player.questmax++;
						acceptQuest(12);
						backToDialogue();
						spawnBoss2();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[12].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[12].take == 1)
			{
				QuestComplete12();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[12].clear == 1) {
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 다른 장군들에게 한번 물어보겠소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("같은 동료끼리 이러기요?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가시오, 몸 조심하고");
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
	if (strcmp(currentNPC->name, "조개옥") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_3();
	if (strcmp(currentNPC->name, "김종원") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_4();
	if (strcmp(currentNPC->name, "김창룡") == 0 && currentNPC->hasQuest == true)
		GoverArmyLog_5();
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
		setCursorPosition(30, 11);
		printf("나는 조선 관군이다.");
		setCursorPosition(30, 12);
		printf("이 전쟁에서 나라를 지키는 게 내 임무다.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("왜군이 가까운 해안가에 진을 쳤다는 정보가 들어왔다.");
		setCursorPosition(30, 12);
		printf("그 때문에 모두 긴장하고 있어.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
				setCursorPosition(30, 11);
				printf(quest[6].title);
				setCursorPosition(30, 12);
				printf(quest[6].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[6].take = 1;
						player.questmax++;
						acceptQuest(6);
						backToDialogue();
						spawnBoss1();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[6].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
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
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 장군님께 한번 물어보겠소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("지금 군을 무시하는 것인가?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가라, 왜놈들 조심하고");
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
		setCursorPosition(30, 11);
		printf("조선의 명을 받아 이곳을 지키고 있다.");
		setCursorPosition(30, 12);
		printf("적을 물리치기 위해 싸우는 병사다.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("근처에서 의병들과 협력해 작전을 세우고 있다고 해,");
		setCursorPosition(30, 12);
		printf("왜적의 보급을 끊을 계획이라 도움이 필요할지도 모르겠군.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
				setCursorPosition(30, 11);
				printf(quest[2].title);
				setCursorPosition(30, 12);
				printf(quest[2].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
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
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[2].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
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
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 다른 장군들께 한번 물어보지.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("지금 반란을 할 생각인가?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가시게, 몸 조심하고");
		backToMap();
		break;
	}
}
void GoverArmyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("나는 이 지역을 방어하는 관군 장교다.");
		setCursorPosition(30, 12);
		printf("무슨 이유로 나에게 온 것인가?");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("왜적의 수가 점점 늘고 있다는 소문이 있다.");
		setCursorPosition(30, 12);
		printf("전투 준비는 철저히 해야 할 것이다.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[13].clear == 0)
		{
			if (quest[13].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[13].title);
				setCursorPosition(30, 12);
				printf(quest[13].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[13].take = 1;
						player.questmax++;
						acceptQuest(13);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[13].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[13].take == 1)
			{
				QuestComplete13();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[13].clear == 1) {
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 다른 장군한테 한번 물어보지.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("재미 없으니 그만하게");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가시게, 왜군들 조심하고");
		backToMap();
		break;
	}
}
void GoverArmyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("나에대해 궁금해 하는 이유가 있나?");
		setCursorPosition(30, 12);
		printf("난 그저 나라를 위해 싸우고 있을 뿐이야.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("가까운 산골짜기에서 의문의 움직임이 포착 되었다고 한다.");
		setCursorPosition(30, 12);
		printf("왜군의 첩자인지, 의병인지는 아직 알수가 없어.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[14].clear == 0)
		{
			if (quest[14].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[14].title);
				setCursorPosition(30, 12);
				printf(quest[14].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[14].take = 1;
						player.questmax++;
						acceptQuest(14);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[14].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[14].take == 1)
			{
				QuestComplete14();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[14].clear == 1) {
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 동료한테 한번 물어보겠소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("지금 왜군의 편을 드는 것인가?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가, 몸 조심하고");
		backToMap();
		break;
	}
}
void GoverArmyLog_5()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("딱 보면 모르겠소? 왜병 잡으러 온 관군이잖소?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("바다에 이순신 장군님께서 홀로 왜군을 무찌르고 있다고 들었소.");
		setCursorPosition(30, 12);
		printf("허나 그 분을 시샘하는 자들이 많은 것인지");
		setCursorPosition(30, 13);
		printf("조정에서 그자를 잡아들여야 한다는 미친 소리가 돌고 있소.");
		setCursorPosition(30, 14);
		printf("대화문\n");
		setCursorPosition(30, 15);
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
		if (currentNPC->hasQuest == true && quest[15].clear == 0)
		{
			if (quest[15].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[15].title);
				setCursorPosition(30, 12);
				printf(quest[15].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[15].take = 1;
						player.questmax++;
						acceptQuest(15);
						backToDialogue();
						spawnBoss2();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[15].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[15].take == 1)
			{
				QuestComplete15();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[15].clear == 1) {
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 조정에 한번 물어보겠소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("지금 무얼 하는 것인가?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가시오, 혼란한 시대이니 몸 조심하고.");
		backToMap();
		break;
	}
}

void dialogueJapArmy()
{
	if (strcmp(currentNPC->name, "미와 와사부로") == 0 && currentNPC->hasQuest == true && currentNPC->isActive == 1)
		JapArmyLog_1();
	if (strcmp(currentNPC->name, "나까무라") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_2();
	if (strcmp(currentNPC->name, "마에다") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_3();
	if (strcmp(currentNPC->name, "아사노") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_4();
	if (strcmp(currentNPC->name, "마쓰라") == 0 && currentNPC->hasQuest == true)
		JapArmyLog_5();
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
		setCursorPosition(30, 11);
		printf("네놈이 잡은 왜군 장수 마와 와사부로다");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("내 말을 어떻게 이해하는지는 모르겠다만");
		setCursorPosition(30, 12);
		printf("우리는 조선을 점령하러 온 것이 아닌 해방시키러 온 거다");
		setCursorPosition(30, 13);
		printf("그러니 풀어주는게 서로 좋을거다");
		setCursorPosition(30, 14);
		printf("대화문\n");
		setCursorPosition(30, 15);
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
				setCursorPosition(30, 11);
				printf(quest[7].title);
				setCursorPosition(30, 12);
				printf(quest[7].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
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
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[7].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 그럴거 같지는 않소\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[7].take == 1)
			{
				QuestComplete7();
				if (currentNPC->isActive == 0)
				{
					backToMap();
					break;
				}
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[7].clear == 1) {
			//break;
			setCursorPosition(30, 11);
			printf(" ");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("뭔 소리를 하는거야!");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("빌어먹을 놈.");
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
		setCursorPosition(30, 11);
		printf("나는 일본 대군의 일원이다.");
		setCursorPosition(30, 12);
		printf("우리 군의 위력을 곧 알게 될 것이다.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("들리는 소문으로는 조선의 관군이 참패하고 있다던데,");
		setCursorPosition(30, 12);
		printf("과연 네놈이 그 소문을 바꿀수 있을까?");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
				setCursorPosition(30, 11);
				printf(quest[3].title);
				setCursorPosition(30, 12);
				printf(quest[3].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
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
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[3].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
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
			setCursorPosition(30, 11);
			printf("지금은 딱히 시킬만한 일은 없는 것 같은데?");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("바카야로!");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("다른 놈들처럼 행동하지 말게");
		backToMap();
		break;
	}
}
void JapArmyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("나는 왜군의 선봉대다.");
		setCursorPosition(30, 12);
		printf("조선은 우리 발 밑에서 사라질 운명이다.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("조선에 의병이라..");
		setCursorPosition(30, 12);
		printf("농민들이 들고 일어난다 한들,");
		setCursorPosition(30, 13);
		printf("우리 군에겐 아무런 위협도 되지 않는다.");
		setCursorPosition(30, 14);
		printf("대화문\n");
		setCursorPosition(30, 15);
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
		if (currentNPC->hasQuest == true && quest[16].clear == 0)
		{
			if (quest[16].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[16].title);
				setCursorPosition(30, 12);
				printf(quest[16].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[16].take = 1;
						player.questmax++;
						acceptQuest(16);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[16].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[16].take == 1)
			{
				QuestComplete16();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[16].clear == 1) {
			setCursorPosition(30, 11);
			printf("지금은 딱히 시킬만한 일이 없어.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("갑자기 무슨 헛소리야?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘 가게나");
		backToMap();
		break;
	}
}
void JapArmyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("그런걸 왜 묻는거지?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("조선군이 새로운 병력을 모집하고 있다던데,");
		setCursorPosition(30, 12);
		printf("하지만 우리에겐 그저 새로운 먹잇감일 뿐이야.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[17].clear == 0)
		{
			if (quest[17].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[17].title);
				setCursorPosition(30, 12);
				printf(quest[17].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[17].take = 1;
						player.questmax++;
						acceptQuest(17);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[17].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[17].take == 1)
			{
				QuestComplete17();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[17].clear == 1) {
			setCursorPosition(30, 11);
			printf("일? 딱히 없는데 한번 찾아보지.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("갑자기 왜이래?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("빨리 전쟁을 끝내고 한탕하고 싶구만");
		backToMap();
		break;
	}
}
void JapArmyLog_5()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("조선놈들을 처부술 일본군 장군이다.");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("소문? 전쟁에서 소문 보다는 무력이지.");
		setCursorPosition(30, 12);
		printf("직접 우리 일본군을 보고 배워라.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[18].clear == 0)
		{
			if (quest[18].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[18].title);
				setCursorPosition(30, 12);
				printf(quest[18].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[18].take = 1;
						player.questmax++;
						acceptQuest(18);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[18].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[18].take == 1)
			{
				QuestComplete18();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[18].clear == 1) {
			setCursorPosition(30, 11);
			printf("더 할 일은 없어.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("진심이냐?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("우리 왜군이 조선을 먹을날이 머지않았다.");
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
	if (strcmp(currentNPC->name, "김일동") == 0 && currentNPC->hasQuest == true)
		NobodyLog_3();
	if (strcmp(currentNPC->name, "고돌쇠") == 0 && currentNPC->hasQuest == true)
		NobodyLog_4();
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
		setCursorPosition(30, 11);
		printf("나는 그냥 평범한 농민이요.");
		setCursorPosition(30, 12);
		printf("전쟁때문에 요즘 살기가 힘들군..");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("왜군들이 이동네 저동네를 약탈한다고 들었소.");
		setCursorPosition(30, 12);
		printf("관군이 빨리 와서 우리 좀 지켜줬으면 하는데,");
		setCursorPosition(30, 13);
		printf("아직도 안온거 보면, 소식이 조정까지 전해지지 못했나보오.");
		setCursorPosition(30, 14);
		printf("대화문\n");
		setCursorPosition(30, 15);
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
		if (currentNPC->hasQuest == true && quest[0].clear == 0)
		{
			if (quest[0].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[0].title);
				setCursorPosition(30, 12);
				printf(quest[0].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
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
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[0].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
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
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 관아에 가서 물어보시오.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("왜군한테 대가리라도 깨지셨소??");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
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
		setCursorPosition(30, 11);
		printf("나는 그저 평범한 평민일 뿐이네,");
		setCursorPosition(30, 12);
		printf("전쟁통에 할 게 너무나도 많군.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("일을 하느라 소문을 들을 틈도 없다네.");
		setCursorPosition(30, 12);
		printf("근처 양반들은 전부다 피난을 간듯허이.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[4].clear == 0)
		{
			if (quest[4].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[4].title);
				setCursorPosition(30, 12);
				printf(quest[4].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
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
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[4].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
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
			setCursorPosition(30, 11);
			printf("잘 모르겠는데, 관군한테 가보는건 어떤가?");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("힘들어 죽겠는데 그런 장난 하지 마시오.");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가시오, 몸 조심하고");
		backToMap();
		break;
	}
}
void NobodyLog_3()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("나는 그냥 평범한 농민이오.");
		setCursorPosition(30, 12);
		printf("이 전쟁에서 살아남으려고 노력하는 사람일세.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		setCursorPosition(30, 11);
		printf("왜군들이 엄청나게 약탈을 해대고 있다네.");
		setCursorPosition(30, 12);
		printf("자네도 조심하시게.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[8].clear == 0)
		{
			if (quest[8].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[8].title);
				setCursorPosition(30, 12);
				printf(quest[8].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[8].take = 1;
						player.questmax++;
						acceptQuest(8);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[8].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[8].take == 1)
			{
				QuestComplete8();

				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[8].clear == 1) {
			setCursorPosition(30, 11);
			printf("딱히 없는 것 같소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("자네까지 왜 이러는가?");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가게, 위험한 시대야.");
		backToMap();
		break;
	}
}

void NobodyLog_4()
{
	int num = _getch();
	switch (num)
	{
	case '1':
		updateLog("당신은 누구요?");
		displayLog();
		Sleep(100);
		clearScreen();
		setCursorPosition(30, 11);
		printf("하루 벌어 하루 먹고사는 농민이오.");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("관군이 상황이 생각보다 좋지 않다 하오.");
		setCursorPosition(30, 12);
		printf("그래도 바다에서 이순신이란 장군이 활약하고 있다 하오.");
		setCursorPosition(30, 13);
		printf("대화문\n");
		setCursorPosition(30, 14);
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
		if (currentNPC->hasQuest == true && quest[9].clear == 0)
		{
			if (quest[9].take == 0)
			{
				setCursorPosition(30, 11);
				printf(quest[9].title);
				setCursorPosition(30, 12);
				printf(quest[9].description1);
				setCursorPosition(30, 13);
				printf("대화문\n");
				setCursorPosition(30, 14);
				printf("1. 수락한다.\n");
				setCursorPosition(30, 15);
				printf("2. 거절한다.\n");
				int choice = _getch();
				if (choice == '1')
				{
					if (player.questmax < 3)
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트를 수락하셨습니다!");
						updateLog("퀘스트를 수락하셨습니다!");
						quest[9].take = 1;
						player.questmax++;
						acceptQuest(9);
						backToDialogue();
						break;
					}
					else
					{
						clearScreen();
						setCursorPosition(30, 11);
						printf("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						updateLog("퀘스트는 한번에 최대 3개까지 수락 가능합니다!");
						backToDialogue();
						break;
					}
				}
				else if (choice == '2')
				{
					clearScreen();
					setCursorPosition(30, 11);
					printf(quest[9].description2);
					setCursorPosition(30, 12);
					printf("대화문\n");
					setCursorPosition(30, 13);
					printf("1. 미안하오\n");
					updateLog("퀘스트를 거절하셨습니다!");
					backToDialogue();
					break;
				}
			}
			else if (quest[9].take == 1)
			{
				QuestComplete9();
				break;
			}

		}
		else if (currentNPC->hasQuest == false || quest[9].clear == 1) {
			setCursorPosition(30, 11);
			printf("잘 모르겠소.");
			setCursorPosition(30, 12);
			printf("대화문\n");
			setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("장난치지 말아주셨으면 하오.");
		setCursorPosition(30, 12);
		printf("대화문\n");
		setCursorPosition(30, 13);
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
		setCursorPosition(30, 11);
		printf("잘가시오, 몸 조심하고");
		backToMap();
		break;
	}
}
void interactionQuestItem()
{
	if (currentQuestItem->type == VolunArmyQ && currentQuestItem->isActive == 1)
		dialogueVolunQuestItem();
	else if (currentQuestItem->type == GoverArmyQ && currentQuestItem->isActive == 1)
		dialogueGoverQuestItem();
	else if (currentQuestItem->type == JapArmyQ && currentQuestItem->isActive == 1)
		dialogueJapQuestItem();
	else if (currentQuestItem->type == NobodyQ && currentQuestItem->isActive == 1)
		dialogueNobodyQuestItem();
}

void dialogueVolunQuestItem()
{
	if (strcmp(currentQuestItem->name, "군량") == 0)
		VolunItemLog_1();
	if (strcmp(currentQuestItem->name, "왜군 식량 창고") == 0)
		VolunItemLog_2();
}
void VolunItemLog_1()
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
		updateQuestStatusItem(1); // quest[1] 퀘스트 아이템
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
void VolunItemLog_2()
{
	updateLog("왜군 식량 창고를 발견하였습니다.");
	updateLog("[A]를 눌러 불태우거나 [R]을 눌러 맵으로 돌아가세요.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("버튼을 잘못 입력하셨습니다.");
		updateLog("[A]를 눌러 불태우거나 [R]을 눌러 맵으로 돌아가세요.");
		break;
	case 'A':
	case 'a':
		updateLog("왜군 식량 창고를 불태웠습니다.");
		QuestItemList[3].isActive = 0;
		player.questitem2 = 1;
		updateLog("맵으로 돌아갑니다.");
		updateQuestStatusItem(11); // quest[11] 퀘스트 아이템
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
	updateLog("군수물자를 발견하였습니다.");
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
		QuestItemList[5].isActive = 0;
		player.questitem2 = 1;
		updateLog("맵으로 돌아갑니다.");
		updateQuestStatusItem(14); // quest[14] 퀘스트 아이템
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

void dialogueJapQuestItem()
{
	if (strcmp(currentQuestItem->name, "작전 서류") == 0)
		JapItemLog_1();
	if (strcmp(currentQuestItem->name, "수탈한 물품") == 0)
		JapItemLog_2();
}

void JapItemLog_1()
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
		updateQuestStatusItem(3);  // quest[3] 퀘스트 아이템
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
void JapItemLog_2()
{
	updateLog("수탈한 물품을 발견하였습니다.");
	updateLog("[A]를 눌러 챙기거나 [R]을 눌러 맵으로 돌아가세요.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("버튼을 잘못 입력하셨습니다.");
		updateLog("[A]를 눌러 챙기거나 [R]을 눌러 맵으로 돌아가세요.");
		break;
	case 'A':
	case 'a':
		updateLog("수탈한 물품을 챙겼습니다.");
		QuestItemList[4].isActive = 0;
		player.questitem2 = 1;
		updateLog("맵으로 돌아갑니다.");
		updateQuestStatusItem(17); // quest[17] 퀘스트 아이템
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
	if (strcmp(currentQuestItem->name, "바위") == 0)
		NobodyItemLog_1();
	if (strcmp(currentQuestItem->name, "벼") == 0)
		NobodyItemLog_2();
}
void NobodyItemLog_1()
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
			updateQuestStatusItem(4); // quest[4] 퀘스트 아이템
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
void NobodyItemLog_2()
{
	updateLog("벼를 발견하였습니다.");
	updateLog("[A]를 눌러 수확하거나 [R]을 눌러 맵으로 돌아가세요.");
	displayLog();
	char action = _getch();
	switch (action)
	{
	default:
		updateLog("버튼을 잘못 입력하셨습니다.");
		updateLog("[A]를 눌러 수확하거나 [R]을 눌러 맵으로 돌아가세요.");
		break;
	case 'A':
	case 'a':
		Sleep(100);
		if (player.hp > 2)
		{
			updateLog("벼를 수확하였습니다. HP가 2 소모되었습니다.");
			QuestItemList[6].isActive = 0;
			player.questitem1 = 1;
			player.hp -= 2;
			updateLog("맵으로 돌아갑니다.");
			updateQuestStatusItem(9); // quest[9] 퀘스트 아이템
			player.pos = previousPos;
			Situation = 0;
			break;
		}
		else
		{
			updateLog("HP가 3 이상이어야 치울수 있습니다.");
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