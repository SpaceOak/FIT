#ifndef Tower_h
#define Tower_h

#include "SavedTower.h"
#include "Cell.h"
#include "Road.h"
///class to implement tower
class Tower : public Road {
public:
    ///constr
	Tower(const char towerType, const unsigned int X, const unsigned int Y);
	///save tower
	void storeTower(const weak_ptr<SavedTower> & newTower);
    ///get tower
	weak_ptr<SavedTower> & getSavedTower();
		
private:
	weak_ptr<SavedTower> tower;
};

#endif /* Tower_h */
