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
	printf("  스킬목록");

	if (player.job == 1) {

		if (player.level >= 5) {
			
			setCursorPosition(101, 23);
			printf("  1. 강타");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("  2. 난도질");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("  3. 광폭화");
		}
	}
	else if (player.job == 2) {

		if (player.level >= 5) {

			setCursorPosition(101, 23);
			printf("1. 연사");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("2. 집중사격");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("3. 불화살");
		}
	}
	else if (player.job == 3) {

		if (player.level >= 5) {

			setCursorPosition(101, 23);
			printf("1. 투창");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("2. 삼조격");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("3. 무쌍돌격");
		}
	}

	else if (player.job == 4) {

		if (player.level >= 5) {

			setCursorPosition(101, 23);
			printf("1. 방패밀치기");
		}
		if (player.level >= 10) {

			setCursorPosition(101, 24);
			printf("2. 방어태세");
		}
		if (player.level >= 15) {

			setCursorPosition(101, 25);
			printf("3. 가시방패");
		}
	}
}



