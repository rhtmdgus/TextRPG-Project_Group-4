#include <conio.h>
#include <time.h>
#include "battle.h"
#include "potion.h"
#include "animation.h"
#include "quest.h"

int hiddenPotionCount = 0;
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
	updateBattleLog("전투 시작!!");
	int damageToEnemy;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수
	displayBattleScreen();
	displayPlayerStat();
	displayEnemyStat(enemy);
	displayBattleLog();

	SkillAppear();

	while (enemy->hp > 0 && player.hp > 0 && Situation == 1)
	{


		char action = _getch();

		if (enemy == nullptr) {
			updateBattleLog("오류: 전투에 적이 없습니다.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp포션 사용
			hppotion(); if (hiddenPotionCount == 19)
			{
				updateBattleLog("당신은 물약 과다사용으로 중독되어서 죽었습니다...");
				player.ending = 5;
				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp포션 사용
			mppotion();
			if (hiddenPotionCount == 19)
			{
				updateBattleLog("당신은 물약 과다사용으로 중독되어서 죽었습니다...");
				player.ending = 5;
				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			hiddenPotionCount = 0;
			// 공격 로직

			damageToEnemy = player.attack - enemy->defense; // 이전에 선언한 변수를 사용
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					enemyAttackedAnimation(enemy);
					updateBattleLog("치명타 공격!");
					damageToEnemy *= 2;
				}
				else
				{
					playerAttackAnimation();
					enemyAttackedAnimation(enemy);
				}
				enemy->hp -= damageToEnemy;
				if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
					Sleep(100);
					enemyAttackedAnimation(enemy);
					enemy->hp -= 3;
					updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
					displayBattleLog();
				}

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}

				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("적을 공격하였습니다!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("당신의 공격이 너무 약합니다!");
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
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;
		case 'z':  //스킬 1
		case 'Z':
			hiddenPotionCount = 0;
			// 공격 로직
			if (player.level < 5) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 5) {
				updateBattleLog("기력이 부족합니다!!");
				displayBattleLog();
				break;
			}

			damageToEnemy = skill1(player.attack) - enemy->defense; // 이전에 선언한 변수를 사용
			player.mp -= 5;
			updateBattleLog("스킬 1이 발동되었습니다!");
			if (player.job == 1) {
				updateBattleLog("강타 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 2) {
				updateBattleLog("연사 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 3) {
				updateBattleLog("투창 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 4) {
				updateBattleLog("방패밀치기 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			displayBattleLog();
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					enemyAttackedAnimation(enemy);
					updateBattleLog("치명타 공격!");
					damageToEnemy *= 2;
				}
				else
				{
					enemyAttackedAnimation(enemy);
				}
				enemy->hp -= damageToEnemy;
				if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
					Sleep(100);
					enemyAttackedAnimation(enemy);
					enemy->hp -= 3;
					updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("적을 공격하였습니다.!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("당신의 공격이 너무 약합니다!");
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
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

		case 'x':  // 스킬 2
		case 'X':
			hiddenPotionCount = 0;
			if (player.level < 10) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 10) {
				updateBattleLog("기력이 부족합니다!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("스킬 2이 발동되었습니다!");
			displayLog();
			// 공격 로직
			if (player.job == 4) { // 방패병 스킬 2 
				player.mp -= 10;
				player.buff_defense = 5;  // 방어력 5 증가
				player.defense += player.buff_defense;
				player.buffcount2 = 3;     // 3턴 지속, buffcount2 에 방패병 스킬2를 할당
				updateBattleLog("방어태세 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(2);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else {
				damageToEnemy = skill2(player.attack) - enemy->defense; // 이전에 선언한 변수를 사용
				player.mp -= 10;
				if (player.job == 1) {
					updateBattleLog("난도질 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 2) {
					updateBattleLog("집중사격 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 3) {
					updateBattleLog("삼조격 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("치명타 공격!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
						displayBattleLog();
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("적을 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}

			// 적 반격
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'c':  //스킬 3
		case 'C':
			hiddenPotionCount = 0;
			if (player.level < 15) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 20) {
				updateBattleLog("기력이 부족합니다!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("스킬 3이 발동되었습니다!");
			displayBattleLog();

			if (player.job == 1) { // 전사 스킬 3 광폭화
				player.mp -= 20;
				player.buff_attack = 10;  // 공격력 10 증가
				player.attack += player.buff_attack;
				player.buffcount1 = 3;     // 3턴 지속
				updateBattleLog("광폭화 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 4) { // 방패병 스킬 3: 가시방패
				player.mp -= 20;
				player.buff_reflect = 1;    // 가시방패 활성화
				player.buffcount3 = 5;      // 5턴 지속, 방패병 스킬 3을 buffcount3에 할당
				updateBattleLog("가시방패 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 2) { // 궁수 스킬 3 불화살
				damageToEnemy = player.attack - enemy->defense; // 이전에 선언한 변수를 사용
				player.mp -= 20;
				player.buffcount1 = 5;
				updateBattleLog("불화살 발동!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("치명타 공격!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.buffcount1 > 0) {
						Sleep(100);
						enemy->hp -= 3;
						enemyAttackedAnimation(enemy);
						updateBattleLog("불화살 지속딜이 들어갔습니다!");
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("적을 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			else if (player.job == 3) {
				damageToEnemy = skill3(player.attack) - enemy->defense; // 이전에 선언한 변수를 사용
				player.mp -= 20;
				updateBattleLog("무쌍돌격 발동!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("치명타 공격!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("적을 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}

			}
			// 적 반격
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
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
			hiddenPotionCount = 0;
			updateBattleLog("적에게서 도망쳤습니다!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("전투에서 벗어났습니다!");
			break;

		default:
			updateBattleLog("불가능한 행동! 다시 선택해주세요.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		if (player.buffcount1 > 0)
		{
			player.buffcount1--;
			if (player.buffcount1 == 0)
			{
				player.attack -= player.buff_attack;  // 공격력 버프 제거
				player.buff_attack = 0;
				updateBattleLog("버프의 지속시간이 끝났습니다!");
			}
		}

		if (player.buffcount2 > 0)
		{
			player.buffcount2--;
			if (player.buffcount2 == 0)
			{
				player.defense -= player.buff_defense; // 방어력 버프 제거
				player.buff_defense = 0;
				updateBattleLog("방어태세의 지속시간이 끝났습니다!");
			}
		}
		if (player.buffcount3 > 0)
		{
			player.buffcount3--;
			if (player.buffcount3 == 0)
			{
				player.buff_reflect = 0;  // 가시갑옷 비활성화
				updateBattleLog("가시갑옷의 지속 시간이 끝났습니다!");
			}
		}

		// 상태 체크
		if (enemy->hp <= 0) {
			enemyDyingAnimation(enemy);
			updateBattleLog("적을 물리쳤습니다!");
			player.exp += 12;
			player.money += 4;
			player.killcount++;
			player.buff_reflect = 0;
			if (player.buffcount1 != 0) {
				player.buffcount1 = 0;
				player.attack -= player.buff_attack;  // 공격력 버프 제거
				player.buff_attack = 0;
			}
			if (player.buffcount2 != 0) {
				player.buffcount2 = 0;
				player.defense -= player.buff_defense; // 방어력 버프 제거
				player.buff_defense = 0;
			}
			if (player.buffcount3 != 0) {
				player.buffcount3 = 0;
				player.buff_reflect = 0;  // 가시갑옷 비활성화
			}
			updateQuestStatusKill();
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
			playerDyingAnimation();
			updateBattleLog("당신은 패배하였습니다...");
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			player.ending = 4;

			Situation = 0;
		}
		else if (player.ending != 0) {
			playerDyingAnimation();
			Situation = 0;
			player.pos = previousPos;
			break;
		}
	}
	OriginalLevel = player.level;
	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("아무 키를 눌러 맵으로 돌아가십시오.");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // 사용자 입력 대기

	if (player.level > OriginalLevel)
		updateLog("레벨 업!!");

	initializeMap(); // 맵 초기화
	displayMap(); // 이동 맵 출력
	displayPlayerStat(); //플레이어 스탯 표시
	drawPlayer(); // 플레이어 위치 출력
}

// 보스 전투 함수
void bossbattle(Enemy* boss)
{
	updateBattleLog("전투시작!!");
	int damageToBoss;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수
	displayBossBattleScreen();
	displayPlayerStat();
	displayBossStat(boss);
	displayBattleLog();
	SkillAppear();

	while (boss->hp > 0 && player.hp > 0 && Situation == 7)
	{
		char action = _getch();

		if (boss == nullptr) {
			updateBattleLog("오류: 전투에 보스가 없습니다");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp포션 사용
			hppotion();
			if (hiddenPotionCount == 19)
			{
				updateBattleLog("당신은 물약 과다사용으로 중독되어서 죽었습니다...");
				player.ending = 5;

				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp포션 사용
			mppotion();
			if (hiddenPotionCount == 19)
			{
				updateBattleLog("당신은 물약 과다사용으로 중독되어서 죽었습니다...");
				player.ending = 5;

				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			hiddenPotionCount = 0;
			// 공격 로직

			damageToBoss = player.attack - boss->defense; // 이전에 선언한 변수를 사용
			if (damageToBoss > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					BossDamaged(boss);
					updateBattleLog("치명타 공격!");
					damageToBoss *= 2;
				}
				else
				{
					playerAttackAnimation();
					BossDamaged(boss);
				}
				boss->hp -= damageToBoss;
				if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
					Sleep(100);
					BossDamaged(boss);
					boss->hp -= 3;
					updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
				if (boss->hp <= 0)
					boss->hp = 0;
				updateBattleLog("적 장수를 공격하였습니다!");
				displayPlayerStat();
				displayBossStat(boss);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("당신의 공격이 너무 약합니다!");
				displayPlayerStat();
				displayBossStat(boss);
				Sleep(100);
				displayBattleLog();

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}

			// 적 반격
			if (boss->hp > 0) {
				BossAttack(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = boss->attack; // 반사 데미지 계산
					boss->hp -= reflectedDamage;
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적 장수에게 공격 당하였습니다!");
					displayPlayerStat();
					displayBossStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'z':  //스킬 1
		case 'Z':
			hiddenPotionCount = 0;
			// 공격 로직
			if (player.level < 5) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 5) {
				updateBattleLog("마나가 부족합니다!!");
				displayBattleLog();
				break;
			}

			damageToBoss = skill1(player.attack) - boss->defense; // 이전에 선언한 변수를 사용
			player.mp -= 5;
			updateBattleLog("스킬 1이 발동되었습니다!");
			if (player.job == 1) {
				updateBattleLog("강타 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 2) {
				updateBattleLog("연사 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 3) {
				updateBattleLog("투창 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 4) {
				updateBattleLog("방패밀치기 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			displayBattleLog();
			if (damageToBoss > 0) {
				if (Crit() == 1)
				{
					BossDamaged(boss);
					updateBattleLog("치명타 공격!");
					damageToBoss *= 2;
				}
				else
				{
					BossDamaged(boss);
				}
				boss->hp -= damageToBoss;
				if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
					Sleep(100);
					BossDamaged(boss);
					boss->hp -= 3;
					updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
				if (boss->hp <= 0)
					boss->hp = 0;
				updateBattleLog("적 장수를 공격하였습니다!");
				displayPlayerStat();
				displayEnemyStat(boss);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("당신의 공격이 너무 약합니다!");
				displayPlayerStat();
				displayEnemyStat(boss);
				Sleep(100);
				displayBattleLog();

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}

			// 적 반격
			if (boss->hp > 0) {
				enemyAttackAnimation(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = boss->attack; // 반사 데미지 계산
					boss->hp -= reflectedDamage;
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적 장수에게 공격 당하였습니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

		case 'x':  // 스킬 2
		case 'X':
			hiddenPotionCount = 0;
			if (player.level < 10) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 10) {
				updateBattleLog("마나가 부족합니다!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("스킬 2이 발동되었습니다!");
			displayLog();
			// 공격 로직
			if (player.job == 4) { // 방패병 스킬 2 
				player.mp -= 10;
				player.buff_defense = 5;  // 방어력 5 증가
				player.defense += player.buff_defense;
				player.buffcount2 = 3;     // 3턴 지속, buffcount2 에 방패병 스킬2를 할당
				updateBattleLog("방어태세 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(2);

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else {
				damageToBoss = skill2(player.attack) - boss->defense; // 이전에 선언한 변수를 사용
				player.mp -= 10;
				if (player.job == 1) {
					updateBattleLog("난도질 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 2) {
					updateBattleLog("집중사격 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 3) {
					updateBattleLog("삼조격 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				if (damageToBoss > 0) {
					if (Crit() == 1)
					{
						BossDamaged(boss);
						updateBattleLog("치명적 공격!");
						damageToBoss *= 2;
					}
					else
					{
						BossDamaged(boss);
					}
					boss->hp -= damageToBoss;
					if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
						displayBattleLog();
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (boss->hp <= 0)
						boss->hp = 0;
					updateBattleLog("적 장수를 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();

					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
				}
			}

			// 적 반격
			if (boss->hp > 0) {
				enemyAttackAnimation(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = boss->attack; // 반사 데미지 계산
					boss->hp -= reflectedDamage;
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적 장수에게 공격 당하였습니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'c':  //스킬 3
		case 'C':
			hiddenPotionCount = 0;
			if (player.level < 15) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 20) {
				updateBattleLog("마나가 부족합니다!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("스킬 3이 발동되었습니다!");
			displayBattleLog();

			if (player.job == 1) { // 전사 스킬 3 광폭화
				player.mp -= 20;
				player.buff_attack = 10;  // 공격력 10 증가
				player.attack += player.buff_attack;
				player.buffcount1 = 3;     // 3턴 지속
				updateBattleLog("광폭화 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 4) { // 방패병 스킬 3: 가시방패
				player.mp -= 20;
				player.buff_reflect = 1;    // 가시방패 활성화
				player.buffcount3 = 5;      // 5턴 지속, 방패병 스킬 3을 buffcount3에 할당
				updateBattleLog("가시방패 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 2) { // 궁수 스킬 3 불화살
				damageToBoss = player.attack - boss->defense; // 이전에 선언한 변수를 사용
				player.mp -= 20;
				player.buffcount1 = 5;
				updateBattleLog("불화살 발동!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToBoss > 0) {
					if (Crit() == 1)
					{
						BossDamaged(boss);
						updateBattleLog("치명타 공격!");
						damageToBoss *= 2;
					}
					else
					{
						BossDamaged(boss);
					}
					boss->hp -= damageToBoss;
					if (player.buffcount1 > 0) {
						Sleep(100);
						boss->hp -= 3;
						BossDamaged(boss);
						updateBattleLog("불화살 지속딜이 들어갔습니다!");
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (boss->hp <= 0)
						boss->hp = 0;
					updateBattleLog("적 장수를 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();

					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
				}
			}
			else if (player.job == 3) {
				damageToBoss = skill3(player.attack) - boss->defense; // 이전에 선언한 변수를 사용
				player.mp -= 20;
				updateBattleLog("무쌍돌격 발동!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToBoss > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(boss);
						updateBattleLog("치명타 공격!");
						damageToBoss *= 2;
					}
					else
					{
						enemyAttackedAnimation(boss);
					}
					boss->hp -= damageToBoss;
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (boss->hp <= 0)
						boss->hp = 0;
					updateBattleLog("적 장수를 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();

					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
				}

			}
			// 적 반격
			if (boss->hp > 0) {
				enemyAttackAnimation(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = boss->attack; // 반사 데미지 계산
					boss->hp -= reflectedDamage; // 트루데미지
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적 장수에게 공격 당하였습니다!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;




			//적과 전투에서 도주
		case 'r':
		case 'R':
			hiddenPotionCount = 0;
			updateBattleLog("적 장수에게서 도망쳤습니다!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			updateLog("전투에서 벗어났습니다!");
			break;

		default:
			updateBattleLog("불가능한 행동! 다시 선택해주세요.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		if (player.buffcount1 > 0)
		{
			player.buffcount1--;
			if (player.buffcount1 == 0)
			{
				player.attack -= player.buff_attack;  // 공격력 버프 제거
				player.buff_attack = 0;
				updateBattleLog("버프의 지속시간이 끝났습니다!");
			}
		}

		if (player.buffcount2 > 0)
		{
			player.buffcount2--;
			if (player.buffcount2 == 0)
			{
				player.defense -= player.buff_defense; // 방어력 버프 제거
				player.buff_defense = 0;
				updateBattleLog("방어태세의 지속시간이 끝났습니다!");
			}
		}
		if (player.buffcount3 > 0)
		{
			player.buffcount3--;
			if (player.buffcount3 == 0)
			{
				player.buff_reflect = 0;  // 가시갑옷 비활성화
				updateBattleLog("가시갑옷의 지속 시간이 끝났습니다!");
			}
		}





		// 상태 체크
		if (boss->hp <= 0) {
			BossDying(boss);
			updateBattleLog("적 장수를 물리쳤습니다!");
			updateQuestStatusItem(6);
			player.exp += 30;
			player.money += 10;
			player.questitem1 = 1;
			checkboss1 = 1;
			checkboss2 = 1;
			checkboss3 = 1;
			if (player.buffcount1 != 0) {
				player.buffcount1 = 0;
				player.attack -= player.buff_attack;  // 공격력 버프 제거
				player.buff_attack = 0;
			}
			if (player.buffcount2 != 0) {
				player.buffcount2 = 0;
				player.defense -= player.buff_defense; // 방어력 버프 제거
				player.buff_defense = 0;
			}
			if (player.buffcount3 != 0) {
				player.buffcount3 = 0;
				player.buff_reflect = 0;  // 가시갑옷 비활성화
			}
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
			playerDyingAnimation();
			updateBattleLog("당신은 패배하였습니다...");
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			player.ending = 4;

			Situation = 0;
		}
	}





	OriginalLevel = player.level;
	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("아무 키를 눌러 맵으로 돌아가십시오.");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // 사용자 입력 대기

	if (player.level > OriginalLevel)
		updateLog("레벨 업!!");

	initializeMap(); // 맵 초기화
	displayMap(); // 이동 맵 출력
	displayPlayerStat(); //플레이어 스탯 표시
	drawPlayer(); // 플레이어 위치 출력
}

// 랜덤인카운터 전투 함수
void battleRand(Enemy* enemy)
{
	updateBattleLog("전투 시작!!");
	int damageToEnemy;   // 공격할 때 사용할 변수
	int damageToPlayer;  // 반격할 때 사용할 변수
	displayBattleScreen();
	displayPlayerStat();
	displayEnemyStat(enemy);
	displayBattleLog();

	SkillAppear();

	while (enemy->hp > 0 && player.hp > 0 && Situation == 1)
	{


		char action = _getch();

		if (enemy == nullptr) {
			updateBattleLog("오류: 전투에 적이 없습니다.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp포션 사용
			hppotion();
			if (hiddenPotionCount == 19)
			{
				
				updateBattleLog("당신은 물약 과다사용으로 중독되어서 죽었습니다...");
				player.ending = 5;

				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp포션 사용

			mppotion();
			if (hiddenPotionCount == 19)
			{
				
				updateBattleLog("당신은 물약 과다사용으로 중독되어서 죽었습니다...");
				player.ending = 5;

				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			hiddenPotionCount = 0;
			// 공격 로직

			damageToEnemy = player.attack - enemy->defense; // 이전에 선언한 변수를 사용
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					enemyAttackedAnimation(enemy);
					updateBattleLog("치명타 공격!");
					damageToEnemy *= 2;
				}
				else
				{
					playerAttackAnimation();
					enemyAttackedAnimation(enemy);
				}
				enemy->hp -= damageToEnemy;
				if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
					Sleep(100);
					enemyAttackedAnimation(enemy);
					enemy->hp -= 3;
					updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
					displayBattleLog();
				}

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}

				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("적을 공격하였습니다!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("당신의 공격이 너무 약합니다!");
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
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;
		case 'z':  //스킬 1
		case 'Z':
			hiddenPotionCount = 0;
			// 공격 로직
			if (player.level < 5) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 5) {
				updateBattleLog("기력이 부족합니다!!");
				displayBattleLog();
				break;
			}

			damageToEnemy = skill1(player.attack) - enemy->defense; // 이전에 선언한 변수를 사용
			player.mp -= 5;
			updateBattleLog("스킬 1이 발동되었습니다!");
			if (player.job == 1) {
				updateBattleLog("강타 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 2) {
				updateBattleLog("연사 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 3) {
				updateBattleLog("투창 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 4) {
				updateBattleLog("방패밀치기 발동!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			displayBattleLog();
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					enemyAttackedAnimation(enemy);
					updateBattleLog("치명타 공격!");
					damageToEnemy *= 2;
				}
				else
				{
					enemyAttackedAnimation(enemy);
				}
				enemy->hp -= damageToEnemy;
				if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
					Sleep(100);
					enemyAttackedAnimation(enemy);
					enemy->hp -= 3;
					updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("적을 공격하였습니다.!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("당신의 공격이 너무 약합니다!");
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
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

		case 'x':  // 스킬 2
		case 'X':
			hiddenPotionCount = 0;
			if (player.level < 10) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 10) {
				updateBattleLog("기력이 부족합니다!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("스킬 2이 발동되었습니다!");
			displayLog();
			// 공격 로직
			if (player.job == 4) { // 방패병 스킬 2 
				player.mp -= 10;
				player.buff_defense = 5;  // 방어력 5 증가
				player.defense += player.buff_defense;
				player.buffcount2 = 3;     // 3턴 지속, buffcount2 에 방패병 스킬2를 할당
				updateBattleLog("방어태세 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(2);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else {
				damageToEnemy = skill2(player.attack) - enemy->defense; // 이전에 선언한 변수를 사용
				player.mp -= 10;
				if (player.job == 1) {
					updateBattleLog("난도질 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 2) {
					updateBattleLog("집중사격 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 3) {
					updateBattleLog("삼조격 발동!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("치명타 공격!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.job == 2 && player.buffcount1 > 0) {    // 궁수 스킬 3 도트딜 구현
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("불화살의 지속데미지가 들어갔습니다!");
						displayBattleLog();
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("적을 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}

			// 적 반격
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'c':  //스킬 3
		case 'C':
			hiddenPotionCount = 0;
			if (player.level < 15) {
				updateBattleLog("레벨이 부족합니다!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 20) {
				updateBattleLog("기력이 부족합니다!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("스킬 3이 발동되었습니다!");
			displayBattleLog();

			if (player.job == 1) { // 전사 스킬 3 광폭화
				player.mp -= 20;
				player.buff_attack = 10;  // 공격력 10 증가
				player.attack += player.buff_attack;
				player.buffcount1 = 3;     // 3턴 지속
				updateBattleLog("광폭화 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 4) { // 방패병 스킬 3: 가시방패
				player.mp -= 20;
				player.buff_reflect = 1;    // 가시방패 활성화
				player.buffcount3 = 5;      // 5턴 지속, 방패병 스킬 3을 buffcount3에 할당
				updateBattleLog("가시방패 발동!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
					else {                                 // 의병 관계도 50이상일때 1딜 추가
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("의병 동료의 추가 공격!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 2) { // 궁수 스킬 3 불화살
				damageToEnemy = player.attack - enemy->defense; // 이전에 선언한 변수를 사용
				player.mp -= 20;
				player.buffcount1 = 5;
				updateBattleLog("불화살 발동!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("치명타 공격!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.buffcount1 > 0) {
						Sleep(100);
						enemy->hp -= 3;
						enemyAttackedAnimation(enemy);
						updateBattleLog("불화살 지속딜이 들어갔습니다!");
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("적을 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			else if (player.job == 3) {
				damageToEnemy = skill3(player.attack) - enemy->defense; // 이전에 선언한 변수를 사용
				player.mp -= 20;
				updateBattleLog("무쌍돌격 발동!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("치명타 공격!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// 의병 관계도 150이상일때 3딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// 의병 관계도 100이상일때 2딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
						else {                                 // 의병 관계도 50이상일때 1딜 추가
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("의병 동료의 추가 공격!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("적을 공격하였습니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("당신의 공격이 너무 약합니다!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}

			}
			// 적 반격
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // 이전에 선언한 변수를 사용
				if (player.buff_reflect == 1) {  // 가시갑옷 반사 로직
					int reflectedDamage = enemy->attack; // 반사 데미지 계산
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("가시갑옷으로 적에게 데미지를 반사했습니다!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("적에게 공격당하였습니다.!");
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
			hiddenPotionCount = 0;
			updateBattleLog("적에게서 도망쳤습니다!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("전투에서 벗어났습니다!");
			break;

		default:
			updateBattleLog("불가능한 행동! 다시 선택해주세요.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		if (player.buffcount1 > 0)
		{
			player.buffcount1--;
			if (player.buffcount1 == 0)
			{
				player.attack -= player.buff_attack;  // 공격력 버프 제거
				player.buff_attack = 0;
				updateBattleLog("버프의 지속시간이 끝났습니다!");
			}
		}

		if (player.buffcount2 > 0)
		{
			player.buffcount2--;
			if (player.buffcount2 == 0)
			{
				player.defense -= player.buff_defense; // 방어력 버프 제거
				player.buff_defense = 0;
				updateBattleLog("방어태세의 지속시간이 끝났습니다!");
			}
		}
		if (player.buffcount3 > 0)
		{
			player.buffcount3--;
			if (player.buffcount3 == 0)
			{
				player.buff_reflect = 0;  // 가시갑옷 비활성화
				updateBattleLog("가시갑옷의 지속 시간이 끝났습니다!");
			}
		}

		// 상태 체크
		if (enemy->hp <= 0) {
			enemyDyingAnimation(enemy);
			updateBattleLog("적을 물리쳤습니다!");
			player.exp += 12;
			player.money += 4;
			player.killcount++;
			player.buff_reflect = 0;
			if (player.buffcount1 != 0) {
				player.buffcount1 = 0;
				player.attack -= player.buff_attack;  // 공격력 버프 제거
				player.buff_attack = 0;
			}
			if (player.buffcount2 != 0) {
				player.buffcount2 = 0;
				player.defense -= player.buff_defense; // 방어력 버프 제거
				player.buff_defense = 0;
			}
			if (player.buffcount3 != 0) {
				player.buffcount3 = 0;
				player.buff_reflect = 0;  // 가시갑옷 비활성화
			}
			updateQuestStatusKill();
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
			playerDyingAnimation();
			updateBattleLog("당신은 패배하였습니다...");
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			player.ending = 4;

			Situation = 0;
		}
	}
	OriginalLevel = player.level;
	// 전투가 끝난 후 대기 및 본래 화면으로 복귀
	updateBattleLog("아무 키를 눌러 맵으로 돌아가십시오.");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // 사용자 입력 대기

	if (player.level > OriginalLevel)
		updateLog("레벨 업!!");

	initializeMap(); // 맵 초기화
	displayMap(); // 이동 맵 출력
	displayPlayerStat(); //플레이어 스탯 표시
	drawPlayer(); // 플레이어 위치 출력
	displayLog();
	Sleep(200);
	player.money += 10;
	updateLog("닌자의 시체에서 엽전을 발견했습니다!");
	displayLog();
	Sleep(200);
}