#include <vector>
#include "board.h"
#include "square.h"

using namespace std;

vector< vector<char> >* Board::get_board() {                                               
    return grid;
}


void Board::clear_row(int row){
    int r;
    for(auto &blocks: blocks){
        for(auto &squares: squares){
            r = squares->getX();
            if(r == row){
                square = nullptr;
            }
            else if(r < row){
                square->changeX(r + 1);
            }
        } 
    }
}

void Board::drop_blocks(){
    int dist = 18, temp_dist, temp_x;
    for(auto &square: blocks->squares){
        //if()
        temp_dist = distance(square);
        if(temp_dist < dist){
            dist = temp_dist;
        }
    }

    for(auto &square: blocks->squares){
        temp_x = square->getX();
        square->changeX(temp_x + dist);
    }
    
    int row_to_clear = rows_cleared();
    int row_num;
    while(rows_cleared()){
        row_num = row_full();
        clear_row(row_num);
    }
}


int Board::distance(Square *square){
    int i = 1;
    while(!squareExists(square->getX() + i, square->getY()){
        ++i;
    }
    return i - 1;
}

int Board::rows_cleared(){
  int row_status = 1, rows_cleared = 0;
  grid_update();
    for(auto &i: grid){
       for(auto &y: i){
           if(y == " "){
              row_status = 0;
              break;
           }
       }
       if(row_status == 0) row_status = 1;
       else rows_cleared++;
    }
    return rows_cleared;
}

int Board::get_vertical(){
    return this->vertical;
}

int Board::get_horizontal(){
    return this->horizontal;
}

bool Board::squareExists(int vertical, int horizontal){
    if((*grid_squares)[vertical][horizontal].getType() != ' '){
        return true;
    } else {
        return false;
    }
}

void Board::grid_update(){
    for(auto &block: blocks){
        for(auto &squares: blocks->squares){
            (*grid)[squares.x][squares.y] = squares.c;
        }
    }
}

void Board::grid_squares_update(){
    for(auto &block: blocks){
        for(auto &squares: blocks->squares){
            (*grid_squares)[squares.x][squares.y] = squares;
        }
    }
}


int Board::row_full(){
    int row_status = 1, rows_cleared = 0, line_no = 0;
    for(auto &i: grid){
       for(auto &y: i){
           if(y == " "){
              row_status = 0;
              break;
           }
           line_no++;
       }
       if(row_status == 0) row_status = 1;
       else return line_no;
    }
}
