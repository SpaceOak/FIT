#include "Game.h"
#include <queue>

using namespace std;

Game::Game() {
	mapOfGame = Map(0,0);
}

unsigned int Game::startNewGame() {
	
	// Load template file
	ifstream newGameTemplate;
	newGameTemplate.open("src/data/template_new.txt", ios::in);
	
	if (!newGameTemplate.is_open() || newGameTemplate.fail()) {return 1;}
	unsigned int noOfTowers = 0;
	newGameTemplate >> noOfTowers;
	
	for (unsigned int i = 0; i<noOfTowers; i++) {
		char towerName;
		unsigned int health, cost, range, attack;
		
		newGameTemplate >> towerName >> health >> cost >> range >> attack;
        if (newGameTemplate.fail()) {return 1;}
		
		SavedTower newTower(health, cost, range, attack, towerName);
		defaultTowers[towerName] = newTower;
	}
	
	
	unsigned int noOfWarriors = 0;
	newGameTemplate >> noOfWarriors;
    if (newGameTemplate.fail()) {return 1;}
	
	for (unsigned int i = 0; i<noOfWarriors; i++) {
		char warriorName;
		unsigned int health, attack;
		
		newGameTemplate >> warriorName >> health >> attack;
        if (newGameTemplate.fail()) {return 1;}
		defaultCritters.push_back(Critter(health, warriorName, attack));
	}
	
	// Velkost mapy
	unsigned int X = 0, Y = 0;
	
	newGameTemplate >> X >> Y;
    
    if (newGameTemplate.fail()) {return 1;}
	
	mapOfGame = Map(X,Y);
	
	string line = "";
	getline(newGameTemplate, line);
    if (newGameTemplate.fail()) {return 1;}
    
    bool hasStart = false;
    bool hasEnd = false;
	
	for (unsigned int i = 0; i<Y; i++) {
		getline(newGameTemplate, line);
        if (newGameTemplate.fail()) {return 1;}
        
		for (unsigned int j = 0; j<X; j++) {
			char charInFile = line[j];
			
			if (charInFile == ' ') {
				mapOfGame.map[i][j] = new Road(j, i);
			} else if (charInFile == '#') {
				mapOfGame.map[i][j] = new Wall(j, i);
			} else if (charInFile == '<') {
				mapOfGame.setEnd(j, i);
                hasEnd = true;
				mapOfGame.map[i][j] = new Road(j, i);
				mapOfGame.map[i][j]->setChar('<');
			} else if (charInFile == '>') {
				mapOfGame.setStart(j, i);
                hasStart = true;
				mapOfGame.map[i][j] = new Road(j, i);
				mapOfGame.map[i][j]->setChar('>');
			}
		}
	}
    
    if (!hasStart || !hasEnd) {return 1;}
    
    return 0;
}

unsigned int Game::saveGame() {
	ofstream saveFile;
	saveFile.open("src/data/save.txt", ios::out);
    
    if (!saveFile.is_open() || !saveFile.good()) {return 1;}
	saveFile << defaultTowers.size() << endl;
	
	for (auto & tower : defaultTowers) {
		saveFile << tower.first << " " << tower.second.getHealth() << " " << tower.second.getCost() << " " << tower.second.getRange() << " " << tower.second.getAttack() << endl;
        if (!saveFile.good()) {return 1;}
	}
	
	saveFile << "" << endl;
    if (!saveFile.good()) {return 1;}
	saveFile << defaultCritters.size() << endl;
	
	for (auto & Critter : defaultCritters) {
		saveFile << Critter.getCharacter() << " " << Critter.getHp() << " " << Critter.getAttack() << endl;
        if (!saveFile.good()) {return 1;}
	}
	
	saveFile << "" << endl;
    if (!saveFile.good()) {return 1;}
	
	saveFile << mapOfGame.map[0].size() << " " << mapOfGame.map.size() << endl;
    if (!saveFile.good()) {return 1;}
	
	for (unsigned int i = 0; i<mapOfGame.map.size(); i++) {
		for (unsigned int j = 0; j<mapOfGame.map[i].size(); j++) {
			if (mapOfGame.map[i][j]->getChar() == '#' ||
				mapOfGame.map[i][j]->getChar() == '>' || mapOfGame.map[i][j]->getChar() == '<') {
				saveFile << mapOfGame.map[i][j]->getChar();
                if (!saveFile.good()) {return 1;}
			} else {
				saveFile << ' ';
                if (!saveFile.good()) {return 1;}
			}
		}
		saveFile << endl;
        if (!saveFile.good()) {return 1;}
	}
	
	saveFile << "" << endl;
    if (!saveFile.good()) {return 1;}
	unsigned int noOfTowers = 0;
	
	for (unsigned int i = 0; i<towers.size(); i++) {
		if (towers[i]) {noOfTowers++;}
	}
	
	saveFile << noOfTowers << endl;
    if (!saveFile.good()) {return 1;}
	
	for (unsigned int i = 0; i<towers.size(); i++) {
		if (towers[i]) {
			saveFile << towers[i].get()->getCharacter() << " " << towers[i].get()->getTowerCoordinates().first << " " << towers[i].get()->getTowerCoordinates().second << endl;
            if (!saveFile.good()) {return 1;}
		}
	}
	
	saveFile << "" << endl;
    if (!saveFile.good()) {return 1;}
	
	saveFile << round << " " << moneyAvailable << " " << noOfEachCritterOnMap << endl;
    if (!saveFile.good()) {return 1;}
	saveFile.close();
    return 0;
}

unsigned int Game::loadSavedGame() {
	ifstream saveFile;
	saveFile.open("src/data/save.txt", ios::in);
    
    if (!saveFile.is_open() || !saveFile.good()) {
        return 1;
    }
	
	unsigned int defaultTowersSize = 0;
	
	saveFile >> defaultTowersSize;
    
    if (!saveFile.good()) {
        return 1;
    }
	
	for (unsigned int i = 0; i<defaultTowersSize; i++) {
		char towerName;
		unsigned int health, cost, range, attack;
		
		saveFile >> towerName >> health >> cost >> range >> attack;
        
        if (!saveFile.good()) {
            return 1;
        }
		
		SavedTower newTower(health, cost, range, attack, towerName);
		
		defaultTowers[towerName] = newTower;
	}
	
	unsigned int defaultCrittersSize = 0;
	saveFile >> defaultCrittersSize;
    if (!saveFile.good()) {return 1;}
	
	for (unsigned int i = 0; i<defaultCrittersSize; i++) {
		char CritterName;
		unsigned int health, attack;
		saveFile >> CritterName >> health >> attack;
        
        if (!saveFile.good()) {return 1;}
		Critter newCritter(health, CritterName, attack);
		defaultCritters.push_back(newCritter);
	}
	
	unsigned int X = 0, Y = 0;
	
	saveFile >> X >> Y;
    
    if (!saveFile.good()) {return 1;}
	
	mapOfGame = Map(X,Y);
	
	string line = "";
	getline(saveFile, line);
    
    if (!saveFile.good()) {return 1;}
    
    bool hasStart = false;
    bool hasEnd = false;
	
	for (unsigned int i = 0; i<Y; i++) {
		getline(saveFile, line);
        
        if (!saveFile.good()) {return 1;}
		for (unsigned int j = 0; j<X; j++) {
			char charInFile = line[j];
			
			if (charInFile == ' ') {
				mapOfGame.map[i][j] = new Road(j, i);
			} else if (charInFile == '#') {
				mapOfGame.map[i][j] = new Wall(j, i);
			} else if (charInFile == '<') {
				mapOfGame.setEnd(j, i);
                hasEnd = true;
				mapOfGame.map[i][j] = new Road(j, i);
				mapOfGame.map[i][j]->setChar('<');
			} else if (charInFile == '>') {
				mapOfGame.setStart(j, i);
                hasStart = true;
				mapOfGame.map[i][j] = new Road(j, i);
				mapOfGame.map[i][j]->setChar('>');
			}
		}
	}
    
    if (!hasStart || !hasEnd) {return 1;}
	
	unsigned int noOfLiveTowers = 0;
	saveFile >> noOfLiveTowers;
    
    if (!saveFile.good()) {return 1;}
	
	for (unsigned int i = 0; i<noOfLiveTowers; i++) {
		char towerName;
		unsigned int X, Y;
		
		saveFile >> towerName >> X >> Y;
        if (!saveFile.good()) {return 1;}
		placeNewTower(towerName, X, Y);
	}
	
	saveFile >> round >> moneyAvailable >> noOfEachCritterOnMap;
    
    if (!saveFile.good()) {
        return 1;
    }
    
    return 0;
}

void Game::destroyGame() {
	for (unsigned int i = 0; i<mapOfGame.map.size(); i++) {
		for (unsigned int j = 0; j<mapOfGame.map[i].size(); j++) {
			delete mapOfGame.map[i][j];
			mapOfGame.map[i][j] = nullptr;
		}
	}
	
	defaultTowers.clear();
}

unsigned int Game::getRound() const {
    return round;
}

unsigned int Game::getMoneyAvailable() const {
    return moneyAvailable;
}

unsigned int Game::placeNewTower(const char towerName, const unsigned int X, const unsigned int Y) {
	map<char, SavedTower>::iterator it = defaultTowers.find(towerName);
	if (it == defaultTowers.end()) {return 1;}
	else if (it->second.getCost() > moneyAvailable) {return 2;}
	else if (!mapOfGame.canPlaceTower(X, Y))        {return 3;}
	it->second.setTowerCoordinates(X, Y);
	towers.push_back(make_shared<SavedTower>(it->second));
	weak_ptr<SavedTower> weakPtr = towers.back();
	mapOfGame.placeNewTower(weakPtr, it->first, X, Y);
	moneyAvailable = moneyAvailable - it->second.getCost();
	noOfLiveTowers++;
	return 0;
}

void Game::prepareRound() {
	
	// Load Critters
	for (unsigned int i = 0; i<defaultCritters.size(); i++) {
		for (unsigned int j = 0; j<noOfEachCritterOnMap; j++) {
			Critters.push_back(defaultCritters[i]);
		}
	}
	
	noOfEachCritterOnMap++;
    
    round++;
}

void Game::findPath() {
    mapOfGame.findPath();
}

unsigned int Game::moveCritters() {
	
	// If we've got some Critter available, put him at the start coordinates of the map
	if (!Critters.empty()) {
		unsigned int X = mapOfGame.path[mapOfGame.path.size() - 2]->getX();
		unsigned int Y = mapOfGame.path[mapOfGame.path.size() - 2]->getY();
		
		Road * cell = dynamic_cast<Road *> (mapOfGame.map[Y][X]);
		cell->addCritter(Critters.back());
		Critters.pop_back();
		noOfLiveCritters++;
	}
	
	// Ide od ciela cesty
	for (unsigned int i = 0; i<mapOfGame.path.size() - 1; i++) {
		
		Road * now  = dynamic_cast<Road *>(mapOfGame.path[i]);
		Road * next = dynamic_cast<Road *>(mapOfGame.path[i+1]);
		
        if (!now) {
            Tower * tow = dynamic_cast<Tower *>(mapOfGame.path[i]);
            if (!tow) {continue;}
            else if (tow->getSavedTower().expired()) {continue;}
            else if (tow->getSavedTower().lock().get()->isAlive()) {continue;}
        }
		
		// Critter has reached end
		if (i == 0 && next->getCritter().isAlive()) {return 1;}
		
		Critter CritterToMove = next->getCritter();
		
		if (CritterToMove.isAlive()) {
			now->addCritter(CritterToMove);
			now->setChar(CritterToMove.getCharacter());
			next->setChar(' ');
			next->removeCritter();
			
			for (unsigned int j = 0; j<now->getTowersInRange().size(); j++) {
				// Critter is in range of some tower
				// Attack Critter with a given tower; Critters attacks back
				// Returns pair: first - is Critter alive
				//				 second - is Tower alive
				
				// If tower in range has been destroyed, remove weak pointer
				if (now->getTowersInRange()[j].expired()) {
					now->getTowersInRange()[j].reset();
					continue;
				}
				pair<bool, bool> results = now->attackCritter(now->getTowersInRange()[j].lock().get());
				
				// Critter is dead
				if (!results.first) {
					now->removeCritter();
					now->setChar(' ');
					
					noOfLiveCritters--;
					moneyAvailable += 75;
					if (noOfLiveCritters == 0) {return 2;}
					break;
				}
				
				// Tower is dead
				if (!results.second) {
					pair<unsigned int, unsigned int> towerCoordinates = now->getTowersInRange()[j].lock().get()->getTowerCoordinates();
					
					mapOfGame.map[towerCoordinates.second][towerCoordinates.first]->setChar('X');
					
					Tower * tow = dynamic_cast<Tower *>(mapOfGame.map[towerCoordinates.second][towerCoordinates.first]);
					
					for (unsigned int k = 0; k<towers.size(); k++) {
						if (towers[k].get() == tow->getSavedTower().lock().get()) {
							towers[k].reset();
							// Remove weak pointer, since tower has been destroyed
							now->getTowersInRange()[j].reset();
						}
					}
					tow->getSavedTower().reset();
					noOfLiveTowers--;
				}
				if (noOfLiveTowers == 0) {return 3;}
			}
		}
		
	}
	
	return 0;
}

void Game::cleanUpMap() {
	for (unsigned int i = 0; i<mapOfGame.map.size(); i++) {
		for (unsigned int j = 0; j<mapOfGame.map[i].size(); j++) {
			mapOfGame.map[i][j]->setStatus(-1);
			mapOfGame.map[i][j]->setBefore(nullptr);
		}
	}
}
