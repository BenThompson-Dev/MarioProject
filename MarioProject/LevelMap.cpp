#include "LevelMap.h"
#include <iostream>

/*
 * when making a map, remember:
 * 0 = empty space, 1 = blocked/occupied space
 */

LevelMap::LevelMap(int levelID)
{
	//Picks out correct level map based on ID
	switch (levelID)
	{
	case 1:
		//Map initialisation
		int map[LEVEL1_MAP_HEIGHT][LEVEL1_MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
														 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
														 {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
		levelHeight = LEVEL1_MAP_HEIGHT;
		levelWidth = LEVEL1_MAP_WIDTH;
		break;
	case 2:
		int map[LEVEL2_MAP_HEIGHT][LEVEL2_MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0 },
														 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0 },
														 {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
														 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
														 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
														 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
		levelHeight = LEVEL2_MAP_HEIGHT;
		levelWidth = LEVEL2_MAP_WIDTH;
		break;
	default:;
	}

	//Allocate memory for the level map
	m_map = new int* [levelHeight];
	for (unsigned int i = 0; i < levelHeight; i++)
	{
		m_map[i] = new int[levelWidth];
	}

	//Populate the array
	for (unsigned int i = 0; i < levelHeight; i++)
	{
		for (unsigned int j = 0; j < levelWidth; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//Deletes all elements of the array
	for (unsigned int i = 0; i < levelHeight; i++)
	{
		delete[] m_map[i];
	}
	delete[]m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < levelHeight && w < levelWidth)
	{
		return m_map[h][w];
	}
	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	m_map[row][column] = new_value;
}