#include "initmap.h"

void initializeMap()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{

			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
			{
				map[i][j] = '#';
			}
			else
			{
				map[i][j] = ' ';
			}
		}
		for (int j = MAP_WIDTH; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			if (i == 0 || i == MAP_HEIGHT - 1)
			{
				map[i][j] = '#';
			}
		}
	}
}

void initializeMapBattle()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{

			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
			{
				mapBattle[i][j] = '#';
			}
			else
			{
				mapBattle[i][j] = ' ';
			}
		}
		for (int j = MAP_WIDTH; j < MAP_WIDTH + PANEL_WIDTH; j++)
		{
			if (i == 0 || i == MAP_HEIGHT - 1)
			{
				mapBattle[i][j] = '#';
			}
		}
	}
}
