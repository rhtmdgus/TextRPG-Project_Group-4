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
	else
		dialogueNobody();
}

void interactShop() {
	int num = _getch();
	switch (num)
	{
	case '1':
		if (Shop1.hpPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("체력 포션 1개를 구매하였습니다.");
		player.HPpotion += 1;
		Shop1.hpPotion -= 1;
		break;
	case '2':
		if (Shop1.manaPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("마나 포션 1개를 구매하였습니다.");
		player.MPpotion += 1;
		Shop1.manaPotion -= 1;
		break;
	case '3':
		if (Shop1.strengthPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("힘 포션 1개를 구매하였습니다.");
		player.attack += 1;
		Shop1.strengthPotion -= 1;
		break;
	case '4':
		if (Shop1.accuracyPotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("명중 포션 1개를 구매하였습니다.");
		player.accuracy += 1;
		Shop1.accuracyPotion -= 1;
		break;
	case '5':
		if (Shop1.defensePotion <= 0)
		{
			updateLog("상품 수량이 부족합니다.");
			break;
		}
		updateLog("방어 포션 1개를 구매하였습니다.");
		player.defense += 1;
		Shop1.defensePotion -= 1;
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
		setCursorPosition(40, 11);
		if (currentNPC->hasQuest == false)
			printf("잘 모르겠는데, 내 친우들에게 한번 물어보겠소.");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
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
		setCursorPosition(40, 11);
		printf("허나 그 분을 시샘하는 자들이 많은 것인지");
		setCursorPosition(40, 12);
		printf("조정에서 그자를 잡아들여야 한다는 미친 소리가 돌고 있소.");
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
		setCursorPosition(40, 11);
		if (currentNPC->hasQuest == false)
			printf("잘 모르겠는데, 장군님께 한번 여쭤보겠소.");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
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
		setCursorPosition(40, 11);
		printf("우리는 조선을 점령하러 온 것이 아닌 해방시키러 온 거요");
		setCursorPosition(40, 12);
		printf("그대는 우리를 죽이려 하는 저 무지렁이와는 다르길 바라오");
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
		setCursorPosition(40, 11);
		if (currentNPC->hasQuest == false)
			printf("지금은 딱히 시킬만한 일은 없는 것 같소.");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 알겠소\n");
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
		setCursorPosition(40, 11);
		printf("관군이 빨리 와서 우리 좀 지켜줬으면 하는데,");
		setCursorPosition(40, 12);
		printf("아직도 안온거 보면, 소식이 조정까지 전해지지 못했나보오.");
		setCursorPosition(40, 13);
		printf("대화문\n");
		setCursorPosition(40, 14);
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
				int choice = _getch();
				if (choice == 'a')
				{
					clearScreen();
					setCursorPosition(40, 11);
					printf("퀘스트를 수락하셨습니다!");
					updateLog("퀘스트를 수락하셨습니다!");
					quest[0].take = 1;
					backToDialogue();
					break;
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
}