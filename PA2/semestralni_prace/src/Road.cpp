
#include "Road.h"

Road::Road(const unsigned int X, const unsigned int Y) : Cell(' ', X, Y) {}

Road::Road(const char character, const unsigned int X, const unsigned int Y) : Cell(character, X, Y) {}

void Road::addCritter(const Critter & newCritter) {
	critter = newCritter;
}

Critter & Road::getCritter() {
	return critter;
}

void Road::removeCritter() {
	critter.die();
}

pair<bool, bool> Road::attackCritter(SavedTower * tower) {
	// Tower attacks Critter
	if (tower->isAlive()) {
		critter.lowerHealth(tower->getAttack());
		
		// Critter attacks tower
		if (critter.isAlive()) {
			tower->lowerHealth(critter.getAttack());
		}
		
		return make_pair(critter.isAlive(), tower->isAlive());
	}
	
	return make_pair(true, true);
}
