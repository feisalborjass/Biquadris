#include "square.h"
#include <iostream>
using namespace std;

Square::Square(int x, int y, char c) 
	: x{x}, y{y}, c{c} ,is_deleted{false} {}

int Square::getX() const {
	return x;
}

int Square::getY() const {
	return y;
}

char Square::getType() const {
	return c;
}

void Square::changeX(int new_x) {
	x = new_x;
}

void Square::changeY(int new_y) {
	y = new_y;
}

void Square::changeType(char new_c) {
	c = new_c;
}

void Square::moveLeft(int spaces) {
	x -= spaces;
}

void Square::moveRight(int spaces) {	
	x += spaces;
}

void Square::moveDown(int spaces) {
	y += spaces;
}

Square *Square::getAddress() {
	return this;
}

bool Square::return_is_deleted(){
	return is_deleted;
}

void Square::change_is_deleted(bool b){
	is_deleted = b;
}