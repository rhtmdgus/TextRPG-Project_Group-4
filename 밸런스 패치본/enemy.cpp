#include "enemy.h"
#include "player.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

Enemy enemyTemplates[10] = {
    {"�ֱ� ����", 12, 8, 8, {0, 0}, warrior},
    {"�ֱ� â��", 15, 10, 6, {0, 0}, spear},
    {"�ֱ� �ú�", 10, 12, 4, {0, 0}, archor},
    {"�ֱ� ���", 25, 18, 12, {0, 0}, warrior},
    {"�Ǻ� �屺", 20, 20, 10, {0, 0}, warrior},
    {"���� �屺", 22, 16, 14, {0, 0}, warrior},
    {"�ֱ� ���� ���", 40, 25, 20, {0, 0}, warrior},
    {"�Ǻ� ���� �屺", 32, 28, 22, {0, 0}, warrior},
    {"���� ���� �屺", 36, 30, 18, {0, 0}, warrior},
    {"�ֱ� ����", 80, 40, 25, {0, 0}, spear}
};

Enemy currentEnemies[MAX_ENEMY];  // �迭 ����
Enemy* currentEnemy = NULL;       // ������ ����
Enemy currentBosses[MAX_BOSS];
Enemy* currentBoss = NULL;

Enemy createEnemy(const Enemy* enemyTemplate, Position pos) {
    Enemy enemy;
    strcpy_s(enemy.name, sizeof(enemy.name), enemyTemplate->name);
    enemy.hp = enemyTemplate->hp;
    enemy.attack = enemyTemplate->attack;
    enemy.defense = enemyTemplate->defense;
    enemy.pos = pos;
    enemy.type = enemyTemplate->type;
    return enemy;
}

Enemy createBoss(const Enemy* enemyTemplate, Position pos) {
    Enemy boss;
    strcpy_s(boss.name, sizeof(boss.name), enemyTemplate->name);
    boss.hp = enemyTemplate->hp;
    boss.attack = enemyTemplate->attack;
    boss.defense = enemyTemplate->defense;
    boss.pos = pos;
    boss.type = enemyTemplate->type;
    return boss;
}

int isPositionOccupied(int x, int y) {
    for (int i = 0; i < MAX_ENEMY; i++) {
        if (currentEnemies[i].pos.x == x && currentEnemies[i].pos.y == y) 
        {
            return 1;  // ��ġ�� �̹� ��� ����
        }
    }
    if (player.currentmap == 0 && x >= 1 &&x <= 34 && y >= 1 && y <= 15)
    {
        return 1;
    }
    if (map[y][x] == '#' || map[y][x] == 1 || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'T' || map[y][x] == 'F' || map[y][x] == 'O' || map[y][x] == 'R' || map[y][x] == 'B' || map[y][x] == '?')     //���� ��ġ�� ��/npc�� ��� ��ġ ��� ������
    {
        return 1;
    }

    return 0;  // ��ġ�� ������ ����
}

void spawnEnemies() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_ENEMY; i++) {
        int enemyIndex = rand() % 3;

        Position pos;
        do {
            pos.x = rand() % (MAP_WIDTH - 2);
            pos.y = rand() % (MAP_HEIGHT - 2);
        } while (isPositionOccupied(pos.x, pos.y));

        currentEnemies[i] = createEnemy(&enemyTemplates[enemyIndex], pos);
        drawEnemy(&currentEnemies[i]);
        map[currentEnemies[i].pos.y][currentEnemies[i].pos.x] = 'E';
    }
}


void spawnBoss1() {

    Position pos;
    pos.x = MAP_WIDTH - 10;
    pos.y = 2;

    currentBosses[0] = createBoss(&enemyTemplates[3], pos);
    drawBoss(&currentBosses[0]);
    map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';

}

void spawnBoss2() {

    Position pos;
    pos.x = 60;
    pos.y = 24;
    if (player.JRelationship < 0)
    {
        currentBosses[0] = createBoss(&enemyTemplates[8], pos);
        drawBoss(&currentBosses[0]);
        map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';
    }
    else if (player.WRelationship < 0)
    {
        currentBosses[0] = createBoss(&enemyTemplates[7], pos);
        drawBoss(&currentBosses[0]);
        map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';
    }
    else
    {
        currentBosses[0] = createBoss(&enemyTemplates[6], pos);
        drawBoss(&currentBosses[0]);
        map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';
    }
}

void spawnBoss3() {

    Position pos;
    pos.x = (MAP_WIDTH - 10) / 2;
    pos.y = MAP_HEIGHT - 3;
    currentBosses[0] = createBoss(&enemyTemplates[9], pos);
    drawBoss(&currentBosses[0]);
    map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';
}

/*
void spawnBoss() {

    Position pos;
    pos.x = MAP_WIDTH - 10;
    pos.y = 2;
    if (player.JRelationship < 0)
    {
        currentBosses[0] = createBoss(&enemyTemplates[5], pos);
        drawBoss(&currentBosses[0]);
        map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';
    }
    else if (player.WRelationship < 0)
    {
        currentBosses[0] = createBoss(&enemyTemplates[4], pos);
        drawBoss(&currentBosses[0]);
        map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';
    }
    else
    {
        currentBosses[0] = createBoss(&enemyTemplates[3], pos);
        drawBoss(&currentBosses[0]);
        map[currentBosses[0].pos.y][currentBosses[0].pos.x] = 'B';
    }
} */

void drawEnemy(Enemy* enemy) {
    setCursorPosition(enemy->pos.x, enemy->pos.y);
    setColor(4);
    printf("E");
    setColor(7);
}

void eraseEnemy(Enemy* enemy) {
    setCursorPosition(enemy->pos.x, enemy->pos.y);
    printf(" ");
}

void drawBoss(Enemy* boss) {
    setCursorPosition(boss->pos.x, boss->pos.y);
    setColor(6);
    printf("B");
    setColor(7);
}

void eraseBoss(Enemy* boss) {
    setCursorPosition(boss->pos.x, boss->pos.y);
    printf(" ");
}

void eraseAllEnemies() {
    for (int i = 0; i < MAX_ENEMY; i++) {
        eraseEnemy(&currentEnemies[i]); // �� ���� ��ġ�� ����ϴ�.
    }
}