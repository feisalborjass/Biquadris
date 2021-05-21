#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <vector>
#include <string>

class Board;
class Square;

using namespace std;

class Block {
  protected:
	vector<Square*> *squares;
	int rotation;
	int level_generated, weight, L4counter; 
	bool collisionDetected(Board *b, const string direction);
  public:
	Block(int level_generated, int weight = 0);
	void left(Board *b, int spaces = 1);
	void right(Board *b, int spaces = 1);
	void down(Board *b, int spaces = 1);
	void drop(Board *b);
	vector<Square*> *getSquares();
	int getLevelGenerated();
	void addWeight(int n);
	virtual void printBlock(int spaces = 0) = 0;
	// VIOLATES clNVI -> USE PIMPL LATER
	virtual void clockwise(Board *b, int num_spins = 1) = 0;
	virtual void counterclockwise(Board *b, int num_spins = 1) = 0;
	Block(int level_generated, Board *b, int weight=0);
	virtual ~Block();
};

string operator*(string const &s, size_t n);

#endif
