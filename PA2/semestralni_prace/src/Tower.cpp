
#include "Tower.h"

using namespace std;

Tower::Tower(const char towerType, const unsigned int X, const unsigned int Y) : Road(towerType, X, Y) {}

void Tower::storeTower(const weak_ptr<SavedTower> & newTower) {
	tower = newTower;
}

weak_ptr<SavedTower> & Tower::getSavedTower() {
	return tower;
}
