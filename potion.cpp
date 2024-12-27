#include "potion.h"
#include "player.h"

void hppotion() {
	if (player.HPpotion == 0) {
		updateBattleLog("당신은 현재 체력 물약이 0개입니다!!");

	}
	else if (player.HPpotion > 0) {
		if (player.hp == maxhp) {
			updateBattleLog("더이상 회복할 체력이 없습니다!!");
		}
		else if (player.hp <= maxhp - 2) {
			player.hp += 2;
			updateBattleLog("체력을 2 회복하였습니다!!");
			player.HPpotion--;
		}
		else if (player.hp == maxhp - 1) {
			player.hp += 1;
			updateBattleLog("체력을 1 회복하였습니다!!");
			player.HPpotion--;
		}
	}
}//                                                           hp포션 함수

void mppotion() {
	if (player.MPpotion == 0) {
		updateBattleLog("당신은 현재 기력 물약이 0개입니다!!");

	}
	else if (player.MPpotion > 0) {
		if (player.mp == maxmp) {
			updateBattleLog("더이상 회복할 기력이 없습니다!!");
		}
		else if (player.mp <= maxmp - 2) {
			player.mp += 2;
			updateBattleLog("기력을 2 회복하였습니다!!");
			player.MPpotion--;
		}
		else if (player.mp == maxmp - 1) {
			player.mp += 1;
			updateBattleLog("기력을 1 회복하였습니다!!");
			player.MPpotion--;
		}
	}
}//                                                           mp포션 함수

