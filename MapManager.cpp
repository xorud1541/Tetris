#include "stdafx.h"
#include "MapManager.h"


MapManager::MapManager(void)
{
	mapState_ = new int*[WIDTH_IDX];
	for(int i=0; i<WIDTH_IDX; i++){
		mapState_[i]= new int[HEIGHT_IDX];
	}

	for(int i=0; i<WIDTH_IDX; i++)
		for(int j=0; j<HEIGHT_IDX; j++)
			mapState_[i][j] = 0;
}

void MapManager::AddBlockToMap(blockRect& rect){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(rect.blockMask[i][j] == 1){
				int x = i + rect.startX;
				int y = j + rect.startY;

				if(mapState_[x][y] == 1)
					mapState_[x][y] = -1;
			}
		}
	}
}

void MapManager::SetBlockToMap(blockRect& rect){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(rect.blockMask[i][j] == 1){
				int x = i + rect.startX;
				int y = j + rect.startY;

				if(mapState_[x][y] == 0){
					mapState_[x][y] = 1;
				}
			}
		}
	}
}

void MapManager::DeleteBlock(blockRect& rect){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(rect.blockMask[i][j] == 1){
				int x = i + rect.startX;
				int y = j + rect.startY;

				if(mapState_[x][y] == 1)
					mapState_[x][y] = 0;
			}
		}
	}
}


MapManager::~MapManager(void)
{
	for(int i=0; i<WIDTH_IDX; i++){
		delete[] mapState_[i];
	}
	delete[] mapState_;
}
