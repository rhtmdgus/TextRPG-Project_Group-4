#include <conio.h>
#include "encount.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include "npc.h"

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

void encountChoice()
{
    char action = _getch();

    switch (action)
    {
    default:
        updateLog("You choose the wrong key");
        Sleep(100);
        displayLog();
        updateLog("Press [A] to Attack or [R] to Run");
       // Sleep(100);
        //displayLog();
        break;
    case 'A':
    case 'a':
        updateLog("You decided to attack the enemy!");
        Sleep(100);
        displayLog();
        displayBattleScreen();
        battle(currentEnemy);  // currentEnemy РќДо
        break;
    case 'R':
    case 'r':
        updateLog("You ran away from the enemy!");
        Sleep(100);
        displayLog();
        updateLog("You fled from battle!");
        Situation = 0;
        player.pos  = previousPos;
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
        if (player.pos.y == npcList[i].pos.y && player.pos.x == npcList[i].pos.x)
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
    if (player.pos.y == potal[player.currentmap].pos.y && player.pos.x == potal[player.currentmap].pos.x)
    {
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

        gotoNextMap();
        initializeMap();
        displayMap();
        eraseAllEnemies();
        spawnEnemies();
        displayMap();





        break;

    case 'R':
    case 'r':
        updateLog("You decided to stay");

        player.pos = previousPos;
        break;
    }
    displayLog();
}