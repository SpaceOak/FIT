
#include "Cell.h"

Cell::Cell(const unsigned int X, const unsigned int Y) : X(X), Y(Y), type(' ') {}
Cell::Cell(const char type, const unsigned int X, const unsigned int Y) : X(X), Y(Y), type(type) {}

Cell::~Cell() {}

void Cell::addTowerInRange(const weak_ptr<SavedTower> & towerPointer) {
	towersInRange.push_back(towerPointer);
}

vector<weak_ptr<SavedTower>> & Cell::getTowersInRange() {
	return towersInRange;
}

// Get/set cell type
char Cell::getChar() const {
	return type;
}

void Cell::setChar(const char newChar) {
	type = newChar;
}

// Get/set status
int Cell::getStatus() const {
	return status;
}

void Cell::setStatus(const int newStatus) {
	status = newStatus;
}

// Get/set before
Cell * Cell::getBefore() const {
	return before;
}

void Cell::setBefore(Cell ** x) {
	if (x == nullptr) {
		before = nullptr;
	} else {
		before = *x;
	}
}

// Get coordinates
unsigned int Cell::getX() const {
	return X;
}

unsigned int Cell::getY() const {
	return Y;
}
