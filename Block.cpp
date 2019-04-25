#include "stdafx.h"
#include "Block.h"
#include "TetrisView.h"
#include "MainFrm.h"
#include <time.h>
Block::Block(void)
{
}


Block::~Block(void)
{
}

blockRect& Block::MakeFirstBlock(){
	currentBlock_.startX = 12;
	currentBlock_.startY = 0;

	int arr[5][4][4] =
	{
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{1, 0, 0, 0}
		},
		{
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{1, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 0, 0},
			{1, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0}
		},
	};

	srand(time(NULL));

	int random = rand() % 5;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			currentBlock_.blockMask[i][j] = arr[random][i][j];
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

					if(IsRange(x, y) == KEEP){
						if(map_[x][y] == -1){
							return STOP;
						}
					}
					else if(IsRange(x ,y) == STOP) {
						return STOP;
					}
					else if(IsRange(x, y) == OUT){
						return OUT;
					}
					else{
					}
				}
			}
		}
		return KEEP;
	}
	else if(direction == dir::left){
		//left
		blockRect cur = blocks;
		blockRect next;
		next.startX = cur.startX - 1;
		next.startY = cur.startY;

		CopyBlocks(cur.blockMask, next.blockMask);
		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if(next.blockMask[i][j] == 1){
					int x = i + next.startX;
					int y = j + next.startY;
					
					if(IsRange(x, y) == KEEP){
						if(map_[x][y] == -1){
							return STOP;
						}
					}
					else if(IsRange(x ,y) == STOP) {
						return STOP;
					}
					else if(IsRange(x, y) == OUT){
						return OUT;
					}
					else{
					}
				}
			}
		}
		return KEEP;
	}
	else {
		//right
		blockRect cur = blocks;
		blockRect next;
		next.startX = cur.startX + 1;
		next.startY = cur.startY;

		CopyBlocks(cur.blockMask, next.blockMask);
		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if(next.blockMask[i][j] == 1){
					int x = i + next.startX;
					int y = j + next.startY;
					
					if(IsRange(x, y) == KEEP){
						if(map_[x][y] == -1){
							return STOP;
						}
					}
					else if(IsRange(x ,y) == STOP) {
						return STOP;
					}
					else if(IsRange(x, y) == OUT){
						return OUT;
					}
					else{
					}
				}
			}
		}
		return KEEP;
	}

	return KEEP;
}

int Block::DownBlocks(){
	int ret = IsAbleToMove(currentBlock_, dir::down);
	if(ret == KEEP){
		nextBlock_.startX = currentBlock_.startX;
		nextBlock_.startY = currentBlock_.startY + 1;
	
		CopyBlocks(currentBlock_.blockMask, nextBlock_.blockMask);
		return KEEP;
	}
	else if(ret == STOP){
		return STOP;
	}
	else if(ret == OUT){
		nextBlock_ = currentBlock_;
		return OUT;
	}
}

int Block::LeftBlocks(){
	int ret = IsAbleToMove(currentBlock_, dir::left);
	if(ret == KEEP){
		nextBlock_.startX = currentBlock_.startX - 1;
		nextBlock_.startY = currentBlock_.startY;
	
		CopyBlocks(currentBlock_.blockMask, nextBlock_.blockMask);
		return KEEP;
	}
	else if(ret == STOP){
		return STOP;
	}
	else if(ret == OUT){
		nextBlock_ = currentBlock_;
		return OUT;
	}
}

int Block::RightBlocks(){
	int ret = IsAbleToMove(currentBlock_, dir::right);
	if(ret == KEEP){
		nextBlock_.startX = currentBlock_.startX + 1;
		nextBlock_.startY = currentBlock_.startY;
	
		CopyBlocks(currentBlock_.blockMask, nextBlock_.blockMask);
		return KEEP;
	}
	else if(ret == STOP){
		return STOP;
	}
	else if(ret == OUT){
		nextBlock_ = currentBlock_;
		return OUT;
	}
}

void Block::CopyBlocks(int src[][4], int dst[][4]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			dst[i][j] = src[i][j];
		}
	}
}