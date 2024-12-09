#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"
#include "utility.h"
#include "questmanager.h"
#include "item.h"

Quest quest[MAX_QUEST];
PrologueQuest prologuequest; //프롤로그 퀘스트
QuestItemData QuestItemList[MAX_QUESTITEM];
QuestItemData* currentQuestItem = NULL;
int checkboss1 = 0;
int checkboss2 = 0;
int checkboss3 = 0;

void initializeQuest()
{
	quest[0] = { "한푼 줍쇼",
	"사람 살리는 셈 치고 한푼만 주시게",
	0, 0, "너무하구만", "자네도 돈이 없는건가?", "정말 고맙네! 이 은혜는 죽을때까지 잊지 않겠네" , 0, 1 };
	quest[1] = { "식량을 확보하라",
	"식량이 부족한데 식량을 구해다줄수 있겠나?",
	0, 0, "의병이 잘 싸워야 전쟁에서 이기는 법인데..","아직 식량을 구해오지 않았나?", "고맙군! 반드시 승리하고 오겠네" , 0, 1 };
	quest[2] = { "왜군을 죽여라",
	"현재 전황이 불리하다. 왜구 5명을 죽이게.",
	0, 0, "우리나라를 배신할 셈인가?", "아직 5명을 죽이지 못했나?", "자네 덕분에 전쟁에서 유리해졌다네." , 1, 5 };
	quest[3] = { "관군의 작전 서류를 훔쳐라",
	"보상은 짭짤하게 줄테니 조선놈들의 작전 서류를 훔쳐와!",
	0, 0, "너도 결국은 조선놈이로군!", "아직 작전서를 훔치지 못했나?", "고마워! 역시 애국보다는 돈이지! 킬킬킬" , 0, 1 };
	quest[4] = { "노동을 도와주게",
	"지금 바위가 길을 막았는데 도와줄수 있겠나?",
	0, 0, "같은 조선인끼리 돕고 살아야지..", "아직 바위를 치우지 못했나?", "고맙군! 다음에도 일이 생기면 부탁할게" , 0, 1 };
	quest[5] = { "부상당한 의병",
	"거기 누구 있나? 다쳐서 움직일수가 없는데 좀 도와주게",
	0, 0, "(의병이 사망하였다)", " ", "덕분에 살았다네, 의병증을 줄테니 대장님한테 가보지 않겠나 ? " , 0, 1 };
	quest[6] = { "관군 장군과의 만남",
	"거기 자네, 왜구 간부와 싸우고 있는데 좀 도와줄수 있겠나?",
	0, 0, "싸움은 못하나 보군.. 알겠네", "할 일이 있는가?", "고맙군! 자네 덕에 승리할수 있었어, 자네 공은 꼭 전하지" , 0, 1 };
	quest[7] = { "왜구 간부와의 만남",
	"이봐 자네! 날 풀어주면 돈을 주도록 하지",
	0, 0, "후회하게 될거야", "뭘 꾸물거리는 거야?", "탁월한 선택이네" , 0, 1 };
	quest[8] = { "식수 부족",
	"거기 자네 혹시 물 하나 있으면 좀 줄수 있겠나?",
	0, 0, "목이 너무 마른데..아쉽군", "아직 물이 없는가?", "고맙네, 이제 다시 일하러 가야겠군" , 0, 1 }; // 평민
	quest[9] = { "벼 수확",
	"벼를 수확하려는데 일손이 부족해, 좀 도와줄수 있겠나?",
	0, 0, "도와주면 좀 나눠줄테니 부탁하네", "조금 더 쉬었다 할 생각인가?", "이걸로 이번주는 어찌 버틸수 있겠어, 여기 좀 나눠주지" , 0, 1 }; // 평민
	quest[10] = { "왜군 처리",
	"많은 수의 왜군을 죽였는데 계속 증원되고 있어, 좀 도와주게",
	0, 0, "좀 도와주게, 전쟁을 빨리 끝내야 하지 않겠나?", "아직 할 일이 있는가?", "이로서 한숨 돌리곘어.. 고맙네" , 1, 5 }; // 의병
	quest[11] = { "왜군 식량창고 제거",
	"왜군의 식량창고 위치 첩보가 들어왔네, 불을 질러서 없애버리세",
	0, 0, "식량창고를 제거해야 숨이 트인다네", "아직 완료하지 못했나?", "이로서 놈들의 사기가 꺾였을 걸세, 고맙다네" , 0, 1 };// 의병
	quest[12] = { "장군 처리",
	"앞에 우리를 가로막는 놈이 있다네, 좀 도와주게",
	0, 0, "놈을 처리하지 않고서는 지나갈 수 없어", "아직 처리하지 못했나?", "드디어 길이 열렸군, 갑세" , 0, 1 };// 의병
	quest[13] = { "왜군 처리",
	"왜군 본토에서 계속 지원이 오고있네, 자네도 돕게나",
	0, 0, "조정의 명을 거역할 셈인가?", "아직 완료하지 못했나?", "좋다, 자네덕에 우리가 우세하게 될걸세" , 1, 5 };// 관군
	quest[14] = { "물자 보급",
	"전쟁이 길어저서 물자가 부족해, 후방에서 보급 받아 오게나",
	0, 0, "보급받지 않으면 전쟁을 이어갈수 없어!", "아직 가져오지 못했나?", "좋아, 계속 싸울수 있겠어" , 0, 1 };// 관군
	quest[15] = { "강적 처리",
	"앞에 가로막는 저놈은 누구지? 같이 처리하세",
	0, 0, "처리하지 않으면 더이상 싸울수 없어!", "아직 처리하지 못했나?", "좋아, 계속 나아가세" , 0, 1 };// 관군
	quest[16] = { "물 거래",
	"식수좀 가지고 있나? 주면 돈을 주지",
	0, 0, "싫음 말게", "아직 가져오지 못했나?", "시원하군, 여기 약속한 돈이다." , 0, 1 };// 왜군
	quest[17] = { "수탈한 물품 수송",
	"조선 백성들 수탈해서 벌어온 물품이 너무 많아서 못 들고왔네, 좀 들고와줘",
	0, 0, "너무 나쁘게만 생각하지 말게, 좀 때주지", "아직 안 들고왔나?", "짭잘하구먼, 여기 좀 주겠네" , 0, 1 };// 왜군
	quest[18] = { "장군 처리",
	"우릴 도왔던 조선인이구만? 저놈 처리좀 도와주게",
	0, 0, "도와주면 우리쪽 자리 알아봐주지", "아직 처리하지 못했나?", "자네는 이제 왜군장군이 될거야" , 0, 1 };// 왜군
	quest[18] = { "원수와의 만남",
	"드디어 그놈이 내 눈앞에 있다. 빠르게 처리하자.",
	0, 0, " ", " ", "놈을 죽였다." , 0, 1 };// 최종 퀘스트(조정중)
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
	QuestItemList[0] = { "군량", 0, 1, {2, 18}, VolunArmyQ };
	QuestItemList[1] = { "작전 서류", 0, 1, {19, 27} , JapArmyQ };
	QuestItemList[2] = { "바위", 0, 1, {34, 14} , NobodyQ };
	QuestItemList[3] = { "왜군 식량 창고", 1, 0, {51, 23}, VolunArmyQ };
	QuestItemList[4] = { "수탈한 물품", 1, 0, {5, 2} , JapArmyQ };
	QuestItemList[5] = { "군수 물자", 1, 0, {3, 13} , GoverArmyQ };
	QuestItemList[6] = { "벼", 1, 1, {1, 9} , NobodyQ };
}

