#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
class Block;
class Square;

using namespace std;

class Board {
    vector< vector<char> >* grid;
    int vertical, horizontal, L4counter;
    vector< vector<Square> > * grid_squares;
    vector <Block> *blocks;
 public:
    vector< vector<char> >* get_board();
    void clear_row(int row);
    void drop_blocks();
    int rows_cleared();
    int get_vertical();
    int get_horizontal();
    bool squareExists(int vertical, int horizontal);
    Board();
    
};

#endif

