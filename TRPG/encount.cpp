#include <conio.h>
#include "encount.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include "npc.h"
#include "randevent.h"
#include "quest.h"

int encountEnemy()
{
    for (int i = 0; i < MAX_ENEMY; i++) {
        if (currentEnemies[i].hp > 0 &&
            currentEnemies[i].pos.x == player.pos.x &&
            currentEnemies[i].pos.y == player.pos.y)
        {
            currentEnemy = &currentEnemies[i];
            Situation = 1;
            return 1;
        }
    }
    Situation = 0;
    currentEnemy = nullptr;
    return 0;
}

int encountBoss()
{
    for (int i = 0; i < MAX_BOSS; i++) {
        if (currentBosses[i].hp > 0 &&
            currentBosses[i].pos.x == player.pos.x &&
            currentBosses[i].pos.y == player.pos.y)
        {
            currentBoss = &currentBosses[i];
            Situation = 7;
            return 7;
        }
    }
    Situation = 0;
    currentBoss = nullptr;
    return 0;
}

void encountChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("You choose the wrong key");
        Sleep(200);
        displayLog();
        updateLog("Press [A] to Attack or [R] to Run");
        Sleep(200);
        displayLog();
        break;
    case 'A':
    case 'a':
        updateLog("You decided to attack the enemy!");
        Sleep(200);
        displayLog();
        displayBattleScreen();
        battle(currentEnemy);  // currentEnemy 전달
        break;
    case 'R':
    case 'r':
        updateLog("You ran away from the enemy!");
        Sleep(200);
        displayLog();
        updateLog("You fled from battle!");
        Sleep(200);
        displayLog();
        Situation = 0;
        player.pos  = previousPos;
        break;
    }
    Sleep(100);
    displayLog();
}

void encountBossChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("You choose the wrong key");
        Sleep(200);
        displayLog();
        updateLog("Press [A] to Attack or [R] to Run");
        Sleep(200);
        displayLog();
        break;
    case 'A':
    case 'a':
        updateLog("You decided to attack the boss!");
        Sleep(200);
        displayLog();
        displayBossBattleScreen();
        bossbattle(currentBoss);  // currentBoss 전달
        break;
    case 'R':
    case 'r':
        updateLog("You ran away from the boss!");
        Sleep(200);
        displayLog();
        updateLog("You fled from battle!");
        Sleep(200);
        displayLog();
        Situation = 0;
        player.pos = previousPos;
        break;
    }
    Sleep(100);
    displayLog();
}



int encountShop()
{
    if (player.pos.y == Shop1.pos.y && player.pos.x == Shop1.pos.x)
    {
        Situation = 2;
        return 2;
    }
    else
    {
        Situation = 0;
        return 0;
    }
}

void encountShopChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("You choose the wrong key");
        updateLog("Press [A] to use Shop or [R] to Leave");
        break;
    case 'A':
    case 'a':
        Sleep(100);
        updateLog("You decided to use Shop!");
        Situation = 3;
        initializeMap();
        displayShopMap();
        while (Situation == 3)
        {
            displayShopScreen();
            
        }
        break;
    case 'R':
    case 'r':
        updateLog("You decided to leave Shop");
        Situation = 0;
        player.pos = previousPos;
        break;
    }
    displayLog();
}

int encountNpc()
{
    for (int i = 0; i < MAX_NPC; i++) {
        if (player.pos.y == npcList[i].pos.y && player.pos.x == npcList[i].pos.x && player.currentmap == npcList[i].currentmap && npcList[i].isActive == 1)
        {
            currentNPC = &npcList[i];
            Situation = 4;
            return 4;
        }
    }
    Situation = 0;
    currentNPC = nullptr;
    return 0;
}

void encountNpcChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("You choose the wrong key");
        updateLog("Press [A] to talk NPC or [R] to Leave");
        break;
    case 'A':
    case 'a':
        Sleep(100);
        updateLog("You decided to talk to NPC");
        Situation = 5;
        initializeMap();
        displayShopMap();
        while (Situation == 5)
        {
            displayNPCScreen();
        }
        break;
    case 'R':
    case 'r':
        updateLog("You decided to leave NPC");
        Situation = 0;
        player.pos = previousPos;
        break;
    }
    displayLog();
}


int encountPotal()
{
    if (player.pos.y == potal[player.currentmap].pos.y && player.pos.x == potal[player.currentmap].pos.x && potal[player.currentmap].spawnPotal == true)
    {
        Situation = 9;
        return 1;

    }
    else
    {
        Situation = 0;
        return 0;
    }
}

void encountPotalChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("You choose the wrong key");
        updateLog("Press [A] to go next map or [R] to stay");
        break;
    case 'A':
    case 'a':
        Sleep(100);
        updateLog("You decided to go next map!");
        initializeMap();
        player.pos.x = 1;
        player.pos.y = 1;
        ActiveNpc();
        ActiveQuestItem();
        gotoNextMap();
        initializeMap();
        displayMap();
        eraseAllEnemies();
        spawnEnemies();
        displayMap();
        Situation = 0;
        break;

    case 'R':
    case 'r':
        updateLog("You decided to stay");
        Situation = 0;
        player.pos = previousPos;
        break;
    }
    displayLog();
}


int encountRandom()
{
    for (int i = 0; i < MAX_EVENT; i++) {
        if (currentEvents[i].check != 1)
            break;
        else if (player.pos.y == currentEvents[i].pos.y && player.pos.x == currentEvents[i].pos.x)
        {
            currentEvent = &currentEvents[i];
            Situation = 10;
            return 1;
        }
    }
    currentEvent = nullptr;
    Situation = 0;
    return 0;
}

void encountRandomChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("잘못된 키를 눌렀습니다.");
        displayLog();
        Sleep(200);
        updateLog("수상한 기운을 조사하려면 [A]를, 아니면 [R]을 누르세요.");
        displayLog();
        Sleep(200);
        break;
    case 'A':
    case 'a':
        updateLog("수상한 기운을 조사하기로 결정했습니다.");
        displayLog();
        Sleep(200);
        
        if (strcmp(currentEvent->name, "닌자") == 0)
        {
            updateLog("닌자를 발견했다!");
            displayLog();
            Sleep(200);
        }
        if (strcmp(currentEvent->name, "체력 약초 상자") == 0)
        {
            updateLog("버려진 상자를 발견했다.");
            displayLog();
            Sleep(200);
        }

        if (strcmp(currentEvent->name, "기력 약수 상자") == 0)
        {
            updateLog("때깔 좋은 상자를 발견했다.");
            displayLog();
            Sleep(200);
        }

        currentEvent->check = 0;
        break;
    case 'R':
    case 'r':
        updateLog("수상한 기운을 조사하지 않기로 결정했습니다.");
        displayLog();
        Sleep(200);
        currentEvent->check = 0;
        eraseEvent(currentEvent);

        // 이전 위치로 돌아가기
        player.pos = previousPos;
        Situation = 0;
        break;
    }
}



int encountQuestItem()
{
    for (int i = 0; i < MAX_QUESTITEM; i++) {
        if (player.pos.y == QuestItemList[i].pos.y && player.pos.x == QuestItemList[i].pos.x && player.currentmap == QuestItemList[i].currentmap && QuestItemList[i].isActive == 1)
        {
            currentQuestItem = &QuestItemList[i];
            Situation = 6;
            return 6;
        }
    }
    Situation = 0;
    currentQuestItem = nullptr;
    return 0;
}
