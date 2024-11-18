#include "enemy.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

Enemy enemyTemplates[3] = {
    {"�ֱ� ����", 10, 8, 3, {0, 0}, warrior},
    {"�ֱ� â��", 12, 10, 4, {0, 0}, spear},
    {"�ֱ� �ú�", 8, 6, 2, {0, 0}, archor}
};

Enemy currentEnemies[MAX_ENEMY];  // �迭 ����
Enemy* currentEnemy = NULL;       // ������ ����

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

int isPositionOccupied(int x, int y) {
    for (int i = 0; i < MAX_ENEMY; i++) {
        if (currentEnemies[i].pos.x == x && currentEnemies[i].pos.y == y) 
        {
            return 1;  // ��ġ�� �̹� ��� ����
        }
    }
    if (map[y][x] == '#' || map[y][x] == 1)
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

void drawEnemy(Enemy* enemy) {
    setCursorPosition(enemy->pos.x, enemy->pos.y);
    printf("E");
}

void eraseEnemy(Enemy* enemy) {
    setCursorPosition(enemy->pos.x, enemy->pos.y);
    printf(" ");
}
