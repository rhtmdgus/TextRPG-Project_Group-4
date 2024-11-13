#include "potion.h"
#include "player.h"

void hppotion() {
	if (player.HPpotion == 0) {
		updateBattleLog("당신은 현재 HP포션이 0개입니다!!");

	}
	else if (player.HPpotion > 0) {
		if (player.hp == maxhp) {
			updateBattleLog("더이상 회복할 hp가 없습니다!!");
		}
		else if (player.hp <= maxhp - 2) {
			player.hp += 2;
			updateBattleLog("hp를 2 회복하였습니다!!");
			player.HPpotion--;
		}
		else if (player.hp == maxhp - 1) {
			player.hp += 1;
			updateBattleLog("hp를 1 회복하였습니다!!");
			player.HPpotion--;
		}
	}
}//                                                           hp포션 함수

void mppotion() {
	if (player.MPpotion == 0) {
		updateBattleLog("당신은 현재 MP포션이 0개입니다!!");

	}
	else if (player.MPpotion > 0) {
		if (player.mp == 10) {
			updateBattleLog("더이상 회복할 MP가 없습니다!!");
		}
		else if (player.mp <= 8) {
			player.mp += 2;
			updateBattleLog("MP를 2 회복하였습니다!!");
			player.MPpotion--;
		}
		else if (player.mp == 9) {
			player.mp += 1;
			updateBattleLog("MP를 1 회복하였습니다!!");
			player.MPpotion--;
		}
	}
}//                                                           mp포션 함수

