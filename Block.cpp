#include "stdafx.h"
#include "Block.h"
#include "TetrisView.h"
#include "MainFrm.h"
Block::Block(void)
{
}


Block::~Block(void)
{
}

blockRect& Block::MakeFirstBlock(){
	currentBlock_.startX = 12;
	currentBlock_.startY = 0;

	int arr[4][4] = {
		{0, 0, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0}
	};

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			currentBlock_.blockMask[i][j] = arr[i][j];
		}
	}


	return currentBlock_;
}

void Block::UpdateCurrentBlocks(){
	currentBlock_ = nextBlock_;
}

BOOL Block::IsAbleToMove(blockRect blocks, int direction){
	if(direction == dir::down){
		blockRect cur = blocks;
		blockRect next;
		next.startX = cur.startX;
		next.startY = cur.startY + 1;

		CopyBlocks(cur.blockMask, next.blockMask);
		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if(next.blockMask[i][j] == 1){
					int x = i + next.startX;
					int y = j + next.startY;
					if(!IsRange(x ,y)) return FALSE;

					if(map_[x][y] == 0){
						continue;
					}
					else if(map_[x][y] == -1){
						return FALSE;
					}
				}
			}
		}
		return TRUE;
	}
	else if(direction == dir::left){
		//left
		return TRUE;
	}
	else {
		//right
		return TRUE;
	}

	return FALSE;
}

BOOL Block::DownBlocks(){
	if(IsAbleToMove(currentBlock_, dir::down)){
		nextBlock_.startX = currentBlock_.startX;
		nextBlock_.startY = currentBlock_.startY + 1;
	
		CopyBlocks(currentBlock_.blockMask, nextBlock_.blockMask);
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void Block::CopyBlocks(int src[][4], int dst[][4]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			dst[i][j] = src[i][j];
		}
	}
}