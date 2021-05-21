#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
class Block;
class Square;

using namespace std;

class Board {
    int vertical, horizontal, L4counter;
    vector< vector<Square*> > * grid_squares;
    vector <Block*> *blocks;
    vector <int> rowsToClear;
    Square *blankSpace;
    int row_full();
 public:
    Board();
    ~Board();
    void clear_row(int row);
    int drop_blocks();
    void clearBoard();
    int get_vertical();
    int get_horizontal();
    void updateClearStatus();
    int getRowsCleared();
    void clearSquare(int vertical, int horizontal);
    void clearBlock(Block *b);
    void update_grid_squares();
    void addBlock(Block *block);
    void removeBlock(Block *b);
    vector< vector<Square*> > * get_grid_squares();
    bool otherSquareExists(Block *block, int vertical, int horizontal);
    bool otherSquareExists(vector<Square*> squares, int vertical, int horizontal);
    bool otherSquareExists(Square *square, int vertical, int horizontal);
    vector<int> clearBlocks();
    bool isValidPosition(vector<Square*> squares);
    
    
};

#endif

