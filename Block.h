#pragma once
#ifndef __BLOCK_H
#define __BLOCK_H
#include "StructPool.h"
#include "MapManager.h"
#include <vector>
#define BLOCKWIDTH 100
#define PARTICLE 25
#define STOP 0
#define OUT -1
#define KEEP 1

inline int IsRange(int i, int j){
	if(( i >= 0 && i < WIDTH_IDX) && ( j >= 0 && j < HEIGHT_IDX))
		return KEEP;
	else if(( j >= 0 && j < HEIGHT_IDX) && ( i < 0 || i >= WIDTH_IDX))
		return OUT;
	else
		return STOP;
}

enum dir 
{
	down = 0,
	left,
	right
};

class Block
{
private:
	blockRect currentBlock_;
	blockRect nextBlock_;
	int blockMask_[4][4];
	int** map_;
public:
	Block(void);
	~Block(void);
	void SetMap(int** __map) { map_ = __map; };
	blockRect& MakeFirstBlock();
	int DownBlocks();
	int LeftBlocks();
	int RightBlocks();
	int IsAbleToMove(blockRect, int);

	void UpdateCurrentBlocks();
	void CopyBlocks(int a[][4], int b[][4]);
	blockRect& GetCurrentBlock() { return currentBlock_; };
	blockRect& GetNextBlock() { return nextBlock_; };
};
#endif
