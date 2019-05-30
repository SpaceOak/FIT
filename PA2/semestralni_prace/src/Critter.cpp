

#include "Critter.h"

Critter::Critter() = default;

Critter::Critter(const int hp, const char character, const unsigned int attackPower) : hp(hp), character(character), attackPower(attackPower) {}

const int Critter::getHp() const {
	return hp;
}

const unsigned int Critter::getAttack() const {
	return attackPower;
}

const char Critter::getCharacter() const {
	return character;
}

const bool Critter::isAlive() const {
	if (hp != 0 && character != '\0') {
		return true;
	}
	return false;
}

void Critter::die() {
	character = '\0';
	hp = 0;
	attackPower = 0;
}

void Critter::lowerHealth(const int lowerHealth) {
	hp -= lowerHealth;
	
	if (hp < 0) {
		die();
	}
}
