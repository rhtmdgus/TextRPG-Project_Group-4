#include <conio.h>
#include <time.h>
#include "battle.h"
#include "potion.h"
#include "animation.h"
#include "quest.h"

int OriginalLevel;

void LevelUp()	//레벨업
{
	while (player.exp >= EXPbar)
	{
		player.exp = player.exp - EXPbar;
		player.level++;
		maxhp++;
		maxmp++;
		if (player.hp < maxhp)
			player.hp = maxhp;
		if (player.mp < maxmp)
			player.mp = maxmp;
		if (player.job == 1)
		{
			player.attack++;
		}
		else if (player.job == 2)
		{
			player.accuracy++;
		}
		else if (player.job == 4)
		{
			player.defense++;
		}

	}
	if (player.level >= 15)
		EXPbar = 40;
	else if (player.level >= 10)
		EXPbar = 30;
	else if (player.level >= 5)
		EXPbar = 20;
	else
		EXPbar = 10;

}
int Crit()	//크리티컬 히트
{
	// 랜덤 시드 초기화
	srand((unsigned int)time(NULL));
	// accuracy에 따라 치명타 확률 계산 (5%씩 증가)
	int criticalChance = player.accuracy * 5; // accuracy가 0일 때는 0%, 1일 때는 5%...

	// 확률을 0과 1 사이로 변환
	int probability = rand() % 100;

	// 치명타 발생 여부 결정
	if (probability < criticalChance) {
		return 1; // 치명타 발생
	}
	else {
		return 0; // 치명타 미발생
	}
}


// 전투 함수
void battle(Enemy* enemy)
{
	updateBattleLog("Battle start!!");
	int damageToEnemy;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수
	displayBattleScreen();
	displayPlayerStat();
	displayEnemyStat(enemy);
	displayBattleLog();

	while (enemy->hp > 0 && player.hp > 0 && Situation == 1)
	{
		char action = _getch();

		if (enemy == nullptr) {
			updateBattleLog("Error: No enemy to battle.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp포션 사용
			hppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp포션 사용
			mppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			// 공격 로직
			
			damageToEnemy = player.attack - enemy->defense; // 이전에 선언한 변수를 사용
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					enemyAttackedAnimation(enemy);
					updateBattleLog("Critical Attack!");
					damageToEnemy *= 2;
				}
				else
				{
					playerAttackAnimation();
					enemyAttackedAnimation(enemy);
				}
				enemy->hp -= damageToEnemy;
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("You attacked the enemy!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("Your attack was too weak!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}

			// 적 반격
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // 이전에 선언한 변수를 사용
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("The enemy attacked you!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

		//적과 전투에서 도주
		case 'r':
		case 'R':
			updateBattleLog("You ran away from the enemy!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("You fled from battle!");
			break;

		default:
			updateBattleLog("Invalid action! Choose again.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		// 상태 체크
		if (enemy->hp <= 0) {
			enemyDyingAnimation(enemy);
			updateBattleLog("You defeated the enemy!");
			player.exp += 12;
			player.money += 4;
			player.killcount++;
			updateQuestStatusKill();
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
			playerDyingAnimation();
			updateBattleLog("You have been defeated...");
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
	}

	OriginalLevel = player.level;
	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("Press any key to return to the main screen...");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // 사용자 입력 대기

	if (player.level > OriginalLevel)
		updateLog("Level up!!");

	initializeMap(); // 맵 초기화
	displayMap(); // 이동 맵 출력
	displayPlayerStat(); //플레이어 스탯 표시
	drawPlayer(); // 플레이어 위치 출력
}

// 보스 전투 함수
void bossbattle(Enemy* boss)
{
	updateBattleLog("Battle start!!");
	int damageToBoss;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수
	displayBossBattleScreen();
	displayPlayerStat();
	displayBossStat(boss);
	displayBattleLog();

	while (boss->hp > 0 && player.hp > 0 && Situation == 7)
	{
		char action = _getch();

		if (boss == nullptr) {
			updateBattleLog("Error: No boss to battle.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp포션 사용
			hppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp포션 사용
			mppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			// 공격 로직
			
			damageToBoss = player.attack - boss->defense; // 이전에 선언한 변수를 사용
			if (damageToBoss > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					BossDamaged(boss);
					updateBattleLog("Critical Attack!");
					damageToBoss *= 2;
				}
				else
				{
					playerAttackAnimation();
					BossDamaged(boss);
				}
				boss->hp -= damageToBoss;
				if (boss->hp <= 0)
					boss->hp = 0;
				updateBattleLog("You attacked the enemy!");
				displayPlayerStat();
				displayBossStat(boss);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("Your attack was too weak!");
				displayPlayerStat();
				displayBossStat(boss);
				Sleep(100);
				displayBattleLog();
			}

			// 적 반격
			if (boss->hp > 0) {
				BossAttack(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // 이전에 선언한 변수를 사용
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("The boss attacked you!");
					displayPlayerStat();
					displayBossStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

			//적과 전투에서 도주
		case 'r':
		case 'R':
			updateBattleLog("You ran away from the boss!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			updateLog("You fled from battle!");
			break;

		default:
			updateBattleLog("Invalid action! Choose again.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		// 상태 체크
		if (boss->hp <= 0) {
			BossDying(boss);
			updateBattleLog("You defeated the boss!");
			updateQuestStatusItem(6);
			player.exp += 30;
			player.money += 10;
			player.questitem1 = 1;
			checkboss1 = 1;
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
			playerDyingAnimation();
			updateBattleLog("You have been defeated...");
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
	}

	OriginalLevel = player.level;
	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("Press any key to return to the main screen...");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // 사용자 입력 대기

	if (player.level > OriginalLevel)
		updateLog("Level up!!");

	initializeMap(); // 맵 초기화
	displayMap(); // 이동 맵 출력
	displayPlayerStat(); //플레이어 스탯 표시
	drawPlayer(); // 플레이어 위치 출력
}