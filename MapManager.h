#pragma once
#ifndef __MAPMANAGER_H_
#define __MPAMANAGER_H_
#define WIDTH_IDX		28
#define HEIGHT_IDX		36
#include "StructPool.h"
class MapManager
{
private:
	int** mapState_;

public:
	MapManager(void);
	~MapManager(void);
	int** GetMapState() const { return mapState_; };
	
	void AddBlockToMap(blockRect&);
	void DeleteBlock(blockRect&);
	void SetBlockToMap(blockRect&);
};

#endif

