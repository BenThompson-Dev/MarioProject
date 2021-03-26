#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "constants.h"

class LevelMap
{
public:
	LevelMap(int levelID);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);
private:
	int** m_map;

	int levelHeight;
	int levelWidth;
};

#endif //_LEVELMAP_H