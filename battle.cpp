#include "battle.h"
#include <conio.h>

// ���� �Լ�
void battle()
{
	updateBattleLog("Battle start!!");
	int damageToEnemy;   // ������ �� ����� ����
	int damageToPlayer;  // �ݰ��� �� ����� ����

	while (Jap1.hp > 0 && player.hp > 0)
	{
		displayBattleScreen();
		char action = _getch();

		switch (action)
		{
		case 'a':
		case 'A':
			// ���� ����
			damageToEnemy = player.attack - Jap1.defense; // ������ ������ ������ ���
			if (damageToEnemy > 0) {
				Jap1.hp -= damageToEnemy;
				updateBattleLog("You attacked the enemy!");
			}
			else {
				updateBattleLog("Your attack was too weak!");
			}

			// �� �ݰ�
			if (Jap1.hp > 0) {
				damageToPlayer = Jap1.attack - player.defense; // ������ ������ ������ ���
				if (damageToPlayer > 0) {
					player.hp -= damageToPlayer;
					updateBattleLog("The enemy attacked you!");
				}
			}
			break;

		case 'r':
		case 'R':
			updateBattleLog("You ran away from the enemy!");
			Jap1.hp = 0; // �� HP�� 0���� �����Ͽ� ���� ����
			break;

		default:
			updateBattleLog("Invalid action! Choose again.");
			break;
		}

		// ���� üũ
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

	// ������ ���� �� ��� �� ���� ȭ������ ����
	updateBattleLog("Press any key to return to the main screen...");
	displayBattleScreen();
	_getch();  // ����� �Է� ���

	initializeMap(); // �� �ʱ�ȭ
	displayMap(); // �̵� �� ���
	drawPlayer(); // �÷��̾� ��ġ ���
}