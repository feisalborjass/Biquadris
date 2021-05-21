#include <memory>
#include <vector>
#include <iostream>

#include "block.h"
#include "square.h"
#include "board.h"


/*	vector<Square*> squares;
	int rotation, levelGenerated;
	bool collisionDetected(oard);
*/

string operator*(string const &s, size_t n) {
    string r;  // empty string
    r.reserve(n * s.size());
    for (size_t i=0; i<n; i++)
        r += s;
    return r;
}

Block::Block(int level_generated, int weight) : 
	squares{new vector<Square*>}, rotation{0}, level_generated{level_generated}, weight{weight} {}

Block::~Block() {
	squares->clear();
	delete squares;
}

bool Block::collisionDetected(Board *b, string direction) {
	for (auto &square : *squares) {
		if (direction == "down") {
			if (square->getY() == b->get_vertical()-1) {
			//	cout << "collision detected - block is at the bottom of the board" << endl;
				return true;
			} else {
				if (b->otherSquareExists(this, square->getY()+1, square->getX())) {
			//		cout << "collision detected - there is a block below the current position" << endl;
					return true;
				}
			}
		} else if ((direction == "right") &&
			((square->getX() == b->get_horizontal()-1) ||
			(b->otherSquareExists(this, square->getY(), square->getX()+1)))) {
		//	cout << "collision detected - there is an obstacle on the right" << endl;
			return true;
		} else if ((direction == "left") &&
			((square->getX() == 0) ||
			(b->otherSquareExists(this, square->getY(), square->getX()-1)))) {
		//	cout << "collision detected - there is an obstacle on the left" << endl;
			return true;
		}
	}
	//cout << "there was no collision detected" << endl;
	return false;
}
/*
bool Block::collisionDetectedSquare(Square *square, Board *b, string direction) {
	cout << "checking for a square of type " << square->getType() << "'s collision detection" << endl;
	cout << "(x, y): (" << square->getX() << ", " << square->getY() << ")" << endl; 
	if (direction == "down") {
		if (square->getY() == b->get_vertical()-1) {
			cout << "collision detected - block is at the bottom of the board" << endl;
			return true;
		} else {
			if (b->otherSquareExists(this, square->getY()+1, square->getX())) {
		//		cout << "collision detected - there is a block below the current position" << endl;
				return true;
			}
		}
	}
	return false;
}*/

void Block::addWeight(int n) {
	weight += n;
}

void Block::left(Board *b, int spaces) {
	for (int i = 0; i < spaces; ++i) {
		if (!collisionDetected(b, "left")) {
			for (auto &square : *squares) {
				if (square) {
					square->moveLeft();	
					// on the board, make the square's old position a blank square
					b->clearSquare(square->getX()+1, square->getY());
				}	
			}
			// try moving block down if a heavy effect is applied
			down(b, 0);
		}
	}
}

void Block::right(Board *b, int spaces) {	
	for (int i = 0; i < spaces; ++i) {
		if (!collisionDetected(b, "right")) {
			for (auto &square : *squares) {
				if (square) {
					square->moveRight();
					// on the board, make the square's old position a blank square
					b->clearSquare(square->getX()-1, square->getY());
				}
			}
			// try moving block down if a heavy effect is applied
			down(b, 0);
		}
	}
}

void Block::down(Board *b, int spaces) {	
	for (int i = 0; i < spaces; ++i) {
		if (!collisionDetected(b, "down")) {
			for (auto &square : *squares) {
				if (square) {
					square->moveDown();
					// on the board, make the square's old position a blank square
					b->clearSquare(square->getX(), square->getY()-1);
				}
			}
		}
	}
}
/*
void Block::down(Board *b, int spaces) {
	for (int i = 0; i < spaces + weight; ++i) {
		for (auto &square : *squares) {
			if (square) {
				if (!(collisionDetectedSquare(square, b, "down"))) {
					cout << "Moving a square down of type " << square->getType() << endl;
					square->moveDown();
					// on the board, make the square's old position a blank square
					b->clearSquare(square->getX(), square->getY()-1);
				}
			}
		}
	}
}*/

void Block::drop(Board *b) {
	while (!collisionDetected(b, "down")) {
		down(b, 1);
	}
}
/*
void Block::dropSquares(Board *b) {
	//while (!collisionDetected(b, "down")) {
	for (auto &square : *squares){
		while (!collisionDetectedSquare(square, b, "down")) {
			cout << "moving a square down" << endl;
			square->moveDown();
			// on the board, make the square's old position a blank square
			b->clearSquare(square->getX(), square->getY()-1);
		}
	}	
	//	down(b, 1);
	//}
}*/

vector<Square*> *Block::getSquares() {
	return squares;
}

int Block::getLevelGenerated() {
	return level_generated;
}