#include "LevelMap.h"

/*
 * when making a map, remember:
 * 0 = empty space, 1 = blocked/occupied space
 */

LevelMap::LevelMap(int map[LEVEL1_MAP_HEIGHT][LEVEL1_MAP_WIDTH])
{
	//Allocate memory for the level map
	m_map = new int* [LEVEL1_MAP_HEIGHT];
	for (unsigned int i = 0; i < LEVEL1_MAP_HEIGHT; i++)
	{
		m_map[i] = new int[LEVEL1_MAP_WIDTH];
	}

	//Populate the array
	for (unsigned int i = 0; i < LEVEL1_MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < LEVEL1_MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//Deletes all elements of the array
	for (unsigned int i = 0; i < LEVEL1_MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[]m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < LEVEL1_MAP_HEIGHT && w < LEVEL1_MAP_WIDTH)
	{
		return m_map[h][w];
	}
	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	m_map[row][column] = new_value;
}