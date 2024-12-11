#ifndef RANDEVENT_H
#define RANDEVENT_H

#include "utility.h"

#define MAX_EVENT 5
typedef struct
{
	char name[50];
	Position pos;
	int check;
} RandEvent;

extern RandEvent RandomEvent[3];
extern RandEvent currentEvents[MAX_EVENT];
extern RandEvent* currentEvent;

RandEvent createEvent(const RandEvent* RandomEvent, Position pos);

int isPositionEOccupied(int x, int y);
void spawnEvents();
void drawEvent(RandEvent* Event);
void eraseEvent(RandEvent* Event);
void eraseAllEvents();

#endif // RANDEVENT_H
