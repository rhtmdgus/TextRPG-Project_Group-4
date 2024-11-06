#include "battle.h"
#include <conio.h>

// 전투 함수
void battle()
{
	updateBattleLog("Battle start!!");
	int damageToEnemy;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수

	while (Jap1.hp > 0 && player.hp > 0)
	{
		displayBattleScreen();
		char action = _getch();

		switch (action)
		{
		case 'a':
		case 'A':
			// 공격 로직
			damageToEnemy = player.attack - Jap1.defense; // 이전에 선언한 변수를 사용
			if (damageToEnemy > 0) {
				Jap1.hp -= damageToEnemy;
				updateBattleLog("You attacked the enemy!");
			}
			else {
				updateBattleLog("Your attack was too weak!");
			}

			// 적 반격
			if (Jap1.hp > 0) {
				damageToPlayer = Jap1.attack - player.defense; // 이전에 선언한 변수를 사용
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					updateBattleLog("The enemy attacked you!");
				}
			}
			break;

		case 'r':
		case 'R':
			updateBattleLog("You ran away from the enemy!");
			Jap1.hp = 0; // 적 HP를 0으로 설정하여 전투 종료
			break;

		default:
			updateBattleLog("Invalid action! Choose again.");
			break;
		}

		// 상태 체크
		if (Jap1.hp <= 0) {
			Jap1.hp = 0;
			updateBattleLog("You defeated the enemy!");
			Situation = 0;
		}
		else if (player.hp <= 0) {
			player.hp = 0;
			updateBattleLog("You have been defeated...");
			Situation = 0;
		}
	}

	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("Press any key to return to the main screen...");
	displayBattleScreen();
	_getch();  // 사용자 입력 대기

	initializeMap(); // 맵 초기화
	displayMap(); // 이동 맵 출력
	drawPlayer(); // 플레이어 위치 출력
}