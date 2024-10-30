#include <stdio.h>
#pragma warning(disable:4996)
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAP_WIDTH 100
#define MAP_HEIGHT 30
#define PANEL_WIDTH 30

typedef struct {
	int x;
	int y;
} Position;

typedef struct {
	int hp;
	int strength;
	int endurance;
	int intelligence;
	Position pos;
} Player;

Player player = { 10, 15, 8, 5, {1, 1} };
char map[MAP_HEIGHT][MAP_WIDTH + PANEL_WIDTH];
char logMessage[3][40] = { "", "", "" };

void initializeMap() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
				map[i][j] = '#';
			}
			else {
				map[i][j] = ' ';
			}
		}
		for (int j = MAP_WIDTH; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			if (i == 0 || i == MAP_HEIGHT - 1) {
				map[i][j] = '#';
			}
		}
	}
	map[player.pos.y][player.pos.x] = 'P';
}

void displayMap() {
	system("cls");
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH + PANEL_WIDTH; j++) {
			printf("%c", map[i][j]);
		}

		if (i == 1) printf("  HP: %d", player.hp);
		if (i == 2) printf("  Strength: %d", player.strength);
		if (i == 3) printf("  Endurance: %d", player.endurance);
		if (i == 4) printf("  Intelligence: %d", player.intelligence);

		printf("\n");
	}

	printf("=========== Log ===========\n");
	for (int i = 0; i < 3; i++) {
		printf("%s\n", logMessage[i]);
	}
}

void updateLog(const char* message) {
	for (int i = 2; i > 0; i--) {
		snprintf(logMessage[i], sizeof(logMessage[i]), "%s", logMessage[i - 1]);
	}
	snprintf(logMessage[0], sizeof(logMessage[0]), "%s", message);
}

void movePlayer(char direction) {
	map[player.pos.y][player.pos.x] = ' ';
	if (direction == 'w' && player.pos.y > 1) player.pos.y--;
	else if (direction == 's' && player.pos.y < MAP_HEIGHT - 2) player.pos.y++;
	else if (direction == 'a' && player.pos.x > 1) player.pos.x--;
	else if (direction == 'd' && player.pos.x < MAP_WIDTH - 2) player.pos.x++;

	if (map[player.pos.y][player.pos.x] == 'E') {
		updateLog("You encountered an enemy!");
	}
	else if (map[player.pos.y][player.pos.x] == 'P') {
		player.hp += 5;
		updateLog("You found a potion! HP +5");
	}

	map[player.pos.y][player.pos.x] = 'P';
}

int main() {
	initializeMap();
	updateLog("Game started.");

	while (1) {
		displayMap();
		char input = getch();
		movePlayer(input);
	}
	return 0;
}
