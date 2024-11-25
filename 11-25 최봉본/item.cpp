#include "item.h"
#include "log.h"
#pragma warning(disable:4996)
#include <string.h>



weapon weapons[5][10] =
{
    {
        {"녹슨 호미", 0, 0, 0 }

    },
    {
        {"목검", 1, 0, 1}, {"부엌칼", 2, 0, 2}, {"낡은 왜군 카타나", 3, 0, 3}, {"왜군 카타나", 4, 0, 4}, { "군용 대검", 5, 0, 5}, {"조선 환도", 6, 0, 6}
        , {"유성검", 7, 0, 7}, {"백호검", 9, 0, 8}, {"화룡신검", 12, 0, 9}
    },
    {
        {"새총", 1, 0, 1}, {"망가진 활", 2, 0, 2}, {"낡은 왜군 활", 3, 0, 3}, {"왜군 활", 4, 0, 4},{"군용 활", 5, 0, 5}, {"석궁", 6, 0, 6}
        ,{"만궁", 7, 0, 7}, {"주작궁", 9, 0, 8}, {"일월신궁", 12, 0, 9}
    },
    {
        {"죽창", 1, 0, 1}, {"망가진 창", 2, 0, 2}, {"낡은 왜군 창", 3, 0, 3}, {"왜군 창", 4, 0, 4}, {"군용 창", 5, 0, 5}, {"삼지창", 6, 0, 6}
        ,{ "방천화극", 7, 0, 7 }, {"청룡언월도", 9, 0, 8}, {"파천신창", 12, 0, 9}
    },
    {
        {"거북이 등껍질", 1, 1, 1}, {"냄비뚜껑", 1, 2, 2}, {"낡은 왜군 방패", 1, 3, 3}, {"왜군 방패", 2, 4, 4},{"군용 방패", 3, 4, 5}, {"합금 방패", 4, 4, 6}
        , { "흑철방패", 4, 5, 7 }, {"현무 방패", 6, 5, 8}, {"불멸방패", 8, 8, 9}
    }
};


equipment equipments[10] = {
        {"삼베 옷", 0, 1, 1}, { "천 갑옷", 0, 2, 2 }, {"가죽 갑옷", 0, 3, 3}, {"왜군 갑옷", 0, 4, 4}, {"군용 갑옷", 0, 5, 5}, {"두정갑", 0, 6, 6}
        , {"어린갑", 0, 7, 7}, {"북두칠갑", 0, 8, 8}, {"용린갑옷", 0, 9, 9}
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
        player.currentweaponName[sizeof(player.currentweaponName) - 1] = '\0'; // null-termination 보장

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

        strncpy(player.currentequipmentName, equipments[i].name, sizeof(player.currentequipmentName) - 1);
        player.currentequipmentName[sizeof(player.currentequipmentName) - 1] = '\0'; // null-termination 보장
        
        updateLog("현재장비보다 티어가 높은 장비이므로 장비를 교체합니다!");
    }
    else if (player.currentequipment == equipments[i].equipmentTier)
    {
        updateLog("현재장비와 같은 장비이므로 장비를 교체하지 않습니다!");
    }
    else {
        updateLog("현재장비보다 티어가 낮은 장비이므로 장비를 교체하지 않습니다!");
    }

    
}
