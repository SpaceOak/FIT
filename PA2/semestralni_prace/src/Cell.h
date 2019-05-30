

#ifndef Cell_h
#define Cell_h

#include "SavedTower.h"
#include "Critter.h"

#include <vector>
#include <memory>

using namespace std;

/**
 * Cell class, which represents one cell in game map
 */
class Cell {
public:

    /// construct
	Cell(const unsigned int X, const unsigned int Y);
    /// construct and fill
	Cell(const char type, const unsigned int X, const unsigned int Y);
    ///vertical destr
	virtual ~Cell();
	/// get type of content
	char getChar() const;
    /// set type of content
	void setChar(const char newChar);
	///get x coord
	unsigned int getX() const;
    ///get y coord
	unsigned int getY() const;
    ///save tower
	void addTowerInRange(const weak_ptr<SavedTower> & towerPointer);
    ///get pnt at vec of towers
	vector<weak_ptr<SavedTower>> & getTowersInRange();
	///getter
	int getStatus() const;
    ///setter
	void setStatus(const int newStatus);
	///get prev
	Cell * getBefore() const;
    ///set prev
	void setBefore(Cell ** before);
			
protected:
	// Coordinates
	unsigned int X = 0, Y = 0;
	
	// Type of tower
	char type = '\0';
	
	// BFS
	Cell * before = nullptr;
	int status = -1;
	
	// Towers in range
	vector<weak_ptr<SavedTower>> towersInRange;
};

#endif /* Cell_h */
