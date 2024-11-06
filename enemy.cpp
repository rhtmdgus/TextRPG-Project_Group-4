#include "enemy.h"
#include <stdio.h>
#include <string.h>

Enemy createEnemy(const char* name, int hp, int attack, int defense, Position pos)
{
    Enemy enemy;
    strcpy_s(enemy.name, sizeof(enemy.name), name);
    enemy.hp = hp;
    enemy.attack = attack;
    enemy.defense = defense;
    enemy.pos.x = pos.x;
    enemy.pos.y = pos.y;
    return enemy;
}
void drawEnemy(Enemy* enemy)
{
    setCursorPosition(enemy->pos.x, enemy->pos.y);
    printf("E");
}
void eraseEnemy(Enemy* enemy)
{
    setCursorPosition(enemy->pos.x, enemy->pos.y);
    printf(" ");
}