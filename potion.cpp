#include "potion.h"


void hppotion() {
	if (player.hppotion == 0) {
		updateBattleLog("당신은 현재 HP포션이 0개입니다!!");

	}
	else if (player.hppotion > 0) {
		if (player.hp == 10) {
			updateBattleLog("더이상 회복할 hp가 없습니다!!");
		}
		else if (player.hp <= 8) {
			player.hp += 2;
			updateBattleLog("hp를 2 회복하였습니다!!");
			player.hppotion--;
		}
		else if (player.hp == 9) {
			player.hp += 1;
			updateBattleLog("hp를 1 회복하였습니다!!");
			player.hppotion--;
		}
	}
}//                                                           hp포션 함수

void mppotion() {
	if (player.mppotion == 0) {
		updateBattleLog("당신은 현재 MP포션이 0개입니다!!");

	}
	else if (player.mppotion > 0) {
		if (player.mp == 10) {
			updateBattleLog("더이상 회복할 MP가 없습니다!!");
		}
		else if (player.mp <= 8) {
			player.mp += 2;
			updateBattleLog("MP를 2 회복하였습니다!!");
			player.mppotion--;
		}
		else if (player.mp == 9) {
			player.mp += 1;
			updateBattleLog("MP를 1 회복하였습니다!!");
			player.mppotion--;
		}
	}
}//                                                           mp포션 함수

