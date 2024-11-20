#include "item.h"
#include "log.h"
#pragma warning(disable:4996)



weapon weapons[5][10] =
{
    {
        {"녹슨 호미", 1, 0, 0 }

    },
    {
        {"부엌칼", 2, 0, 1}, {"군용 대검", 4, 0, 2}, {"조선 환도", 5, 0, 3},{"백호검", 7, 0, 4},{"화룡신검", 10, 0, 5}
    },
    {
        {"새총", 2, 0, 1}, {"군용 활", 4, 0, 2}, {"만궁", 5, 0, 3}, {"주작궁", 7, 0, 4}, {"일월신궁", 10, 0, 5}
    },
    {
        {"죽창", 2, 0, 1},{"군용 창", 4, 0, 2}, {"삼지창", 5, 0, 3}, {"청룡언월도", 7, 0, 4}, {"파천신창", 10, 0, 5}
    },
    {
        {"냄비 뚜껑", 1, 1, 1}, {"군용 방패", 3, 3, 2}, {"합금 방패", 4, 4, 3}, {"현무 방패", 6, 6, 4}, {"용린방패", 9, 9, 5}
    }
};


equipment equipments[5] = {
        {"삼베 옷", 0, 1, 1}, { "천 갑옷", 0, 2, 2 }, {"판금갑옷", 0, 3, 3}, {"두석린갑", 0, 4, 4}, {"용린갑옷", 0, 6, 6}
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

        updateLog("현재장비보다 티어가 높은 장비이므로 장비를 교체합니다!");
    }
    else if (player.currentweapon == weapons[player.job][i].weaponTier) 
    {
        updateLog("현재장비와 같은 장비이므로 장비를 교체하지 않습니다!");
    } 
    else {
        updateLog("현재장비보다 티어가 낮은 장비이므로 장비를 교체하지 않습니다!");
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
