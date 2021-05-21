#include <vector>
#include <iostream>
#include <string>
#include "board.h"
#include "square.h"
#include <iostream>
#include "block.h"

using namespace std;

void Board::clear_row(int row){
    int r;
    
    for(auto &block: *blocks){
        Square *temp;
        for(auto &square: *(block->getSquares())){
            r = square->getY();
            cout << "r : " << r << endl;
            cout << "row: " << row << endl;
            if(r == row){
                square->change_is_deleted(true);
                clearBoard();
            }
            if(r < row){
                cout<< square->getY() <<endl;
                square->changeY(r + 1);
                cout<< square->getY() << endl;
            }  
        }
    }
    clearBoard();
    for(auto &block: *blocks){
        block->drop(this);
    }
    update_grid_squares();
}

int Board::drop_blocks(){
    int no_rows_cleared = 0;
    int row_num;
    update_grid_squares();
    if(row_full() == -1){
        return 0;
    }
    else{
        while(row_full() != -1){
            row_num = row_full(); 
            clear_row(row_num);
            no_rows_cleared++;
            cout<< "no of rows" << no_rows_cleared <<endl;
        }
    }
    //return no_rows_cleared;
    return 1;
}

/*int Board::rows_cleared(){
  int row_status = 1, rows_cleared = 0;
  update_grid_squares();
    for(auto &i: *grid_squares){
       for(auto &y: i){
           if(y->getType() == ' '){
              row_status = 0;
              break;
           }
       }
       if(row_status == 0) row_status = 1;
       else rows_cleared++;
    }
    return rows_cleared;
}*/

int Board::get_vertical(){
    return this->vertical;
}

int Board::get_horizontal(){
    return this->horizontal;
}

bool Board::otherSquareExists(Block *block, int vertical, int horizontal){
    vector<Square*> squares = *(block->getSquares());
    Square *otherSquare = (*grid_squares)[vertical][horizontal];
    if (otherSquare->getType() != ' ') {///made a change to check the attribute
        // compare addresses to determine if the other square is part of the given block
        for (auto &square : squares) {
            if (square->getAddress()==otherSquare->getAddress()) return false;
        }
        return true;
    } 
    return false;
}

bool Board::otherSquareExists(vector<Square*> squares, int vertical, int horizontal){
    Square *otherSquare = (*grid_squares)[vertical][horizontal];
    if (otherSquare->getType() != ' ') {
        // compare addresses to determine if the other square is part of the given block
        for (auto &square : squares) {
            if (square->getAddress()==otherSquare->getAddress()) return false;
        }
        return true;
    } 
    return false;
}

bool Board::otherSquareExists(Square* square, int vertical, int horizontal){
    Square *otherSquare = (*grid_squares)[vertical][horizontal];
    if (otherSquare->getType() != ' ') {
        // compare addresses to determine if the other square is part of the given block
        if (square->getAddress()==otherSquare->getAddress()) return false;
        return true;
    } 
    return false;
}

void Board::clearSquare(int vertical, int horizontal){
    if ((horizontal < 0) || (vertical < 0)) return;
    (*grid_squares)[horizontal][vertical] = blankSpace;
    //cout << "cleared space at (" << horizontal << ", " << vertical << ")" << endl;
}

void Board::clearBoard(){
    cout<< "you have been summoned";
    /*for(auto &i: *grid_squares){
        cout<< " hello" << endl;
       for(auto &square: i){
           cout<< " hi " << endl;
           if(square->return_is_deleted()){//||checkSquare(square->getY(), square->getX())) {//&&
                                            //(*grid_squares)[square->getY()][square->getX()]->getType() != ' ')){
                //                checkSquare(square->getY(), square->getX());
                cout<< " Does seg fault happen here? " << endl;
                //delete square;
               (*grid_squares)[square->getY()][square->getX()]->changeType(' ');
           //}
       }
    }
    }*/
	vector<Square*> s;
    grid_squares->clear();
	
		for (int j = 0; j < 18; ++j) {
			for (int i = 0; i < 11; ++i) {
				s.emplace_back(blankSpace);
			}
			grid_squares->emplace_back(s);
			s.clear();
		}
        update_grid_squares();
}


