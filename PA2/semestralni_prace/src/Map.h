
#ifndef Map_h
#define Map_h

#include "Cell.h"
#include "Tower.h"
#include "Road.h"
#include "Wall.h"

#include <list>
#include <map>

using namespace std;

/*
 * Map class represents game map
 */
class Map {
public:
    /// create empty
	Map();
    ///create and fill
	Map(const unsigned int X, const unsigned int Y);
    ///destr
	~Map();
    ///set start by coordinates
	void setStart(const unsigned int X, const unsigned int Y);
    ///set end by coordinates
	void setEnd(const unsigned int X, const unsigned int Y);
    ///find path from start to end
	void findPath();
    ///check if can place tower
    bool canPlaceTower(const unsigned int X, const unsigned int Y) const;   
    ///place tower by coord
	unsigned int placeNewTower(const weak_ptr<SavedTower> & towerToAdd, const char towerName, const unsigned int X, const unsigned int Y);
    ///place weak pointer to all cells, where the tower has got range
	void placeTowerInRange(const weak_ptr<SavedTower> & towerPointer, const unsigned int X, const unsigned int Y, const unsigned int currentTowerRange);
	
    ///map
	vector<vector<Cell*>> map;
    ///path at map
	vector<Cell*> path;
	
private:
	unsigned int width = 0;
	unsigned int heigth = 0;
	unsigned int startX = 0, startY = 0, endX = 0, endY = 0;
};

#endif /* Map_h */
