
#ifndef Critter_h
#define Critter_h

#include "SavedTower.h"
#include "Cell.h"

#include <vector>

using namespace std;

class Critter {
public:
    ///constr
	Critter();
    ///constr and fill
	Critter(const int hp, const char character, const unsigned int attackPower);
    ///getter hp
    const int getHp() const;   
    ///getter type
    const char getCharacter() const;
    ///getter dmg
    const unsigned int getAttack() const;
    ///check if alive
    const bool isAlive() const;
    ///and his agony
    void die();
    ///check if about to die
	void lowerHealth(const int minusHealth);
	
private:
	int hp = 0;
	char character = '\0';
	unsigned int attackPower = 0;
};

#endif /* Critter_h */
