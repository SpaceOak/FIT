
#include "SavedTower.h"

SavedTower::SavedTower() = default;

SavedTower::SavedTower(const int health, const unsigned int cost, const unsigned int range, const unsigned int attack, const char character) : character(character), health(health), cost(cost), range(range), attack(attack) {}

bool SavedTower::lowerHealth(const unsigned int minusHealth) {
	health -= minusHealth;
	
	if (isAlive()) {
		return false;
	}
	
	return true;
}

const char SavedTower::getCharacter() const {
	return character;
}

const int SavedTower::getHealth() const {
	return health;
}

const unsigned int SavedTower::getCost() const {
	return cost;
}

const unsigned int SavedTower::getAttack() const {
	return attack;
}

const unsigned int SavedTower::getRange() const {
	return range;
}

void SavedTower::setAttack(const unsigned int newAttack) {
	attack = newAttack;
}

pair<unsigned int, unsigned int> SavedTower::getTowerCoordinates() const {
	return make_pair(this->X, this->Y);
}

void SavedTower::setTowerCoordinates(const unsigned int newX, const unsigned int newY) {
	X = newX;
	Y = newY;
}

bool SavedTower::isAlive() const {
	return health > 0;
}
