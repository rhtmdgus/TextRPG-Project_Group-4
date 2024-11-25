#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"
#include "utility.h"

Quest quest[MAX_QUEST];
PrologueQuest prologuequest; //프롤로그 퀘스트
QuestItemData QuestItemList[MAX_QUESTITEM];
QuestItemData* currentQuestItem = NULL;

void initializeQuest()
{
	quest[0] = { "한푼 줍쇼",
	"사람 살리는 셈 치고 한푼만 주시게",
	0, 0, "너무하구만", "자네도 돈이 없는건가?", "정말 고맙네! 이 은혜는 죽을때까지 잊지 않겠네" , 0, 1};
	quest[1] = { "식량을 확보하라",
	"식량이 부족한데 식량을 구해다줄수 있겠나?",
	0, 0, "의병이 잘 싸워야 전쟁에서 이기는 법인데..","아직 식량을 구해오지 않았나?", "고맙군! 반드시 승리하고 오겠네" , 0, 1};
	quest[2] = { "왜군을 죽여라",
	"현재 전황이 불리하다. 왜구 5명을 죽이게.",
	0, 0, "우리나라를 배신할 셈인가?", "아직 5명을 죽이지 못했나?", "자네 덕분에 전쟁에서 유리해졌다네." , 1, 5};
	quest[3] = { "관군의 작전 서류를 훔쳐라",
	"보상은 짭짤하게 줄테니 조선놈들의 작전 서류를 훔쳐와!",
	0, 0, "너도 결국은 조선놈이로군!", "아직 작전서를 훔치지 못했나?", "고마워! 역시 애국보다는 돈이지! 킬킬킬" , 0, 1};
	quest[4] = { "노동을 도와주게",
	"지금 바위가 길을 막았는데 도와줄수 있겠나?",
	0, 0, "같은 조선인끼리 돕고 살아야지..", "아직 바위를 치우지 못했나?", "고맙군! 다음에도 일이 생기면 부탁할게" , 0, 1};
	quest[5] = { "부상당한 의병",
	"거기 누구 있나? 다쳐서 움직일수가 없는데 좀 도와주게",
	0, 0, "(의병이 사망하였다)", " ", "덕분에 살았다네, 의병증을 줄테니 대장님한테 가보지 않겠나 ? " , 0, 1};
	quest[6] = { "관군 장군과의 만남",
	"거기 자네, 왜구 간부와 싸우고 있는데 좀 도와줄수 있겠나?",
	0, 0, "싸움은 못하나 보군.. 알겠네", "할 일이 있는가?", "고맙군! 자네 덕에 승리할수 있었어, 자네 공은 꼭 전하지" , 0, 1};
	quest[7] = { "왜구 간부와의 만남",
	"이봐 자네! 날 풀어주면 자네의 복수를 도와주겠네",
	0, 0, "후회하게 될거야", "뭘 꾸물거리는 거야?", "탁월한 선택이네" , 0, 1};
}
/*

void initializePrologueQuest()
{
	prologuequest = { "전쟁의 시작",
	"머리가 아프다. 왜구들한테 습격을 받고 기절했었나 보다.",
	"아내다, 왜구한테 당한듯하다", "왜구를 용서할 수 없다. 복수를 하러가자" };
}  */

void initializeQuestItem()
{
	QuestItemList[0] = {"군량", 0, 1, {15, 5}, VolunArmyQ};
	QuestItemList[1] = { "작전 서류", 0, 1, {17, 5} , JapArmyQ};
	QuestItemList[2] = { "바위", 0, 1, {19, 5} , NobodyQ};
}

void drawQuestItem(QuestItemData* QuestItemList)
{
	for (int i = 0; i < MAX_QUESTITEM; i++)
	{
		if (player.currentmap == (QuestItemList + i)->currentmap)
		{
			setCursorPosition((QuestItemList + i)->pos.x, (QuestItemList + i)->pos.y);
			if ((QuestItemList + i)->type == Nobody)
				setColor(7);
			else if ((QuestItemList + i)->type == GoverArmy)
				setColor(2);
			else if ((QuestItemList + i)->type == JapArmy)
				setColor(4);
			else if ((QuestItemList + i)->type == VolunArmy)
				setColor(3);
			if ((QuestItemList + i)->isActive)
				printf("Q");
			setColor(7);
		}
	}
}

