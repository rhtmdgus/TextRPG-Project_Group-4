#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"

Quest quest[MAX_QUEST];

void initializeQuest()
{
	quest[0] = { "한푼 줍쇼",
	"사람 살리는 셈 치고 한푼만 주시게",
	0, 0, "너무하구만", "자네도 돈이 없는건가?", "정말 고맙네! 이 은혜는 죽을때까지 잊지 않겠네"};
	quest[1] = { "식량을 확보하라", 
	"의병들이 열심히 일하고 있는데 식량이 부족하다네\n 식량을 구해다줄수 있겠나?",
	0, 0, "의병이 잘 싸워야 전쟁에서 이기는 법인데..","아직 식량을 구해오지 않았군.", "고맙군! 반드시 승리하고 오겠네"};
	quest[2] = { "왜군을 죽여라",
	"현재 왜군이 대대적으로 몰려오는 중이라 관군이 불리한 상황이다.\n왜구 5명을 죽이고 돌아와라.",
	0, 0, "우리나라를 배신할 셈인가?", "아직 5명을 죽이지 못했다!", "자네 덕분에 전쟁에서 유리해졌다네."};
	quest[3] = { "관군의 작전서를 훔쳐라",
	"보상은 짭짤하게 줄테니 조선놈들의 작전서를 훔쳐와!",
	0, 0, "너도 결국은 조선놈이로군!", "아직 작전서를 훔치지 못했군!", "고마워! 역시 애국보다는 돈이지! 킬킬킬"};
	quest[4] = { "노동을 도와주게",
	"지금 바위가 길을 막아서 지나다니기가 힘든 상황이네\n 손 좀 빌려줄수 있겠나?",
	0, 0, "같은 조선인끼리 돕고 살아야지..", "아직 바위를 치우지 못했어", "고맙군! 다음에도 일이 생기면 부탁할게"};
}

void QuestComplete1() {
	if (player.money > 1)
	{
		setCursorPosition(40, 11);
		printf("돌쇠에게 1냥을 줄까?");
		int num = _getch();
		if (num == 'a')
		{
			quest[0].clear = 1;
			player.money--;
			player.RRelationship += 10;
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
