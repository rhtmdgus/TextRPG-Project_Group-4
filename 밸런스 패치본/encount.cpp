#include <conio.h>
#include "encount.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include "npc.h"
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
        updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
        Sleep(200);
        displayLog();
        updateLog("[A]Ű�� ���� �������� [R]Ű�� ���� ����ĥ�� �����Ͻʽÿ�.");
        Sleep(200);
        displayLog();
        break;
    case 'A':
    case 'a':
        updateLog("������ ������ ���۵˴ϴ�!");
        Sleep(200);
        displayLog();
        displayBattleScreen();
        battle(currentEnemy);  // currentEnemy ����
        break;
    case 'R':
    case 'r':
        updateLog("�����Լ� �����ƽ��ϴ�!");
        Sleep(200);
        displayLog();
        updateLog("������ ������ϴ�!");
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
        updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
        Sleep(200);
        displayLog();
        updateLog("[A]Ű�� ���� �������� [R]Ű�� ���� ����ĥ�� �����Ͻʽÿ�.");
        Sleep(200);
        displayLog();
        break;
    case 'A':
    case 'a':
        updateLog("�� ������� ������ ���۵˴ϴ�!");
        Sleep(200);
        displayLog();
        displayBossBattleScreen();
        bossbattle(currentBoss);  // currentBoss ����
        break;
    case 'R':
    case 'r':
        updateLog("�� ������Լ� �����ƽ��ϴ�!");
        Sleep(200);
        displayLog();
        updateLog("�������� ������ϴ�!");
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
        updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
        updateLog("[A]Ű�� ���� ������ ���� [R]Ű�� ���� ������ �����Ͻʽÿ�.");
        break;
    case 'A':
    case 'a':
        Sleep(100);
        updateLog("������ ���Խ��ϴ�!");
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
        updateLog("������ �������ϴ�.");
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
        updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
        updateLog("[A]Ű�� ���� ��ȭ���� [R]Ű�� ���� ������ �����Ͻʽÿ�.");
        break;
    case 'A':
    case 'a':
        Sleep(100);
        updateLog("NPC�� ��ȭ�� �����մϴ�.");
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
        updateLog("NPC���� ��ȭ�� �����մϴ�.");
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
        updateLog("�߸��� Ű�� �Է��Ͽ����ϴ�.");
        updateLog("[A]Ű�� ���� ������ ������ [R]Ű�� ���� �ӹ��� �����Ͻʽÿ�.");
        break;
    case 'A':
    case 'a':
        Sleep(100);
        updateLog("���� ������ �����ϴ�!");
        initializeMap();
        player.pos.x = 1;
        player.pos.y = 1;
        ActiveNpc();
        ActiveQuestItem();
        gotoNextMap();
        initializeMap();
        displayMap();
        eraseAllEnemies();
        if(player.currentmap != 2)
            spawnEnemies();
        displayMap();
        Situation = 0;
        break;

    case 'R':
    case 'r':
        updateLog("���� ������ �ӹ���� �����Ͽ����ϴ�.");
        Situation = 0;
        player.pos = previousPos;
        break;
    }
    displayLog();
}

/**
int encountRandom()
{
    if (player.pos.y == Random.pos.y && player.pos.x == Random.pos.x)
    {
        Situation = 10;
        return 10;
    }
    else
    {
        Situation = 0;
        return 0;
    }
}
*/

/**
void encountRandomChoice()
{

}
*/


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