void QuestComplete1() {
	if (player.money > 1)
	{
		setCursorPosition(40, 11);
		printf("돌쇠에게 1냥을 줄까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 준다\n");
		setCursorPosition(40, 14);
		printf("2. 좀 더 생각해보자\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[0].clear = 1;
			player.money--;
			player.RRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[0].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[0].description3);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 미안하오\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("돈이 없어서 미션을 클리어할수 없다.");
		setCursorPosition(40, 12);
		printf("돈을 모으고 다시 오도록 하자.");
		backToDialogue();
	}
}


void QuestComplete2() {
	if (player.questitem1 == 1)
	{
		setCursorPosition(40, 11);
		printf("식량을 줄까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 준다\n");
		setCursorPosition(40, 14);
		printf("2. 좀 더 생각해보자\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[1].clear = 1;
			player.questitem1 = 0;
			player.RRelationship += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[1].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 힘내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[1].description3);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 미안하오\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("식량이 없어서 미션을 클리어할수 없다.");
		setCursorPosition(40, 12);
		printf("식량을 수집하고 다시 오도록 하자.");
		backToDialogue();
	}
}


void QuestComplete3() {
	if (player.killcount >= 5)
	{
		setCursorPosition(40, 11);
		printf("관군에게 퀘스트를 완료했다고 말할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 말한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[2].clear = 1;
			player.killcount = 0;
			player.JRelationship += 30;
			player.WRelationship -= 50;
			player.money += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[2].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 승리하길 바라오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[2].description3);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 미안하오\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("아직 충분한 수의 왜군을 죽이지 못했다.");
		setCursorPosition(40, 12);
		printf("왜군을 조금 더 제거하고 오도록 하자.");
		backToDialogue();
	}
}


void QuestComplete4() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("왜군에게 작전서류를 넘길까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 준다\n");
		setCursorPosition(40, 14);
		printf("2. 좀 더 생각해보자\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[3].clear = 1;
			player.questitem2 = 0;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.RRelationship -= 30;
			player.money += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[3].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[3].description3);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 미안하오\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("작전 서류가 없어서 미션을 클리어할수 없다.");
		setCursorPosition(40, 12);
		printf("작전 서류를 훔치고 다시 오도록 하자.");
		backToDialogue();
	}
}


void QuestComplete5() {
	if (player.questitem3 == 1)
	{
		setCursorPosition(40, 11);
		printf("임무를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 완료하자.\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[4].clear = 1;
			player.questitem3 = 0;
			player.RRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[4].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[4].description3);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 미안하오\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("아직 돌을 치우지 않아 미션을 클리어할수 없다.");
		setCursorPosition(40, 12);
		printf("돌을 치우고 다시 오도록 하자.");
		backToDialogue();
	}
}

void QuestComplete6() {
	if (//player.questitem1 == 1
		true)
	{
		setCursorPosition(40, 11);
		printf("임무를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 완료하자.\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[6].clear = 1;
			player.questitem1 = 0;
			player.JRelationship += 20;
			player.questmax--;
			npcList[7].isActive = 1;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[6].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 과찬이오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			Sleep(200);
			displayLog();
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[6].description3);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 미안하오\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("아직 왜구 간부를 잡지 못하였다.");
		setCursorPosition(40, 12);
		printf("왜구 장수를 잡고 다시 오도록 하자.");
		backToDialogue();
	}
}

void QuestComplete7() {
	if (//player.questitem2 == 1
		true)
	{
		setCursorPosition(40, 11);
		printf("왜구 장수를 풀어줄까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 완료하자.\n");
		int num = _getch();
		if (num == 'a')
		{
			quest[7].clear = 1;
			//player.questitem2 = 0;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[7].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 빨리 가시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			Sleep(200);
			displayLog();
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[7].description3);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 기다려보시오\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("아직 왜구 장수를 풀어줄 도구를 챙기지 못했다.");
		setCursorPosition(40, 12);
		printf("도구를 챙기고 다시 오도록 하자.");
		backToDialogue();
	}
}
