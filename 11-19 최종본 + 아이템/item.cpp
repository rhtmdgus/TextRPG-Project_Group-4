#include "item.h"
#include "log.h"
#pragma warning(disable:4996)



weapon weapons[5][10] =
{
    {
        {"�콼 ȣ��", 1, 0, 0 }

    },
    {
        {"�ξ�Į", 2, 0, 1}, {"���� ���", 4, 0, 2}, {"���� ȯ��", 5, 0, 3},{"��ȣ��", 7, 0, 4},{"ȭ��Ű�", 10, 0, 5}
    },
    {
        {"����", 2, 0, 1}, {"���� Ȱ", 4, 0, 2}, {"����", 5, 0, 3}, {"���۱�", 7, 0, 4}, {"�Ͽ��ű�", 10, 0, 5}
    },
    {
        {"��â", 2, 0, 1},{"���� â", 4, 0, 2}, {"����â", 5, 0, 3}, {"û������", 7, 0, 4}, {"��õ��â", 10, 0, 5}
    },
    {
        {"���� �Ѳ�", 1, 1, 1}, {"���� ����", 3, 3, 2}, {"�ձ� ����", 4, 4, 3}, {"���� ����", 6, 6, 4}, {"�븰����", 9, 9, 5}
    }
};


equipment equipments[5] = {
        {"�ﺣ ��", 0, 1, 1}, { "õ ����", 0, 2, 2 }, {"�Ǳݰ���", 0, 3, 3}, {"�μ�����", 0, 4, 4}, {"�븰����", 0, 6, 6}
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

        memset(player.currentweaponName, '\0', sizeof(player.currentweaponName));
        strcpy(player.currentweaponName, weapons[player.job][i].name);

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

        strcpy(player.currentequipmentName, equipments[i].name);

    }
    
}