void Board::update_grid_squares(){
    //cout << "started update_grid_squares" << endl;
                    
    for(auto &block: *blocks){
        //cout << "updating a block..." << endl;
        for(auto &square: *(block->getSquares())){
            cout << "updating a square..." << endl;
            if(!square->return_is_deleted()){
                (*grid_squares)[square->getY()][square->getX()] = square;
                cout << blankSpace->getType() << endl;
            }
        }
    }
    cout << "finished update_grid_squares" << endl;
    for(auto &block: *blocks){
        //cout << "updating a block..." << endl;
        for(auto &square: *(block->getSquares())){
            //if(!square->return_is_deleted()){
                cout<<square->getX()<< endl;
                cout<<square->getY()<<endl;
                cout<<(*grid_squares)[square->getY()][square->getX()]->getType()<< endl;
            //}
        }
    }
}

vector< vector<Square*> > * Board::get_grid_squares() {
    return grid_squares;
}

void Board::addBlock(Block *block) {
    blocks->emplace_back(block);
}

void Board::removeBlock(Block *b) {
    int i = 0;
    for (auto &block : *blocks) {
        if (b==block) blocks->erase(blocks->begin() + i);
        ++i;
    }
}


Board::Board(): vertical{18}, horizontal{11}, L4counter{0},  
				grid_squares{new vector< vector<Square*> >}, blocks{new vector<Block*>},
                blankSpace{new Square{-1, -1, ' '}} {
//      vector< vector<char> > *grid{vector< vector<char> > (18, vector<char>(11, ' '))};
//      *grid(18, vector<char>(11, ' '));
		//vector< vector<char> > my_grid;
		vector<Square*> s;
	
		for (int j = 0; j < 18; ++j) {
			for (int i = 0; i < 11; ++i) {
				s.emplace_back(blankSpace);
			}
			grid_squares->emplace_back(s);
			s.clear();
		}
    }

Board::~Board() {
  /*  for (auto &row : *grid_squares) {
        cout << "clearing row" << endl;
        row.clear();
    }*/
    //grid->clear();
   // blocks->clear();
   /*for (int i = 0; i < vertical; ++i) {
       for (int j = 0; j < horizontal; ++j) {
           cout << "deleting a square at " << j << " " << i << endl;
           if ((*grid_squares)[vertical][horizontal]) delete (*grid_squares)[vertical][horizontal];
           cout << "deleted a square" << endl;
       }
   }*/
    delete grid_squares;
    delete blocks;
    delete blankSpace;
}

vector<int> Board::clearBlocks() {
    int blocks_cleared = 0;
    vector<int> level_vector;
    vector<Block*> :: iterator it;
    it = blocks->begin();
    for (auto &block: *blocks) {
        int isclearedcounter = 0;
        for (auto &square: *block->getSquares()) {
            if (!square->return_is_deleted()) {
                break;}
            ++isclearedcounter;
        }

        if (isclearedcounter == 4) {
            level_vector.emplace_back(block->getLevelGenerated());
            //blocks->erase(it);
            ++blocks_cleared;
        }

    }
    /*for (auto &block: *blocks) {
        int isclearedcounter = 0; it++;
        for (auto &square: *block->getSquares()) {
            if (!square->return_is_deleted()) {
                break;}
                isclearedcounter++;
        }

        if (isclearedcounter == 4) {
            blocks->erase(it);
             cout<<"FREE INVALID POINTER ERROR" <<endl;
        }

    }*/
    return level_vector;
}

int Board::row_full(){
    int line_no = -1, state = 1;
    for(auto &i: *grid_squares){
       for(auto &y: i){
           if(y->getType() == ' '){
              state = 0;
              break;
           }
       }
       if(state == 1){
           line_no++;
           return line_no;
        } else {
            line_no++; 
            state = 1;
        }
    }
    return -1;
}

bool Board::isValidPosition(vector<Square*> squares) {
    cout << "Called isValidPosition()" << endl;
    for (auto square : squares) {
		if ((square->getX() >= horizontal) || (square->getX() < 0) ||
			(square->getY() >= vertical) || (square->getY() < 0)) return false;
        if ((otherSquareExists(squares, square->getY(), square->getX())) ||
            (otherSquareExists(squares, square->getY(), square->getX())) ||
            (otherSquareExists(squares, square->getY(), square->getX())) ||
            (otherSquareExists(squares, square->getY(), square->getX()))) {
            cout << "Position is not valid" << endl;
            return false;
        }
	}
	return true;
}