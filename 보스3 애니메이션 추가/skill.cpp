#include "skill.h"
#include <stdio.h>


int skill1(int playerAttackPoint) {
	if (player.job == 1) {

		int Damage;

		Damage = player.attack * 3;

		return Damage;

	}
	else if (player.job == 2) {

		int Damage;

		Damage = player.attack * 3;

		return Damage;

	}
	else if (player.job == 3) {

		int Damage;

		Damage = player.attack * 3;

		return Damage;
	}
	else if (player.job == 4) {
		int Damage;

		Damage = player.attack * 3;

		return Damage;
	}


}

int skill2(int playerAttackPoint) {
	if (player.job == 1) {

		int Damage;

		Damage = player.attack * 4;

		return Damage;

	}
	else if (player.job == 2) {

		int Damage;

		Damage = player.attack * 5;

		return Damage;

	}
	else if (player.job == 3) {

		int Damage;

		Damage = player.attack * 4;

		return Damage;
	}
	


}

int skill3(int playerAttackPoint) {
	
	if (player.job == 3) {
		int Damage;

		Damage = player.attack * 6;

		return Damage;
	}

	
}





void SkillAppear() {

	setCursorPosition(101, 22);
	printf("  ��ų���");

	if (player.job == 1) {

		if (player.level >= 5) {
			
			setCursorPosition(101, 23);
			printf("  1. ��Ÿ");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("  2. ������");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("  3. ����ȭ");
		}
	}
	else if (player.job == 2) {

		if (player.level >= 5) {

			setCursorPosition(101, 23);
			printf("1. ����");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("2. ���߻��");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("3. ��ȭ��");
		}
	}
	else if (player.job == 3) {

		if (player.level >= 5) {

			setCursorPosition(101, 23);
			printf("1. ��â");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("2. ������");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("3. ���ֵ���");
		}
	}

	else if (player.job == 4) {

		if (player.level >= 5) {

			setCursorPosition(101, 23);
			printf("1. ���й�ġ��");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("2. ����¼�");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("3. ���ù���");
		}
	}
}



