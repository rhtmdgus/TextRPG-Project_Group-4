#include "potion.h"
#include "player.h"

void hppotion() {
	if (player.HPpotion == 0) {
		updateBattleLog("����� ���� ü�� ������ 0���Դϴ�!!");

	}
	else if (player.HPpotion > 0) {
		if (player.hp == maxhp) {
			updateBattleLog("���̻� ȸ���� ü���� �����ϴ�!!");
		}
		else if (player.hp <= maxhp - 2) {
			player.hp += 2;
			updateBattleLog("ü���� 2 ȸ���Ͽ����ϴ�!!");
			player.HPpotion--;
		}
		else if (player.hp == maxhp - 1) {
			player.hp += 1;
			updateBattleLog("ü���� 1 ȸ���Ͽ����ϴ�!!");
			player.HPpotion--;
		}
	}
}//                                                           hp���� �Լ�

void mppotion() {
	if (player.MPpotion == 0) {
		updateBattleLog("����� ���� ��� ������ 0���Դϴ�!!");

	}
	else if (player.MPpotion > 0) {
		if (player.mp == maxmp) {
			updateBattleLog("���̻� ȸ���� ����� �����ϴ�!!");
		}
		else if (player.mp <= maxmp - 2) {
			player.mp += 2;
			updateBattleLog("����� 2 ȸ���Ͽ����ϴ�!!");
			player.MPpotion--;
		}
		else if (player.mp == maxmp - 1) {
			player.mp += 1;
			updateBattleLog("����� 1 ȸ���Ͽ����ϴ�!!");
			player.MPpotion--;
		}
	}
}//                                                           mp���� �Լ�

