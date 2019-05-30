
#ifndef Road_h
#define Road_h

#include "Cell.h"
#include "Critter.h"
///implement road
class Road : public Cell {
public:
    /// create without type
	Road(const unsigned int X, const unsigned int Y);
    /// create with type
    Road(const char character, const unsigned int X, const unsigned int Y);
    /// add critter to cell
	void addCritter(const Critter & newCritter);
    /// getter
	Critter & getCritter();
    ///kill
	void removeCritter();
    /// attack critter -> tower
    /// damage can be changed in src/data
	pair<bool, bool> attackCritter(SavedTower * tower);
	
private:
	Critter critter;
};

#endif /* Road_h */
