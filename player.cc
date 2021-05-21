#include <iostream>
#include <vector>
#include "player.h"
#include "block.h"
#include "board.h"
#include "square.h"
#include "level.h"
#include "level_0.h"

using namespace std;

Player :: Player(string filename, unsigned int seed, int currLevel):
    board{new Board()}, score{0}, filename{filename}, seed{seed}, currLevel{currLevel} {
        levelVector.emplace_back(new Level_0{filename});
        levelVector.emplace_back(new Level_1{seed});
        levelVector.emplace_back(new Level_2{seed});
        levelVector.emplace_back(new Level_3{seed});
        levelVector.emplace_back(new Level_4{seed});
		currblock = levelVector.at(currLevel)->next();
		nextblock = levelVector.at(currLevel)->next();
		board->addBlock(currblock);
		board->update_grid_squares();
}

Player :: ~Player() {
    delete board;
	levelVector.clear();
}

Level* Player :: getLevelObject() {
    return levelVector.at(currLevel);
}

Board* Player :: getBoardObject() {
    return board;
}

Block* Player :: getCurrBlock() {
	return currblock;
}

Block* Player :: getNextBlock() {
	return nextblock;
}

void Player :: computeScore() {}

int Player :: getScore() {
    return score;
}

void Player :: addScore(int add_score) {
    score += add_score;
}

void Player :: levelUp() {
    if (currLevel < 4) {
		currLevel += 1;
	} else {
		cout << "Level cannot exceed 4" << endl;
	}
}

void Player :: levelDown() {
    if (currLevel > 0) {
		currLevel -= 1;
	} else {
		cout << "Level cannot fall below 0" << endl;
	}
}

void Player :: swapCurrBlock() {
	currblock = nextblock;
	board->addBlock(currblock);
	board->update_grid_squares();
	nextblock = levelVector.at(currLevel)->next();
}

void Player :: replaceCurrBlock(char type) {
	for (auto &square : *currblock->getSquares()) {
		board->clearSquare(square->getX(), square->getY());
	}	
	board->removeBlock(currblock);
	
	if (type == 'I') {
		currblock = new I_Block(currLevel);
	} else if (type == 'J') {
		currblock = new J_Block(currLevel);
	} else if (type == 'L') {
		currblock = new L_Block(currLevel);
	} else if (type == 'O') {
		currblock = new O_Block(currLevel);
	} else if (type == 'S') {
		currblock = new S_Block(currLevel);
	} else if (type == 'T') {
		currblock = new T_Block(currLevel);
	} else if (type == 'Z') {
		currblock = new Z_Block(currLevel);
	} else {
		cerr << "Error: Invalid block replacement" << endl;
	}
	board->addBlock(currblock);
	board->update_grid_squares();
}

void Player::apply_heavy(Block *block, int weight_factor) {
    block->addWeight(weight_factor);
}

void Player::force(Block *newBlock) {
	currblock = newBlock;
	//remove old currblock in blocks and add newBlock
}