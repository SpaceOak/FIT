
#ifndef SavedTower_h
#define SavedTower_h

#include <vector>

using namespace std;
///represent saved tower
class SavedTower {
public:
    ///create empty
	SavedTower();
    ///create and fill
	SavedTower(const int health, const unsigned int cost, const unsigned int range, const unsigned int attack, const char character);
	///get type
	const char getCharacter() const;
    ///get hp
	const int getHealth() const;
    ///get cost
	const unsigned int getCost() const;
    ///get range
	const unsigned int getRange() const;
    ///get attack
	const unsigned int getAttack() const;
    ///set attack
	void setAttack(const unsigned int newAttack);
	///get pos (x and y)
	pair<unsigned int, unsigned int> getTowerCoordinates() const;
    ///set pos (x and y)
	void setTowerCoordinates(const unsigned int X, const unsigned int Y);
	///check if alive
	bool isAlive() const;
    ///check if about to die
	bool lowerHealth(const unsigned int minusHealth);
	
protected:
	char character = '\0';
	
	int health = 0;
	unsigned int cost = 0;
	unsigned int range = 0;
	unsigned int attack = 0;
	unsigned int X = 0;
	unsigned int Y = 0;
};
#endif /* SavedTower_h */
