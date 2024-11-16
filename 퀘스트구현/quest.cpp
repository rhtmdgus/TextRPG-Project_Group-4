#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"
#include "utility.h"

Quest quest[MAX_QUEST];

void initializeQuest()
{
	quest[0] = { "한푼 줍쇼",
	"사람 살리는 셈 치고 한푼만 주시게",
	0, 0, "너무하구만", "자네도 돈이 없는건가?", "정말 고맙네! 이 은혜는 죽을때까지 잊지 않겠네"};
	quest[1] = { "식량을 확보하라", 
	"식량이 부족한데 식량을 구해다줄수 있겠나?",
	0, 0, "의병이 잘 싸워야 전쟁에서 이기는 법인데..","아직 식량을 구해오지 않았나?", "고맙군! 반드시 승리하고 오겠네"};
	quest[2] = { "왜군을 죽여라",
	"현재 전황이 불리하다. 왜구 5명을 죽이게.",
	0, 0, "우리나라를 배신할 셈인가?", "아직 5명을 죽이지 못했나?", "자네 덕분에 전쟁에서 유리해졌다네."};
	quest[3] = { "관군의 작전 서류를 훔쳐라",
	"보상은 짭짤하게 줄테니 조선놈들의 작전 서류를 훔쳐와!",
	0, 0, "너도 결국은 조선놈이로군!", "아직 작전서를 훔치지 못했나?", "고마워! 역시 애국보다는 돈이지! 킬킬킬"};
	quest[4] = { "노동을 도와주게",
	"지금 바위가 길을 막았는데 도와줄수 있겠나?",
	0, 0, "같은 조선인끼리 돕고 살아야지..", "아직 바위를 치우지 못했나?", "고맙군! 다음에도 일이 생기면 부탁할게"};
}


void drawQuestItem1() {
	setCursorPosition(questitem1.pos.x, questitem1.pos.y);
	printf("F");
	setColor(3);
}

void drawQuestItem2() {
	setCursorPosition(questitem2.pos.x, questitem2.pos.y);
	printf("O");
	setColor(4);;
}

void drawQuestItem3() {
	setCursorPosition(questitem3.pos.x, questitem3.pos.y);
	printf("R");
	setColor(7);
}

void eraseQuestItem1() {
	setCursorPosition(questitem1.pos.x, questitem1.pos.y);
	printf(" ");
}

void eraseQuestItem2() {
	setCursorPosition(questitem2.pos.x, questitem2.pos.y);
	printf(" ");
}

void eraseQuestItem3() {
	setCursorPosition(questitem3.pos.x, questitem3.pos.y);
	printf(" ");
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
			player.questitem1 == 0;
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
			player.questitem2 == 1;
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
