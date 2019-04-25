#pragma once
#ifndef __BLOCK_H
#define __BLOCK_H
#include "StructPool.h"
#include "MapManager.h"
#define BLOCKWIDTH 100
#define PARTICLE 25

inline bool IsRange(int i, int j){
	if(( i >= 0 && i < WIDTH_IDX) && ( j >= 0 && j < HEIGHT_IDX))
		return true;
	else
		return false;
}

enum dir 
{
	down = 0,
	left,
	rigth
};

class Block
{
private:
	blockRect currentBlock_;
	blockRect nextBlock_;
	int blockMask_[4][4];
	int** map_;

	HWND hView_;
public:
	Block(void);
	Block(HWND handle) { hView_ = handle; };
	~Block(void);
	void SetMap(int** __map) { map_ = __map; };
	blockRect& MakeFirstBlock();
	BOOL DownBlocks();
	BOOL IsAbleToMove(blockRect, int);

	void UpdateCurrentBlocks();
	void CopyBlocks(int a[][4], int b[][4]);
	blockRect& GetCurrentBlock() { return currentBlock_; };
	blockRect& GetNextBlock() { return nextBlock_; };
};
#endif
