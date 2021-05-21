#ifndef __OBLOCK_H__
#define __OBLOCK_H__
#include "block.h"

class O_Block : public Block {
	public:
	O_Block(int level_generated, int weight = 0);
	void printBlock(int currplayer);
	void clockwise(Board *b, int num_spins = 1);
	void counterclockwise(Board *b, int num_spins = 1);
	~O_Block();
};


#endif
