#include "prologuemap.h"
#include "log.h"
#include "utility.h"
#include <stdio.h>

void p_map0()
{
    // �÷��̾ �� �������� �� (���� �ֺ�)
    for (int i = 10; i < 15; i++) {
        map[i][10] = '#'; // ���� ��
        map[i][30] = '#'; // ������ ��
    }
    for (int j = 10; j <= 30; j++) {
        
        map[10][j] = '#'; // ���� ��  
        if (j >= 18 && j <= 22)
            continue;
        else
            map[15][j] = '#'; // �Ʒ��� ��
    }
    for (int i = 15; i <= 29; i++) {
        map[i][17] = '#'; // ���� ��  
        map[i][23] = '#'; // �Ʒ��� ��
    }
}

void p_map1()
{
    for (int i = 30; i < 38; i++) {
        map[17][i] = '#'; // ���� ��
        map[21][i] = '#'; // �Ʒ��� ��
    }

    for (int i = 1; i < 29; i++) {
        map[i][10] = '#'; // ���� ��
        if (i >= 17 && i <= 21)
        {
            map[i][37] = '#'; // ������ ��
            continue;
        }
        map[i][30] = '#'; // ������ ��
    }
}
void p_map2()
{
    for (int i = 1; i <= 10; i++) {
        map[i][10] = '#'; // ���� ��
        map[i][30] = '#'; // ������ ��
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
        map[i][1] = '#'; // ���� ��
        map[i][39] = '#'; // ������ ��
    }
}