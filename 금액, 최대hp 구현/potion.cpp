#include "potion.h"
#include "player.h"

void hppotion() {
	if (player.HPpotion == 0) {
		updateBattleLog("����� ���� HP������ 0���Դϴ�!!");

	}
	else if (player.HPpotion > 0) {
		if (player.hp == maxhp) {
			updateBattleLog("���̻� ȸ���� hp�� �����ϴ�!!");
		}
		else if (player.hp <= maxhp - 2) {
			player.hp += 2;
			updateBattleLog("hp�� 2 ȸ���Ͽ����ϴ�!!");
			player.HPpotion--;
		}
		else if (player.hp == maxhp - 1) {
			player.hp += 1;
			updateBattleLog("hp�� 1 ȸ���Ͽ����ϴ�!!");
			player.HPpotion--;
		}
	}
}//                                                           hp���� �Լ�

void mppotion() {
	if (player.MPpotion == 0) {
		updateBattleLog("����� ���� MP������ 0���Դϴ�!!");

	}
	else if (player.MPpotion > 0) {
		if (player.mp == 10) {
			updateBattleLog("���̻� ȸ���� MP�� �����ϴ�!!");
		}
		else if (player.mp <= 8) {
			player.mp += 2;
			updateBattleLog("MP�� 2 ȸ���Ͽ����ϴ�!!");
			player.MPpotion--;
		}
		else if (player.mp == 9) {
			player.mp += 1;
			updateBattleLog("MP�� 1 ȸ���Ͽ����ϴ�!!");
			player.MPpotion--;
		}
	}
}//                                                           mp���� �Լ�

