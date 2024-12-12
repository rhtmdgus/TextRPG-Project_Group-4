#include <conio.h>
#include <time.h>
#include "battle.h"
#include "potion.h"
#include "animation.h"
#include "quest.h"

int hiddenPotionCount = 0;
int OriginalLevel;

void LevelUp()	//������
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
	updateBattleLog("���� ����!!");
	int damageToEnemy;   // ������ �� ����� ����
	int damageToPlayer;  // �ݰ��� �� ����� ����
	displayBattleScreen();
	displayPlayerStat();
	displayEnemyStat(enemy);
	displayBattleLog();

	SkillAppear();

	while (enemy->hp > 0 && player.hp > 0 && Situation == 1)
	{


		char action = _getch();

		if (enemy == nullptr) {
			updateBattleLog("����: ������ ���� �����ϴ�.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp���� ���
			hppotion(); if (hiddenPotionCount == 19)
			{
				updateBattleLog("����� ���� ���ٻ������ �ߵ��Ǿ �׾����ϴ�...");
				player.ending = 5;
				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp���� ���
			mppotion();
			if (hiddenPotionCount == 19)
			{
				updateBattleLog("����� ���� ���ٻ������ �ߵ��Ǿ �׾����ϴ�...");
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
			// ���� ����

			damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					enemyAttackedAnimation(enemy);
					updateBattleLog("ġ��Ÿ ����!");
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
					updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
					displayBattleLog();
				}

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}

				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("���� �����Ͽ����ϴ�!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;
		case 'z':  //��ų 1
		case 'Z':
			hiddenPotionCount = 0;
			// ���� ����
			if (player.level < 5) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 5) {
				updateBattleLog("����� �����մϴ�!!");
				displayBattleLog();
				break;
			}

			damageToEnemy = skill1(player.attack) - enemy->defense; // ������ ������ ������ ���
			player.mp -= 5;
			updateBattleLog("��ų 1�� �ߵ��Ǿ����ϴ�!");
			if (player.job == 1) {
				updateBattleLog("��Ÿ �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 2) {
				updateBattleLog("���� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 3) {
				updateBattleLog("��â �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 4) {
				updateBattleLog("���й�ġ�� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			displayBattleLog();
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					enemyAttackedAnimation(enemy);
					updateBattleLog("ġ��Ÿ ����!");
					damageToEnemy *= 2;
				}
				else
				{
					enemyAttackedAnimation(enemy);
				}
				enemy->hp -= damageToEnemy;
				if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
					Sleep(100);
					enemyAttackedAnimation(enemy);
					enemy->hp -= 3;
					updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("���� �����Ͽ����ϴ�.!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

		case 'x':  // ��ų 2
		case 'X':
			hiddenPotionCount = 0;
			if (player.level < 10) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 10) {
				updateBattleLog("����� �����մϴ�!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("��ų 2�� �ߵ��Ǿ����ϴ�!");
			displayLog();
			// ���� ����
			if (player.job == 4) { // ���к� ��ų 2 
				player.mp -= 10;
				player.buff_defense = 5;  // ���� 5 ����
				player.defense += player.buff_defense;
				player.buffcount2 = 3;     // 3�� ����, buffcount2 �� ���к� ��ų2�� �Ҵ�
				updateBattleLog("����¼� �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(2);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else {
				damageToEnemy = skill2(player.attack) - enemy->defense; // ������ ������ ������ ���
				player.mp -= 10;
				if (player.job == 1) {
					updateBattleLog("������ �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 2) {
					updateBattleLog("���߻�� �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 3) {
					updateBattleLog("������ �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("ġ��Ÿ ����!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
						displayBattleLog();
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("���� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'c':  //��ų 3
		case 'C':
			hiddenPotionCount = 0;
			if (player.level < 15) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 20) {
				updateBattleLog("����� �����մϴ�!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("��ų 3�� �ߵ��Ǿ����ϴ�!");
			displayBattleLog();

			if (player.job == 1) { // ���� ��ų 3 ����ȭ
				player.mp -= 20;
				player.buff_attack = 10;  // ���ݷ� 10 ����
				player.attack += player.buff_attack;
				player.buffcount1 = 3;     // 3�� ����
				updateBattleLog("����ȭ �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 4) { // ���к� ��ų 3: ���ù���
				player.mp -= 20;
				player.buff_reflect = 1;    // ���ù��� Ȱ��ȭ
				player.buffcount3 = 5;      // 5�� ����, ���к� ��ų 3�� buffcount3�� �Ҵ�
				updateBattleLog("���ù��� �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 2) { // �ü� ��ų 3 ��ȭ��
				damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
				player.mp -= 20;
				player.buffcount1 = 5;
				updateBattleLog("��ȭ�� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("ġ��Ÿ ����!");
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
						updateBattleLog("��ȭ�� ���ӵ��� �����ϴ�!");
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("���� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			else if (player.job == 3) {
				damageToEnemy = skill3(player.attack) - enemy->defense; // ������ ������ ������ ���
				player.mp -= 20;
				updateBattleLog("���ֵ��� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("ġ��Ÿ ����!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("���� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
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
			hiddenPotionCount = 0;
			updateBattleLog("�����Լ� �����ƽ��ϴ�!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("�������� ������ϴ�!");
			break;

		default:
			updateBattleLog("�Ұ����� �ൿ! �ٽ� �������ּ���.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		if (player.buffcount1 > 0)
		{
			player.buffcount1--;
			if (player.buffcount1 == 0)
			{
				player.attack -= player.buff_attack;  // ���ݷ� ���� ����
				player.buff_attack = 0;
				updateBattleLog("������ ���ӽð��� �������ϴ�!");
			}
		}

		if (player.buffcount2 > 0)
		{
			player.buffcount2--;
			if (player.buffcount2 == 0)
			{
				player.defense -= player.buff_defense; // ���� ���� ����
				player.buff_defense = 0;
				updateBattleLog("����¼��� ���ӽð��� �������ϴ�!");
			}
		}
		if (player.buffcount3 > 0)
		{
			player.buffcount3--;
			if (player.buffcount3 == 0)
			{
				player.buff_reflect = 0;  // ���ð��� ��Ȱ��ȭ
				updateBattleLog("���ð����� ���� �ð��� �������ϴ�!");
			}
		}

		// ���� üũ
		if (enemy->hp <= 0) {
			enemyDyingAnimation(enemy);
			updateBattleLog("���� �����ƽ��ϴ�!");
			player.exp += 12;
			player.money += 4;
			player.killcount++;
			player.buff_reflect = 0;
			if (player.buffcount1 != 0) {
				player.buffcount1 = 0;
				player.attack -= player.buff_attack;  // ���ݷ� ���� ����
				player.buff_attack = 0;
			}
			if (player.buffcount2 != 0) {
				player.buffcount2 = 0;
				player.defense -= player.buff_defense; // ���� ���� ����
				player.buff_defense = 0;
			}
			if (player.buffcount3 != 0) {
				player.buffcount3 = 0;
				player.buff_reflect = 0;  // ���ð��� ��Ȱ��ȭ
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
			updateBattleLog("����� �й��Ͽ����ϴ�...");
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
	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("�ƹ� Ű�� ���� ������ ���ư��ʽÿ�.");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // ����� �Է� ���

	if (player.level > OriginalLevel)
		updateLog("���� ��!!");

	initializeMap(); // �� �ʱ�ȭ
	displayMap(); // �̵� �� ���
	displayPlayerStat(); //�÷��̾� ���� ǥ��
	drawPlayer(); // �÷��̾� ��ġ ���
}

// ���� ���� �Լ�
void bossbattle(Enemy* boss)
{
	updateBattleLog("��������!!");
	int damageToBoss;   // ������ �� ����� ����
	int damageToPlayer;  // �ݰ��� �� ����� ����
	displayBossBattleScreen();
	displayPlayerStat();
	displayBossStat(boss);
	displayBattleLog();
	SkillAppear();

	while (boss->hp > 0 && player.hp > 0 && Situation == 7)
	{
		char action = _getch();

		if (boss == nullptr) {
			updateBattleLog("����: ������ ������ �����ϴ�");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp���� ���
			hppotion();
			if (hiddenPotionCount == 19)
			{
				updateBattleLog("����� ���� ���ٻ������ �ߵ��Ǿ �׾����ϴ�...");
				player.ending = 5;

				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp���� ���
			mppotion();
			if (hiddenPotionCount == 19)
			{
				updateBattleLog("����� ���� ���ٻ������ �ߵ��Ǿ �׾����ϴ�...");
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
			// ���� ����

			damageToBoss = player.attack - boss->defense; // ������ ������ ������ ���
			if (damageToBoss > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					BossDamaged(boss);
					updateBattleLog("ġ��Ÿ ����!");
					damageToBoss *= 2;
				}
				else
				{
					playerAttackAnimation();
					BossDamaged(boss);
				}
				boss->hp -= damageToBoss;
				if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
					Sleep(100);
					BossDamaged(boss);
					boss->hp -= 3;
					updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
				if (boss->hp <= 0)
					boss->hp = 0;
				updateBattleLog("�� ����� �����Ͽ����ϴ�!");
				displayPlayerStat();
				displayBossStat(boss);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("����� ������ �ʹ� ���մϴ�!");
				displayPlayerStat();
				displayBossStat(boss);
				Sleep(100);
				displayBattleLog();

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}

			// �� �ݰ�
			if (boss->hp > 0) {
				BossAttack(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // ������ ������ ������ ���
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = boss->attack; // �ݻ� ������ ���
					boss->hp -= reflectedDamage;
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("�� ������� ���� ���Ͽ����ϴ�!");
					displayPlayerStat();
					displayBossStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'z':  //��ų 1
		case 'Z':
			hiddenPotionCount = 0;
			// ���� ����
			if (player.level < 5) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 5) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}

			damageToBoss = skill1(player.attack) - boss->defense; // ������ ������ ������ ���
			player.mp -= 5;
			updateBattleLog("��ų 1�� �ߵ��Ǿ����ϴ�!");
			if (player.job == 1) {
				updateBattleLog("��Ÿ �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 2) {
				updateBattleLog("���� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 3) {
				updateBattleLog("��â �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 4) {
				updateBattleLog("���й�ġ�� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			displayBattleLog();
			if (damageToBoss > 0) {
				if (Crit() == 1)
				{
					BossDamaged(boss);
					updateBattleLog("ġ��Ÿ ����!");
					damageToBoss *= 2;
				}
				else
				{
					BossDamaged(boss);
				}
				boss->hp -= damageToBoss;
				if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
					Sleep(100);
					BossDamaged(boss);
					boss->hp -= 3;
					updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
				if (boss->hp <= 0)
					boss->hp = 0;
				updateBattleLog("�� ����� �����Ͽ����ϴ�!");
				displayPlayerStat();
				displayEnemyStat(boss);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("����� ������ �ʹ� ���մϴ�!");
				displayPlayerStat();
				displayEnemyStat(boss);
				Sleep(100);
				displayBattleLog();

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}

			// �� �ݰ�
			if (boss->hp > 0) {
				enemyAttackAnimation(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // ������ ������ ������ ���
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = boss->attack; // �ݻ� ������ ���
					boss->hp -= reflectedDamage;
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("�� ������� ���� ���Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

		case 'x':  // ��ų 2
		case 'X':
			hiddenPotionCount = 0;
			if (player.level < 10) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 10) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("��ų 2�� �ߵ��Ǿ����ϴ�!");
			displayLog();
			// ���� ����
			if (player.job == 4) { // ���к� ��ų 2 
				player.mp -= 10;
				player.buff_defense = 5;  // ���� 5 ����
				player.defense += player.buff_defense;
				player.buffcount2 = 3;     // 3�� ����, buffcount2 �� ���к� ��ų2�� �Ҵ�
				updateBattleLog("����¼� �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(2);

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else {
				damageToBoss = skill2(player.attack) - boss->defense; // ������ ������ ������ ���
				player.mp -= 10;
				if (player.job == 1) {
					updateBattleLog("������ �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 2) {
					updateBattleLog("���߻�� �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 3) {
					updateBattleLog("������ �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				if (damageToBoss > 0) {
					if (Crit() == 1)
					{
						BossDamaged(boss);
						updateBattleLog("ġ���� ����!");
						damageToBoss *= 2;
					}
					else
					{
						BossDamaged(boss);
					}
					boss->hp -= damageToBoss;
					if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
						displayBattleLog();
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (boss->hp <= 0)
						boss->hp = 0;
					updateBattleLog("�� ����� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();

					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
				}
			}

			// �� �ݰ�
			if (boss->hp > 0) {
				enemyAttackAnimation(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // ������ ������ ������ ���
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = boss->attack; // �ݻ� ������ ���
					boss->hp -= reflectedDamage;
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("�� ������� ���� ���Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'c':  //��ų 3
		case 'C':
			hiddenPotionCount = 0;
			if (player.level < 15) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 20) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("��ų 3�� �ߵ��Ǿ����ϴ�!");
			displayBattleLog();

			if (player.job == 1) { // ���� ��ų 3 ����ȭ
				player.mp -= 20;
				player.buff_attack = 10;  // ���ݷ� 10 ����
				player.attack += player.buff_attack;
				player.buffcount1 = 3;     // 3�� ����
				updateBattleLog("����ȭ �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 4) { // ���к� ��ų 3: ���ù���
				player.mp -= 20;
				player.buff_reflect = 1;    // ���ù��� Ȱ��ȭ
				player.buffcount3 = 5;      // 5�� ����, ���к� ��ų 3�� buffcount3�� �Ҵ�
				updateBattleLog("���ù��� �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						BossDamaged(boss);
						boss->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 2) { // �ü� ��ų 3 ��ȭ��
				damageToBoss = player.attack - boss->defense; // ������ ������ ������ ���
				player.mp -= 20;
				player.buffcount1 = 5;
				updateBattleLog("��ȭ�� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToBoss > 0) {
					if (Crit() == 1)
					{
						BossDamaged(boss);
						updateBattleLog("ġ��Ÿ ����!");
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
						updateBattleLog("��ȭ�� ���ӵ��� �����ϴ�!");
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (boss->hp <= 0)
						boss->hp = 0;
					updateBattleLog("�� ����� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();

					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
				}
			}
			else if (player.job == 3) {
				damageToBoss = skill3(player.attack) - boss->defense; // ������ ������ ������ ���
				player.mp -= 20;
				updateBattleLog("���ֵ��� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToBoss > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(boss);
						updateBattleLog("ġ��Ÿ ����!");
						damageToBoss *= 2;
					}
					else
					{
						enemyAttackedAnimation(boss);
					}
					boss->hp -= damageToBoss;
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (boss->hp <= 0)
						boss->hp = 0;
					updateBattleLog("�� ����� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();

					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							BossDamaged(boss);
							boss->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
				}

			}
			// �� �ݰ�
			if (boss->hp > 0) {
				enemyAttackAnimation(boss);
				playerAttackedAnimation();
				damageToPlayer = boss->attack - player.defense; // ������ ������ ������ ���
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = boss->attack; // �ݻ� ������ ���
					boss->hp -= reflectedDamage; // Ʈ�絥����
					if (boss->hp < 0) boss->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayBossStat(boss);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("�� ������� ���� ���Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(boss);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;




			//���� �������� ����
		case 'r':
		case 'R':
			hiddenPotionCount = 0;
			updateBattleLog("�� ������Լ� �����ƽ��ϴ�!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			updateLog("�������� ������ϴ�!");
			break;

		default:
			updateBattleLog("�Ұ����� �ൿ! �ٽ� �������ּ���.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		if (player.buffcount1 > 0)
		{
			player.buffcount1--;
			if (player.buffcount1 == 0)
			{
				player.attack -= player.buff_attack;  // ���ݷ� ���� ����
				player.buff_attack = 0;
				updateBattleLog("������ ���ӽð��� �������ϴ�!");
			}
		}

		if (player.buffcount2 > 0)
		{
			player.buffcount2--;
			if (player.buffcount2 == 0)
			{
				player.defense -= player.buff_defense; // ���� ���� ����
				player.buff_defense = 0;
				updateBattleLog("����¼��� ���ӽð��� �������ϴ�!");
			}
		}
		if (player.buffcount3 > 0)
		{
			player.buffcount3--;
			if (player.buffcount3 == 0)
			{
				player.buff_reflect = 0;  // ���ð��� ��Ȱ��ȭ
				updateBattleLog("���ð����� ���� �ð��� �������ϴ�!");
			}
		}





		// ���� üũ
		if (boss->hp <= 0) {
			BossDying(boss);
			updateBattleLog("�� ����� �����ƽ��ϴ�!");
			updateQuestStatusItem(6);
			player.exp += 30;
			player.money += 10;
			player.questitem1 = 1;
			checkboss1 = 1;
			checkboss2 = 1;
			checkboss3 = 1;
			if (player.buffcount1 != 0) {
				player.buffcount1 = 0;
				player.attack -= player.buff_attack;  // ���ݷ� ���� ����
				player.buff_attack = 0;
			}
			if (player.buffcount2 != 0) {
				player.buffcount2 = 0;
				player.defense -= player.buff_defense; // ���� ���� ����
				player.buff_defense = 0;
			}
			if (player.buffcount3 != 0) {
				player.buffcount3 = 0;
				player.buff_reflect = 0;  // ���ð��� ��Ȱ��ȭ
			}
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			Situation = 0;
		}
		else if (player.hp <= 0) {
			playerDyingAnimation();
			updateBattleLog("����� �й��Ͽ����ϴ�...");
			displayPlayerStat();
			displayBossStat(boss);
			Sleep(100);
			displayBattleLog();
			player.ending = 4;

			Situation = 0;
		}
	}





	OriginalLevel = player.level;
	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("�ƹ� Ű�� ���� ������ ���ư��ʽÿ�.");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // ����� �Է� ���

	if (player.level > OriginalLevel)
		updateLog("���� ��!!");

	initializeMap(); // �� �ʱ�ȭ
	displayMap(); // �̵� �� ���
	displayPlayerStat(); //�÷��̾� ���� ǥ��
	drawPlayer(); // �÷��̾� ��ġ ���
}

// ������ī���� ���� �Լ�
void battleRand(Enemy* enemy)
{
	updateBattleLog("���� ����!!");
	int damageToEnemy;   // ������ �� ����� ����
	int damageToPlayer;  // �ݰ��� �� ����� ����
	displayBattleScreen();
	displayPlayerStat();
	displayEnemyStat(enemy);
	displayBattleLog();

	SkillAppear();

	while (enemy->hp > 0 && player.hp > 0 && Situation == 1)
	{


		char action = _getch();

		if (enemy == nullptr) {
			updateBattleLog("����: ������ ���� �����ϴ�.");
			displayBattleLog();
			return;
		}

		switch (action)
		{
		case '1'://           hp���� ���
			hppotion();
			if (hiddenPotionCount == 19)
			{
				
				updateBattleLog("����� ���� ���ٻ������ �ߵ��Ǿ �׾����ϴ�...");
				player.ending = 5;

				displayLog();
			}
			hiddenPotionCount += 1;
			displayPlayerStat();
			Sleep(100);
			displayBattleLog();
			break;

		case '2'://           mp���� ���

			mppotion();
			if (hiddenPotionCount == 19)
			{
				
				updateBattleLog("����� ���� ���ٻ������ �ߵ��Ǿ �׾����ϴ�...");
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
			// ���� ����

			damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					playerCritAnimation();
					enemyAttackedAnimation(enemy);
					updateBattleLog("ġ��Ÿ ����!");
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
					updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
					displayBattleLog();
				}

				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}

				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("���� �����Ͽ����ϴ�!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;
		case 'z':  //��ų 1
		case 'Z':
			hiddenPotionCount = 0;
			// ���� ����
			if (player.level < 5) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 5) {
				updateBattleLog("����� �����մϴ�!!");
				displayBattleLog();
				break;
			}

			damageToEnemy = skill1(player.attack) - enemy->defense; // ������ ������ ������ ���
			player.mp -= 5;
			updateBattleLog("��ų 1�� �ߵ��Ǿ����ϴ�!");
			if (player.job == 1) {
				updateBattleLog("��Ÿ �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 2) {
				updateBattleLog("���� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 3) {
				updateBattleLog("��â �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			else if (player.job == 4) {
				updateBattleLog("���й�ġ�� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(1);
			}
			displayBattleLog();
			if (damageToEnemy > 0) {
				if (Crit() == 1)
				{
					enemyAttackedAnimation(enemy);
					updateBattleLog("ġ��Ÿ ����!");
					damageToEnemy *= 2;
				}
				else
				{
					enemyAttackedAnimation(enemy);
				}
				enemy->hp -= damageToEnemy;
				if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
					Sleep(100);
					enemyAttackedAnimation(enemy);
					enemy->hp -= 3;
					updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
					displayBattleLog();
				}
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
				if (enemy->hp <= 0)
					enemy->hp = 0;
				updateBattleLog("���� �����Ͽ����ϴ�.!");
				displayPlayerStat();
				displayEnemyStat(enemy);
				Sleep(100);
				displayBattleLog();
			}
			else {
				updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;

		case 'x':  // ��ų 2
		case 'X':
			hiddenPotionCount = 0;
			if (player.level < 10) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 10) {
				updateBattleLog("����� �����մϴ�!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("��ų 2�� �ߵ��Ǿ����ϴ�!");
			displayLog();
			// ���� ����
			if (player.job == 4) { // ���к� ��ų 2 
				player.mp -= 10;
				player.buff_defense = 5;  // ���� 5 ����
				player.defense += player.buff_defense;
				player.buffcount2 = 3;     // 3�� ����, buffcount2 �� ���к� ��ų2�� �Ҵ�
				updateBattleLog("����¼� �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(2);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else {
				damageToEnemy = skill2(player.attack) - enemy->defense; // ������ ������ ������ ���
				player.mp -= 10;
				if (player.job == 1) {
					updateBattleLog("������ �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 2) {
					updateBattleLog("���߻�� �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				else if (player.job == 3) {
					updateBattleLog("������ �ߵ�!");
					displayBattleLog();
					playerSkillAnimation(2);
				}
				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("ġ��Ÿ ����!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.job == 2 && player.buffcount1 > 0) {    // �ü� ��ų 3 ��Ʈ�� ����
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("��ȭ���� ���ӵ������� �����ϴ�!");
						displayBattleLog();
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("���� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			break;


		case 'c':  //��ų 3
		case 'C':
			hiddenPotionCount = 0;
			if (player.level < 15) {
				updateBattleLog("������ �����մϴ�!!");
				displayBattleLog();
				break;
			}
			if (player.mp < 20) {
				updateBattleLog("����� �����մϴ�!!");
				displayBattleLog();
				break;
			}

			updateBattleLog("��ų 3�� �ߵ��Ǿ����ϴ�!");
			displayBattleLog();

			if (player.job == 1) { // ���� ��ų 3 ����ȭ
				player.mp -= 20;
				player.buff_attack = 10;  // ���ݷ� 10 ����
				player.attack += player.buff_attack;
				player.buffcount1 = 3;     // 3�� ����
				updateBattleLog("����ȭ �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 4) { // ���к� ��ų 3: ���ù���
				player.mp -= 20;
				player.buff_reflect = 1;    // ���ù��� Ȱ��ȭ
				player.buffcount3 = 5;      // 5�� ����, ���к� ��ų 3�� buffcount3�� �Ҵ�
				updateBattleLog("���ù��� �ߵ�!");
				displayBattleLog();
				displayPlayerStat();
				playerSkillAnimation(3);
				if (player.RRelationship >= 50) {
					if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 3;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 2;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
					else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
						Sleep(100);
						enemyAttackedAnimation(enemy);
						enemy->hp -= 1;
						updateBattleLog("�Ǻ� ������ �߰� ����!");
						displayBattleLog();
					}
				}
			}
			else if (player.job == 2) { // �ü� ��ų 3 ��ȭ��
				damageToEnemy = player.attack - enemy->defense; // ������ ������ ������ ���
				player.mp -= 20;
				player.buffcount1 = 5;
				updateBattleLog("��ȭ�� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("ġ��Ÿ ����!");
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
						updateBattleLog("��ȭ�� ���ӵ��� �����ϴ�!");
					}
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("���� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
			}
			else if (player.job == 3) {
				damageToEnemy = skill3(player.attack) - enemy->defense; // ������ ������ ������ ���
				player.mp -= 20;
				updateBattleLog("���ֵ��� �ߵ�!");
				displayBattleLog();
				playerSkillAnimation(3);

				if (damageToEnemy > 0) {
					if (Crit() == 1)
					{
						enemyAttackedAnimation(enemy);
						updateBattleLog("ġ��Ÿ ����!");
						damageToEnemy *= 2;
					}
					else
					{
						enemyAttackedAnimation(enemy);
					}
					enemy->hp -= damageToEnemy;
					if (player.RRelationship >= 50) {
						if (player.RRelationship >= 150) {// �Ǻ� ���赵 150�̻��϶� 3�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 3;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else if (player.RRelationship >= 100) {// �Ǻ� ���赵 100�̻��϶� 2�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 2;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
						else {                                 // �Ǻ� ���赵 50�̻��϶� 1�� �߰�
							Sleep(100);
							enemyAttackedAnimation(enemy);
							enemy->hp -= 1;
							updateBattleLog("�Ǻ� ������ �߰� ����!");
							displayBattleLog();
						}
					}
					if (enemy->hp <= 0)
						enemy->hp = 0;
					updateBattleLog("���� �����Ͽ����ϴ�!");
					displayPlayerStat();
					displayEnemyStat(enemy);
					Sleep(100);
					displayBattleLog();
				}
				else {
					updateBattleLog("����� ������ �ʹ� ���մϴ�!");
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
				if (player.buff_reflect == 1) {  // ���ð��� �ݻ� ����
					int reflectedDamage = enemy->attack; // �ݻ� ������ ���
					enemy->hp -= reflectedDamage;
					if (enemy->hp < 0) enemy->hp = 0;
					updateBattleLog("���ð������� ������ �������� �ݻ��߽��ϴ�!");
					displayBattleLog();
					displayEnemyStat(enemy);
				}
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					if (player.hp <= 0)
						player.hp = 0;
					updateBattleLog("������ ���ݴ��Ͽ����ϴ�.!");
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
			hiddenPotionCount = 0;
			updateBattleLog("�����Լ� �����ƽ��ϴ�!");
			Situation = 0;
			player.pos = previousPos;
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			updateLog("�������� ������ϴ�!");
			break;

		default:
			updateBattleLog("�Ұ����� �ൿ! �ٽ� �������ּ���.");
			Sleep(100);
			displayBattleLog();
			break;
		}

		if (player.buffcount1 > 0)
		{
			player.buffcount1--;
			if (player.buffcount1 == 0)
			{
				player.attack -= player.buff_attack;  // ���ݷ� ���� ����
				player.buff_attack = 0;
				updateBattleLog("������ ���ӽð��� �������ϴ�!");
			}
		}

		if (player.buffcount2 > 0)
		{
			player.buffcount2--;
			if (player.buffcount2 == 0)
			{
				player.defense -= player.buff_defense; // ���� ���� ����
				player.buff_defense = 0;
				updateBattleLog("����¼��� ���ӽð��� �������ϴ�!");
			}
		}
		if (player.buffcount3 > 0)
		{
			player.buffcount3--;
			if (player.buffcount3 == 0)
			{
				player.buff_reflect = 0;  // ���ð��� ��Ȱ��ȭ
				updateBattleLog("���ð����� ���� �ð��� �������ϴ�!");
			}
		}

		// ���� üũ
		if (enemy->hp <= 0) {
			enemyDyingAnimation(enemy);
			updateBattleLog("���� �����ƽ��ϴ�!");
			player.exp += 12;
			player.money += 4;
			player.killcount++;
			player.buff_reflect = 0;
			if (player.buffcount1 != 0) {
				player.buffcount1 = 0;
				player.attack -= player.buff_attack;  // ���ݷ� ���� ����
				player.buff_attack = 0;
			}
			if (player.buffcount2 != 0) {
				player.buffcount2 = 0;
				player.defense -= player.buff_defense; // ���� ���� ����
				player.buff_defense = 0;
			}
			if (player.buffcount3 != 0) {
				player.buffcount3 = 0;
				player.buff_reflect = 0;  // ���ð��� ��Ȱ��ȭ
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
			updateBattleLog("����� �й��Ͽ����ϴ�...");
			displayPlayerStat();
			displayEnemyStat(enemy);
			Sleep(100);
			displayBattleLog();
			player.ending = 4;

			Situation = 0;
		}
	}
	OriginalLevel = player.level;
	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("�ƹ� Ű�� ���� ������ ���ư��ʽÿ�.");
	LevelUp();
	displayPlayerStat();
	displayBattleLog();
	_getch();  // ����� �Է� ���

	if (player.level > OriginalLevel)
		updateLog("���� ��!!");

	initializeMap(); // �� �ʱ�ȭ
	displayMap(); // �̵� �� ���
	displayPlayerStat(); //�÷��̾� ���� ǥ��
	drawPlayer(); // �÷��̾� ��ġ ���
	displayLog();
	Sleep(200);
	player.money += 10;
	updateLog("������ ��ü���� ������ �߰��߽��ϴ�!");
	displayLog();
	Sleep(200);
}