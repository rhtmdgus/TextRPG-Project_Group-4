#include "selectmap.h"


void map1_0()
{

	//두꺼운벽부분

	for (int i = 1; i < 35; i++) {
		map[15][i] = '#';
		map[16][i] = '#';
	}

	for (int i = 1; i < 13; i++) {
		map[i][33] = '#';
		map[i][34] = '#';
	}


	for (int i = 5; i < 30; i++) {
		map[i][55] = '#';
		map[i][56] = '#';
	}

	for (int i = 1; i < 20; i++) {
		map[i][80] = '#';
		map[i][81] = '#';
	}

	//집
	for (int i = 25; i < 30; i++) {
		map[i][6] = '#';
		map[i][15] = '#';
	}

	map[13][34] = '#';
}

void map1_1()
{
	//두꺼운 벽 부분
	for (int i = 1; i < 70; i++) {
		map[10][i] = '#';
		map[11][i] = '#';
	}
	for (int i = 30; i < 80; i++) {
		map[20][i] = '#';
		map[21][i] = '#';
	}
	for (int i = 10; i < 20; i++) {
		map[i][80] = '#';
		map[i][81] = '#';
	}
	for (int i = 20; i < 30; i++) {
		map[i][55] = '#';
		map[i][56] = '#';
	}

}


void map1_2() {
	for (int i = 5; i < 15; i++) {
		map[i][20] = '#';
		map[i][21] = '#';
	}

	for (int i = 1; i < 70; i++) {
		map[10][i] = '#';
		map[11][i] = '#';
	}

	for (int i = 20; i < 30; i++) {
		map[i][70] = '#';
		map[i][71] = '#';
	}

	for (int i = 25; i < 80; i++) {
		map[15][i] = '#';
		map[16][i] = '#';
	}
}



void map1_3() {
	for (int i = 5; i < 25; i++) {
		map[i][10] = '#';
		map[i][11] = '#';
	}

	for (int i = 10; i < 90; i++) {
		map[15][i] = '#';
		map[16][i] = '#';
	}

	for (int i = 20; i < 30; i++) {
		map[i][45] = '#';
		map[i][46] = '#';
	}

	for (int i = 1; i < 60; i++) {
		map[5][i] = '#';
		map[6][i] = '#';
	}
}

void map1_4() {
	for (int i = 5; i < 25; i++) {
		map[i][10] = '#';
		map[i][11] = '#';
	}
	for (int i = 10; i < 90; i++) {
		map[15][i] = '#';
		map[16][i] = '#';
	}
	for (int i = 10; i < 20; i++) {
		map[i][45] = '#';
		map[i][46] = '#';
	}
	for (int i = 1; i < 60; i++) {
		map[5][i] = '#';
		map[6][i] = '#';
	}
	for (int i = 20; i < 29; i++) {
		map[i][80] = '#';
		map[i][81] = '#';
	}
	for (int i = 60; i < 80; i++) {
		map[25][i] = '#';
		map[26][i] = '#';
	}
}



void map1_5() {
	for (int i = 1; i < 25; i++) {
		map[i][30] = '#';
		map[i][31] = '#';
	}
	for (int i = 40; i < 70; i++) {
		map[20][i] = '#';
		map[21][i] = '#';
	}
	for (int i = 5; i < 25; i++) {
		map[i][50] = '#';
		map[i][51] = '#';
	}
	for (int i = 15; i < 30; i++) {
		map[i][70] = '#';
		map[i][71] = '#';
	}
	for (int i = 1; i < 30; i++) {
		map[28][i] = '#';
		map[29][i] = '#';
	}
}


void map1_10() // 성 안으로 들어가는 맵
{
	for (int i = 10; i < 25; i++) {
		for (int j = 1; j < 40; j++) {
			map[i][j] = '#';
		}
	}

	for (int i = 1; i < 36; i++) {
		map[6][i] = '#';
	}

	map[6][36] = '#';
	map[7][37] = '#';
	map[8][38] = '#';
	map[9][39] = '#';


	for (int i = 10; i < 25; i++) {
		for (int j = 50; j < 100; j++) {
			map[i][j] = '#';
		}

	}

	for (int i = 55; i < 100; i++) {
		map[6][i] = '#';
	}

	map[6][54] = '#';
	map[7][53] = '#';
	map[8][52] = '#';
	map[9][51] = '#';

}






void map1_11() // 관군 퀘스트맵 ( 왜구 보급로 차단 )
{
	//두꺼운 벽 부분
	for (int i = 1; i < 20; i++) {
		map[i][65] = '#';
		map[i][66] = '#';
	}

	for (int i = 22; i < 30; i++) {
		map[i][65] = '#';
		map[i][66] = '#';
	}


	for (int i = 8; i < 30; i++) {
		for (int j = 1; j < 50; j++) {
			map[i][j] = '#';

		}

	}

}


