#include <conio.h>
#include <time.h>
#include "battle.h"
#include "potion.h"
#include "animation.h"


int OriginalLevel;

void LevelUp()	//������
{
	if (player.exp >= EXPbar)
	{
		player.exp = player.exp - EXPbar;
		player.level++;
	}
	if (player.level >= 15)
		EXPbar = 40;
	else if (player.level >= 10)
		EXPbar = 30;
	else if (player.level >= 2)
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
			playerAttackAnimation();
			enemyAttackedAnimation();
			damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					updateBattleLog("Critical Attack!");
					damageToEnemy *= 2;
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
				enemyAttackAnimation();
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
			updateBattleLog("You defeated the enemy!");
			player.exp += 12;
			player.money += 4;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
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