void ActiveQuestItem()
{

	if (player.JRelationship >= player.WRelationship && player.JRelationship >= player.RRelationship)
		QuestItemList[5].isActive = 1;
	else if (player.RRelationship >= player.WRelationship && player.RRelationship >= player.JRelationship)
		QuestItemList[3].isActive = 1;
	else if (player.WRelationship >= player.RRelationship && player.WRelationship >= player.JRelationship)
		QuestItemList[4].isActive = 1;
	else
		return;
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
		if (num == '1')
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
			completeQuest(0);
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
		if (num == '1')
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
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(2);
			equipmentchange(2);
			completeQuest(1);
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
		if (num == '1')
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
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(2);
			equipmentchange(2);
			completeQuest(2);
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
		if (num == '1')
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
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(3);
			equipmentchange(3);
			completeQuest(3);
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
		if (num == '1')
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
			completeQuest(4);
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
	if (checkboss1 == 1)
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
		if (num == '1')
		{
			quest[6].clear = 1;
			player.questitem1 = 0;
			player.JRelationship += 20;
			player.questmax--;
			npcList[7].isActive = 1;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[6].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 과찬이오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(3);
			equipmentchange(3);
			completeQuest(6);
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
	if (quest[7].clear == 0)
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
		if (num == '1')
		{
			quest[7].clear = 1;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.RRelationship -= 10;
			player.money += 20;
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
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(7);
			npcList[7].isActive = 0;
			Sleep(200);
			displayLog();
			backToMap();
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
void QuestComplete8() {
	if (player.MPpotion >= 1)
	{
		setCursorPosition(40, 11);
		printf("마나 포션 한개를 줄까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 준다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[8].clear = 1;
			player.MPpotion--;
			player.RRelationship += 10;
			player.JRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[8].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[8].description3);
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
		printf("마나 포션이 없어서 완료할 수 없다.");
		setCursorPosition(40, 12);
		printf("상점에서 구매하고 오자.");
		backToDialogue();
	}
}
void QuestComplete9() {
	if (player.questitem1 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[9].clear = 1;
			player.questitem1 = 0;
			player.RRelationship += 10;
			player.JRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[9].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			completeQuest(9);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[9].description3);
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
		printf("아직 쌀을 수확하지 못했다.");
		setCursorPosition(40, 12);
		printf("쌀을 수확하고 오자.");
		backToDialogue();
	}
}
void QuestComplete10() {
	if (player.killcount >= 5)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[10].clear = 1;
			player.killcount = 0;
			player.RRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[10].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(10);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[10].description3);
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
		printf("아직 충분한 수의 적을 죽이지 못했다.");
		setCursorPosition(40, 12);
		printf("적을 죽이고 다시 오자.");
		backToDialogue();
	}
}
void QuestComplete11() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[11].clear = 1;
			player.questitem2 = 0;
			player.RRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[11].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(11);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[11].description3);
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
		printf("아직 식량창고를 태우지 못했다.");
		setCursorPosition(40, 12);
		printf("식량창고를 태우고 오자.");
		backToDialogue();
	}
}
void QuestComplete12() {
	if (checkboss2 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[12].clear = 1;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			player.RRelationship += 50;
			player.money += 30;
			player.questmax--;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[12].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 갑시다\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(5);
			equipmentchange(5);
			completeQuest(12);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[12].description3);
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
		printf("아직 보스를 처치하지 못했다.");
		setCursorPosition(40, 12);
		printf("보스를 처치하고 오자.");
		backToDialogue();
	}
}

