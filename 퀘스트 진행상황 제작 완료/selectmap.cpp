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