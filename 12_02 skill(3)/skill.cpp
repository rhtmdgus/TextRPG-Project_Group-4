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
	else if (player.job == 4) {
		
		int increaseDefense;

		increaseDefense = 5;

		return increaseDefense;

	}


}

int skill3(int playerAttackPoint) {
	if (player.job == 1) {
		int increaseAttack = 8;

		return increaseAttack;

	}
	else if (player.job == 2) {
		int Damage;

		Damage = player.attack * 2;

		return Damage;
	}
	else if (player.job == 3) {
		int Damage;

		Damage = player.attack * 6;

		return Damage;
	}

	
}









int warriorSkill1() {
	
	int Damage;

	Damage = player.attack * 3;

	return Damage;
}

int warriorSkill2() {

	int Damage;

	Damage = player.attack * 4;

	return Damage;
}

int warriorSkill3() { // player.attack �� warriorSkill3�� ���ؼ� ���

	int increaseAttack = 8;

	return increaseAttack;
}

int archerSkill1() {

	int Damage;

	Damage = player.attack * 3;

	return Damage;
}

int archerSkill2() {

	int Damage;

	Damage = player.attack * 5;

	return Damage;

}

int archerSkill3() {
	int Damage;

	Damage = player.attack * 2;

	return Damage;

}

int spearSkill1() {
	int Damage;

	Damage = player.attack * 3;

	return Damage;
}


int spearSkill2() {
	int Damage;

	Damage = player.attack * 4;

	return Damage;
}

int spearSkill3() {
	int Damage;

	Damage = player.attack * 6;

	return Damage;
}

int shieldSkill1() {
	int Damage;

	Damage = player.attack * 3;

	return Damage;
}

int shieldSkill2() {
	int increaseDefense;

	increaseDefense = 5;

	return increaseDefense;
}

int shieldSkill3(int Damaged) {
	int Reflect;


	Reflect = Damaged;


	return Reflect;
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



