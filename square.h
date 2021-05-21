#ifndef __SQUARE_H__
#define __SQUARE_H__

class Square {
	int x, y;
	bool is_deleted;
	char c;
  public:
	Square(int x, int y, char c);
	bool return_is_deleted();
	void change_is_deleted(bool b);
	int getX() const;
	int getY() const;
	char getType() const;
	void changeX(int new_x);
	void changeY(int new_y);
	void changeType(char new_c);
	void moveLeft(int spaces = 1);
	void moveRight(int spaces = 1);
	void moveDown(int spaces = 1);
	Square *getAddress();	
};

#endif
