#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <string>
#include "level_0.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"

class Block;
class Board;
class Square;

using namespace std;

class Player {
    Board *board;

    //Block *currBlock = NULL;
    //Block *nextBlock = NULL;
    int score;
    string filename;
    unsigned int seed;
    int currLevel;
    vector<Level*> levelVector;
    Block *nextblock;
	Block *currblock;
    
    //Initialize a vector of size 18, all containing vectors of size 11, containing a char
    //vector< vector<char> > board{vector< vector<char> > (18, vector<char>(11, '-'))};


   public:
    Level *getLevelObject();
    Board *getBoardObject();
	Block *getCurrBlock();
	Block *getNextBlock();
    void computeScore();
    int getScore();
    void addScore(int add_score);
    void levelUp();
    void levelDown();
    void apply_heavy(Block *block, int weight_factor);
    void force(Block *newblock);
	void swapCurrBlock();
	void replaceCurrBlock(char type);
    Player(string filename, unsigned int seed, int currLevel);
    ~Player();
};




#endif
