#include <conio.h>
#include <time.h>
#include "battle.h"
#include "potion.h"
#include "animation.h"
#include "quest.h"
#include "skill.h"

int OriginalLevel;

void LevelUp()	//������
{
	while (player.exp >= EXPbar)
	{
		player.exp = player.exp - EXPbar;
		player.level++;
		maxhp++;
		maxmp++;
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
int Crit()	//ũ��Ƽ�� ��Ʈ
{
	// ���� �õ� �ʱ�ȭ
	srand((unsigned int)time(NULL));
	// accuracy�� ���� ġ��Ÿ Ȯ�� ��� (5%�� ����)
	int criticalChance = player.accuracy * 5; // accuracy�� 0�� ���� 0%, 1�� ���� 5%...

	// Ȯ���� 0�� 1 ���̷� ��ȯ
	int probability = rand() % 100;

	// ġ��Ÿ �߻� ���� ����
	if (probability < criticalChance) {
		return 1; // ġ��Ÿ �߻�
	}
	else {
		return 0; // ġ��Ÿ �̹߻�
	}
}


// ���� �Լ�
void battle(Enemy* enemy)
{
	updateBattleLog("Battle start!!");
	int damageToEnemy;   // ������ �� ����� ����
	int damageToPlayer;  // �ݰ��� �� ����� ����
	displayBattleScreen();
	displayPlayerStat();
	displayEnemyStat(enemy);
	displayBattleLog();


	SkillAppear();  //                                                                      ����!



	while (enemy->hp > 0 && player.hp > 0 && Situation == 1)
	{
		if (player.buffcount1 > 0) {
			player.buffcount1--;
			if (player.buffcount1 == 0) {
				player.attack -= player.buff_attack;  // ���ݷ� ���� ����
				player.buff_attack = 0;
				updateBattleLog("������ ���ӽð��� �������ϴ�!");
			}
		}

		if (player.buffcount2 > 0) {
			player.buffcount2--;
			if (player.buffcount2 == 0) {
				player.defense -= player.buff_defense; // ���� ���� ����
				player.buff_defense = 0;
				updateBattleLog("����¼��� ���ӽð��� �������ϴ�!");
			}
		}
		if (player.buffcount3 > 0) {
			player.buffcount3--;
			if (player.buffcount3 == 0) {
				player.buff_reflect = 0;  // ���ð��� ��Ȱ��ȭ
				updateBattleLog("���ð����� ���� �ð��� �������ϴ�!");
			}
		}

		char action = _getch();

		if (enemy == nullptr) {
			updateBattleLog("Error: No enemy to battle.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp���� ���
			hppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp���� ���
			mppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			// ���� ����
			
			damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
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
				if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
					Sleep(100);
					enemyAttackedAnimation(enemy);
					enemy->hp -= 3;
				}
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

			// �� �ݰ�
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // ������ ������ ������ ���
				if (damageToPlayer > 0) {
					if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
						int reflectedDamage = damageToPlayer; // �ݻ� ������ ���
						enemy->hp -= reflectedDamage;
						if (enemy->hp < 0) enemy->hp = 0;
						updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					}
					else
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
		case 'z':  //��ų 1
		case 'Z':
			// ���� ����
			if (player.level < 5) {
				updateBattleLog("������ �����մϴ�!!");
				displayLog();
				break;
			}
			if (player.mp < 5) {
				updateBattleLog("������ �����մϴ�!!");
				displayLog();
				break;
			}

			damageToEnemy = skill1(player.attack) - enemy->defense; // ������ ������ ������ ���
			player.mp -= 5;

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

			// �� �ݰ�
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // ������ ������ ������ ���
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

		case 'x':  // ��ų 2
		case 'X':
			if (player.level < 10) {
				updateBattleLog("������ �����մϴ�!!");
				displayLog();
				break;
			}
			if (player.mp < 10) {
				updateBattleLog("������ �����մϴ�!!");
				displayLog();
				break;
			}
			// ���� ����
			if (player.job == 4 ) { // ���к� ��ų 2 
				player.mp -= 10;
				player.buff_defense += 5;  // ���� 5 ����
				player.buffcount2 = 3;     // 3�� ����, buffcount2 �� ���к� ��ų2�� �Ҵ�
				updateBattleLog("����¼� �ߵ�!");
				displayPlayerStat();
			}
			else  {
				damageToEnemy = skill2(player.attack) - enemy->defense; // ������ ������ ������ ���
				player.mp -= 10;

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
			}

			// �� �ݰ�
			if (enemy->hp > 0) {
				enemyAttackAnimation(enemy);
				playerAttackedAnimation();
				damageToPlayer = enemy->attack - player.defense; // ������ ������ ������ ���
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


		case 'c':  //��ų 3
		case 'C':
			if (player.level < 15) {
				updateBattleLog("������ �����մϴ�!!");
				displayLog();
				break;
			}
			if (player.mp < 20) {
				updateBattleLog("������ �����մϴ�!!");
				displayLog();
				break;
			}

			if (player.job == 1) { // ���� ��ų 3 ����ȭ
				player.mp -= 20;
				player.buff_attack += 10;  // ���ݷ� 10 ����
				player.buffcount1 = 3;     // 3�� ����
				updateBattleLog("����ȭ �ߵ�!");
				displayPlayerStat();
			}
			else if (player.job == 4) { // ���к� ��ų 3: ���ù���
				player.mp -= 20;
				player.buff_reflect = 1;    // ���ù��� Ȱ��ȭ
				player.buffcount3 = 5;      // 5�� ����, ���к� ��ų 3�� buffcount3�� �Ҵ�
				updateBattleLog("���ù��� �ߵ�!");
				displayPlayerStat();
			}
			else if (player.job == 2) { // �ü� ��ų 3 ��ȭ��
				damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
				player.mp -= 20;
				player.buffcount1 = 5;


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
					if (player.buffcount1 > 0) {
						Sleep(100);
						enemy->hp -= 3;
						enemyAttackedAnimation(enemy);
					}
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
			}
			else if (player.job == 3) {
				damageToEnemy = skill3(player.attack) - enemy->defense; // ������ ������ ������ ���
				player.mp -= 20;

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
			}
			break;



		//���� �������� ����
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

		// ���� üũ
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
	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("Press any key to return to the main screen...");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // ����� �Է� ���

	if (player.level > OriginalLevel)
		updateLog("Level up!!");

	initializeMap(); // �� �ʱ�ȭ
	displayMap(); // �̵� �� ���
	displayPlayerStat(); //�÷��̾� ���� ǥ��
	drawPlayer(); // �÷��̾� ��ġ ���
}

// ���� ���� �Լ�
void bossbattle(Enemy* boss)
{
	updateBattleLog("Battle start!!");
	int damageToBoss;   // ������ �� ����� ����
	int damageToPlayer;  // �ݰ��� �� ����� ����
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
		case '1'://           hp���� ���
			hppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp���� ���
			mppotion();
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case 'a':
		case 'A':
			// ���� ����
			
			damageToBoss = player.attack - boss->defense; // ������ ������ ������ ���
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

			// �� �ݰ�
			if (boss->hp > 0) {
				BossAttack(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // ������ ������ ������ ���
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

			//���� �������� ����
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

		// ���� üũ
		if (boss->hp <= 0) {
			BossDying(boss);
			updateBattleLog("You defeated the boss!");
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
	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("Press any key to return to the main screen...");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // ����� �Է� ���

	if (player.level > OriginalLevel)
		updateLog("Level up!!");

	initializeMap(); // �� �ʱ�ȭ
	displayMap(); // �̵� �� ���
	displayPlayerStat(); //�÷��̾� ���� ǥ��
	drawPlayer(); // �÷��̾� ��ġ ���
}