#include "randevent.h"
#include "player.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

RandEvent RandomEvent[3] = {
    {"����", {0, 0}, 1},
    {"ü�� ���� ����", {0, 0}, 1},
    {"��� ��� ����", {0, 0}, 1}
};

RandEvent currentEvents[MAX_EVENT];  // �迭 ����
RandEvent* currentEvent = NULL;       // ������ ����

RandEvent createEvent(const RandEvent* RandomEvent, Position pos)
{
    RandEvent event;
    strcpy_s(event.name, sizeof(event.name), RandomEvent->name);
    event.pos = pos;
    event.check = RandomEvent->check;
    return event;
}

int isPositionEOccupied(int x, int y)
{
    for (int i = 0; i < MAX_EVENT; i++) {
        if (currentEvents[i].pos.x == x && currentEvents[i].pos.y == y)
        {
            return 1;  // ��ġ�� �̹� ��� ����
        }
    }
    if (player.currentmap == 0 && x >= 1 && x <= 34 && y >= 1 && y <= 15)
    {
        return 1;
    }
    if (map[y][x] == '#' || map[y][x] == 1 || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'T' || map[y][x] == 'F' || map[y][x] == 'O' || map[y][x] == 'R' || map[y][x] == 'B' || map[y][x] == 'E')     //���� ��ġ�� ��/npc�� ��� ��ġ ��� ������
    {
        return 1;
    }

    return 0;  // ��ġ�� ������ ����
}


void spawnEvents()
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_EVENT; i++) {
        int eventIndex = rand() % 3;

        Position pos;
        do {
            pos.x = rand() % (MAP_WIDTH - 2);
            pos.y = rand() % (MAP_HEIGHT - 2);
        } while (isPositionEOccupied(pos.x, pos.y));

        currentEvents[i] = createEvent(&RandomEvent[eventIndex], pos);
        drawEvent(&currentEvents[i]);
        map[currentEvents[i].pos.y][currentEvents[i].pos.x] = '?';
    }
}
void drawEvent(RandEvent* Event)
{
    setCursorPosition(Event->pos.x, Event->pos.y);
    setColor(14);
    printf("?");
    setColor(7);
}
void eraseEvent(RandEvent* Event)
{
    map[Event->pos.y][Event->pos.x] = ' ';
}

void eraseAllEvents() {
    for (int i = 0; i < MAX_EVENT; i++) {
        eraseEvent(&currentEvents[i]); // �� ���� ��ġ�� ����ϴ�.
    }
}