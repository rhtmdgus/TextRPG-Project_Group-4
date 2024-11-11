#include "encount.h"
#include "enemy.h"
#include "log.h"
#include "initmap.h"
#include "displaymap.h"
#include "player.h"
#include "battle.h"
#include <conio.h>

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
        Sleep(100);
        displayLog();
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
        player.pos.x -= 1;
        break;
    }
    Sleep(100);
    displayLog();
}
