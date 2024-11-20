#ifndef CURRENTQUEST_H
#define CURRENTQUEST_H

#include "quest.h"
#include "player.h"
#include "npc.h"
#include "utility.h"

typedef struct {
    char title[100];
    char description[200];
    int progress;
} CurrentQuest;

extern CurrentQuest questlist[3];

void displayquest();
int updatequestlist(const char* questTitle, const char* questDescription, int progress);

#endif // CURRENTQUEST_H
