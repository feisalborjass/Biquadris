#ifndef __TBLOCK_H__
#define __TBLOCK_H__
#include "block.h"

class T_Block : public Block {
	public:
	T_Block(int level_generated, int weight = 0);
	void printBlock(int currplayer);
	void clockwise(Board *b, int num_spins = 1);
	void counterclockwise(Board *b, int num_spins = 1);
	~T_Block();
};

#endif
