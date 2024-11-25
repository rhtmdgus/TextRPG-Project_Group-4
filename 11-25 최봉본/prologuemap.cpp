#include "prologuemap.h"
#include "log.h"
#include "utility.h"
#include <stdio.h>

void p_map0()
{
    // 플레이어가 못 지나가는 벽 (공터 주변)
    for (int i = 10; i < 15; i++) {
        map[i][10] = '#'; // 왼쪽 벽
        map[i][30] = '#'; // 오른쪽 벽
    }
    for (int j = 10; j <= 30; j++) {
        
        map[10][j] = '#'; // 위쪽 벽  
        if (j >= 18 && j <= 22)
            continue;
        else
            map[15][j] = '#'; // 아래쪽 벽
    }
    for (int i = 15; i <= 29; i++) {
        map[i][17] = '#'; // 위쪽 벽  
        map[i][23] = '#'; // 아래쪽 벽
    }
}

void p_map1()
{
    for (int i = 30; i < 38; i++) {
        map[17][i] = '#'; // 위쪽 벽
        map[21][i] = '#'; // 아래쪽 벽
    }

    for (int i = 1; i < 29; i++) {
        map[i][10] = '#'; // 왼쪽 벽
        if (i >= 17 && i <= 21)
        {
            map[i][37] = '#'; // 오른쪽 벽
            continue;
        }
        map[i][30] = '#'; // 오른쪽 벽
    }
}
void p_map2()
{
    for (int i = 1; i <= 10; i++) {
        map[i][10] = '#'; // 왼쪽 벽
        map[i][30] = '#'; // 오른쪽 벽
    }
    for (int i = 1; i < 10; i++)
    {
        map[10][i] = '#';
    }
    for (int i = 30; i < 39; i++)
    {
        map[10][i] = '#';
    }

    for (int i = 10; i < 29; i++) {
        map[i][1] = '#'; // 왼쪽 벽
        map[i][39] = '#'; // 오른쪽 벽
    }
}