void QuestComplete13() {
	if (player.killcount >= 5)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[13].clear = 1;
			player.killcount = 0;
			player.JRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[13].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(13);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[13].description3);
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
		printf("아직 충분한 수의 적을 죽이지 못했다.");
		setCursorPosition(40, 12);
		printf("적을 죽이고 다시 오자.");
		backToDialogue();
	}
}

void QuestComplete14() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[14].clear = 1;
			player.questitem2 = 0;
			player.JRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[14].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(14);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[14].description3);
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
		printf("아직 물자를 가져오지 못했다.");
		setCursorPosition(40, 12);
		printf("물자를 가지고 오자.");
		backToDialogue();
	}
}

void QuestComplete15() {
	if (checkboss2 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[15].clear = 1;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			player.JRelationship += 50;
			player.money += 30;
			player.questmax--;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[15].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 갑시다\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(5);
			equipmentchange(5);
			completeQuest(15);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[15].description3);
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
		printf("아직 보스를 처치하지 못했다.");
		setCursorPosition(40, 12);
		printf("보스를 처치하고 오자.");
		backToDialogue();
	}
}

void QuestComplete16() {
	if (player.MPpotion >= 1)
	{
		setCursorPosition(40, 11);
		printf("마나 포션 한개를 줄까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 준다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[16].clear = 1;
			player.MPpotion--;
			player.WRelationship += 30;
			player.RRelationship -= 30;
			player.JRelationship -= 30;
			player.money += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[16].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(5);
			equipmentchange(5);
			completeQuest(16);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[16].description3);
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
		printf("마나 포션이 없어서 완료할 수 없다.");
		setCursorPosition(40, 12);
		printf("상점에서 구매하고 오자.");
		backToDialogue();
	}
}

void QuestComplete17() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[17].clear = 1;
			player.questitem2 = 0;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.RRelationship -= 30;
			player.money += 50;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[17].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 잘 지내시오\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(6);
			equipmentchange(6);
			completeQuest(17);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[17].description3);
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
		printf("아직 수탈한 물품을 가지고 오지 못했다");
		setCursorPosition(40, 12);
		printf("수탈한 물품을 가지고 오자.");
		backToDialogue();
	}
}

void QuestComplete18() {
	if (checkboss2 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[18].clear = 1;
			checkboss2 = 0;
			player.WRelationship += 50;
			player.JRelationship -= 30;
			player.RRelationship -= 30;
			player.money += 100;
			player.questmax--;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[18].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 갑시다\n");
			updateLog("퀘스트를 클리어 했습니다!");
			updateLog("무기를 획득하였습니다!");
			updateLog("장비를 획득하였습니다!");
			weaponchange(7);
			equipmentchange(7);
			completeQuest(18);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[18].description3);
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
		printf("아직 보스를 처치하지 못했다.");
		setCursorPosition(40, 12);
		printf("보스를 처치하고 오자.");
		backToDialogue();
	}
}

void QuestComplete19() {
	if (checkboss3 == 1)
	{
		setCursorPosition(40, 11);
		printf("퀘스트를 완료할까?");
		setCursorPosition(40, 12);
		printf("대화문\n");
		setCursorPosition(40, 13);
		printf("1. 완료한다\n");
		setCursorPosition(40, 14);
		printf("2. 나중에 하자\n");
		int num = _getch();
		if (num == '1')
		{
			quest[19].clear = 1;
			checkboss2 = 0;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[19].description4);
			setCursorPosition(40, 12);
			printf("대화문\n");
			setCursorPosition(40, 13);
			printf("1. 엔딩으로\n");
			completeQuest(19);
			backToDialogue();
		}
		else
		{
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("아직 놈을 처치하지 못했다.");
		setCursorPosition(40, 12);
		printf("놈을 처치하고 오자.");
		backToDialogue();
	}
}