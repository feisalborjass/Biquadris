#include <iostream>
#include "o-block.h"
#include "board.h"
#include "square.h"

O_Block::O_Block(int level_generated, int weight) 
	: Block{level_generated, weight} {
	squares->emplace_back(new Square{0, 2, 'O'});
	squares->emplace_back(new Square{1, 2, 'O'});
	squares->emplace_back(new Square{0, 3, 'O'});
	squares->emplace_back(new Square{1, 3, 'O'});
	rotation = 1;
}

O_Block::~O_Block() {
	for (auto &square : *squares) {
		delete square;
	}
}

void O_Block::clockwise(Board *b, int num_spins) {
	// no implementation, as rotating an o-block has no effect
}

void O_Block::counterclockwise(Board *b, int num_spins) {
	// no implementation, as rotating an o-block has no effect
}

void O_Block::printBlock(int currplayer) {
	string space = " ";
    cout << space * currplayer * 15 << "OO" << endl;
    cout << space * currplayer * 15 << "OO" << endl;
}
