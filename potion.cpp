#include "potion.h"


void hppotion() {
	if (player.hppotion == 0) {
		updateBattleLog("����� ���� HP������ 0���Դϴ�!!");

	}
	else if (player.hppotion > 0) {
		if (player.hp == 10) {
			updateBattleLog("���̻� ȸ���� hp�� �����ϴ�!!");
		}
		else if (player.hp <= 8) {
			player.hp += 2;
			updateBattleLog("hp�� 2 ȸ���Ͽ����ϴ�!!");
			player.hppotion--;
		}
		else if (player.hp == 9) {
			player.hp += 1;
			updateBattleLog("hp�� 1 ȸ���Ͽ����ϴ�!!");
			player.hppotion--;
		}
	}
}//                                                           hp���� �Լ�

void mppotion() {
	if (player.mppotion == 0) {
		updateBattleLog("����� ���� MP������ 0���Դϴ�!!");

	}
	else if (player.mppotion > 0) {
		if (player.mp == 10) {
			updateBattleLog("���̻� ȸ���� MP�� �����ϴ�!!");
		}
		else if (player.mp <= 8) {
			player.mp += 2;
			updateBattleLog("MP�� 2 ȸ���Ͽ����ϴ�!!");
			player.mppotion--;
		}
		else if (player.mp == 9) {
			player.mp += 1;
			updateBattleLog("MP�� 1 ȸ���Ͽ����ϴ�!!");
			player.mppotion--;
		}
	}
}//                                                           mp���� �Լ�

