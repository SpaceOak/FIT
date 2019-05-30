
#ifndef Game_h
#define Game_h

#include "Map.h"
#include "SavedTower.h"
#include "Road.h"
#include "Wall.h"
#include "Tower.h"
#include "Critter.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <list>

class Game {
public:
    ///constr
	Game();
    ///foo to alloc initialize and go to main menu
	unsigned int startNewGame();
    ///same like prev but load from file
	unsigned int loadSavedGame();
    ///save game
	unsigned int saveGame();
    ///free all allocks and expell all bastards
	void destroyGame();
    ///getter round
    unsigned int getRound() const;
    ///getter cash
    unsigned int getMoneyAvailable() const;
    ///prepeare for next round
	void prepareRound();
    ///do u know de way? (knock knock)
    void findPath();
    ///move critter and attack each other
	unsigned int moveCritters();
    ///delete but not all
	void cleanUpMap();
    ///add tower
	unsigned int placeNewTower(const char towerName, const unsigned int X, const unsigned int Y);
    ///more Map.h and Map.cpp
	Map mapOfGame;
    ///loaded from file towers
    map<char, SavedTower> defaultTowers;
    
private:
    vector<Critter> defaultCritters;
    
    vector<Critter> Critters;
    vector<shared_ptr<SavedTower>> towers;
    
    unsigned int round = 0;
    unsigned int moneyAvailable = 500;
    
    unsigned int noOfEachCritterOnMap = 2;
    unsigned int noOfLiveCritters = 0;
    unsigned int noOfLiveTowers = 0;
};

#endif /* Game_h */
