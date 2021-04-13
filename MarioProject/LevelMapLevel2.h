#pragma once
#ifndef _LEVELMAPLEVEL2_H
#define _LEVELMAPLEVEL2_H

#include "constants.h"

class LevelMapLevel2
{
public:
	LevelMapLevel2(int map[LEVEL2_MAP_HEIGHT][LEVEL2_MAP_WIDTH]);
	~LevelMapLevel2();

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

private:
	int** m_map;
};

#endif //_LEVELMAPLEVEL2_H