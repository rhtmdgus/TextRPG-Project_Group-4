#include "item.h"
#include "log.h"
#pragma warning(disable:4996)
#include <string.h>



weapon weapons[5][10] =
{
    {
        {"�콼 ȣ��", 0, 0, 0 }

    },
    {
        {"���", 1, 0, 1}, {"�ξ�Į", 2, 0, 2}, {"���� �ֱ� īŸ��", 3, 0, 3}, {"�ֱ� īŸ��", 4, 0, 4}, { "���� ���", 5, 0, 5}, {"���� ȯ��", 6, 0, 6}
        , {"������", 7, 0, 7}, {"��ȣ��", 9, 0, 8}, {"ȭ��Ű�", 12, 0, 9}
    },
    {
        {"����", 1, 0, 1}, {"������ Ȱ", 2, 0, 2}, {"���� �ֱ� Ȱ", 3, 0, 3}, {"�ֱ� Ȱ", 4, 0, 4},{"���� Ȱ", 5, 0, 5}, {"����", 6, 0, 6}
        ,{"����", 7, 0, 7}, {"���۱�", 9, 0, 8}, {"�Ͽ��ű�", 12, 0, 9}
    },
    {
        {"��â", 1, 0, 1}, {"������ â", 2, 0, 2}, {"���� �ֱ� â", 3, 0, 3}, {"�ֱ� â", 4, 0, 4}, {"���� â", 5, 0, 5}, {"����â", 6, 0, 6}
        ,{ "��õȭ��", 7, 0, 7 }, {"û������", 9, 0, 8}, {"��õ��â", 12, 0, 9}
    },
    {
        {"�ź��� ���", 1, 1, 1}, {"����Ѳ�", 1, 2, 2}, {"���� �ֱ� ����", 1, 3, 3}, {"�ֱ� ����", 2, 4, 4},{"���� ����", 3, 4, 5}, {"�ձ� ����", 4, 4, 6}
        , { "��ö����", 4, 5, 7 }, {"���� ����", 6, 5, 8}, {"�Ҹ����", 8, 8, 9}
    }
};


equipment equipments[10] = {
        {"�ﺣ ��", 0, 1, 1}, { "õ ����", 0, 2, 2 }, {"���� ����", 0, 3, 3}, {"�ֱ� ����", 0, 4, 4}, {"���� ����", 0, 5, 5}, {"������", 0, 6, 6}
        , {"���", 0, 7, 7}, {"�ϵ�ĥ��", 0, 8, 8}, {"�븰����", 0, 9, 9}
};





void weaponchange(int i) 
{
    if (player.currentweapon < weapons[player.job][i].weaponTier) 
    {
        player.attack = player.attack - weapons[player.job][player.currentweapon].attackpoint;
        player.defense = player.defense - weapons[player.job][player.currentweapon].defensepoint;

        player.currentweapon = weapons[player.job][i].weaponTier;

        player.attack = player.attack + weapons[player.job][player.currentweapon].attackpoint;
        player.defense = player.defense + weapons[player.job][player.currentweapon].defensepoint;

        strncpy(player.currentweaponName, weapons[player.job][i].name, sizeof(player.currentweaponName) - 1);
        player.currentweaponName[sizeof(player.currentweaponName) - 1] = '\0'; // null-termination ����

        updateLog("������񺸴� Ƽ� ���� ����̹Ƿ� ��� ��ü�մϴ�!");
    }
    else if (player.currentweapon == weapons[player.job][i].weaponTier) 
    {
        updateLog("�������� ���� ����̹Ƿ� ��� ��ü���� �ʽ��ϴ�!");
    } 
    else {
        updateLog("������񺸴� Ƽ� ���� ����̹Ƿ� ��� ��ü���� �ʽ��ϴ�!");
    }
        
        
    
}

void equipmentchange(int i)
{


    if (player.currentequipment < equipments[i].equipmentTier)
    {
        player.attack = player.attack - equipments[player.currentequipment].attackpoint;
        player.defense = player.defense - equipments[player.currentequipment].defensepoint;

        player.currentequipment = equipments[i].equipmentTier;

        player.attack = player.attack + equipments[player.currentequipment].attackpoint;
        player.defense = player.defense + equipments[player.currentequipment].defensepoint;

        strncpy(player.currentequipmentName, equipments[i].name, sizeof(player.currentequipmentName) - 1);
        player.currentequipmentName[sizeof(player.currentequipmentName) - 1] = '\0'; // null-termination ����
        
        updateLog("������񺸴� Ƽ� ���� ����̹Ƿ� ��� ��ü�մϴ�!");
    }
    else if (player.currentequipment == equipments[i].equipmentTier)
    {
        updateLog("�������� ���� ����̹Ƿ� ��� ��ü���� �ʽ��ϴ�!");
    }
    else {
        updateLog("������񺸴� Ƽ� ���� ����̹Ƿ� ��� ��ü���� �ʽ��ϴ�!");
    }

    
}
