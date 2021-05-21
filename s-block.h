#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include "block.h"

class S_Block : public Block {
	public:
	S_Block(int level_generated, int weight = 0);
	void printBlock(int currplayer);
	void clockwise(Board *b, int num_spins = 1);
	void counterclockwise(Board *b, int num_spins = 1);
	~S_Block();
};


#endif
