
#include "Map.h"

Map::Map() = default;

Map::Map(const unsigned int X, const unsigned int Y) : width(X), heigth(Y) {
	map.resize(heigth);
	for (auto & row : map) {
		row.resize(width);
	}
}

Map::~Map() = default;

void Map::setStart(const unsigned int X, const unsigned int Y) {
	startX = X;
	startY = Y;
}

void Map::setEnd(const unsigned int X, const unsigned int Y) {
	endX = X;
	endY = Y;
}

void Map::findPath() {
    
    path.clear();
	
	list<Cell *> q;
	
	q.push_back(map.at(startY).at(startX));
	
	map.at(startY).at(startX)->setStatus(0);
	
	while (!q.empty()) {
		Cell * cell = q.front();
		unsigned int cellX = cell->getX();
		
		unsigned int cellY = cell->getY();
		
		q.pop_front();
		
		try {
			Cell * neighbour = map.at(cellY-1).at(cellX);
            if (neighbour->getStatus() == -1 && neighbour->getChar() != '#') {
				neighbour->setStatus(0);
				neighbour->setBefore(&cell);
				
				q.push_back(map.at(cellY-1).at(cellX));
			}
		} catch(...) {
			
		}
		
		try {
			Cell * neighbour = map.at(cellY).at(cellX+1);
			if (neighbour->getStatus() == -1 && neighbour->getChar() != '#') {
				neighbour->setStatus(0);
				neighbour->setBefore(&cell);
				
				q.push_back(map.at(cellY).at(cellX+1));
			}
		} catch(...) {
			
		}
		
		try {
			Cell * neighbour = map.at(cellY+1).at(cellX);
			if (neighbour->getStatus() == -1 && neighbour->getChar() != '#') {
				neighbour->setStatus(0);
				neighbour->setBefore(&cell);
				
				q.push_back(map.at(cellY+1).at(cellX));
			}
		} catch(...) {
			
		}
		
		try {
			Cell * neighbour = map.at(cellY).at(cellX-1);
			if (neighbour->getStatus() == -1 && neighbour->getChar() != '#') {
				neighbour->setStatus(0);
				neighbour->setBefore(&cell);
				
				q.push_back(map.at(cellY).at(cellX-1));
			}
		} catch(...) {
			
		}
		
		cell->setStatus(1);
	}
	
	Cell * endCell = map.at(endY).at(endX);
	
	while (endCell) {
		path.push_back(endCell);
		endCell = endCell->getBefore();
	}
}

bool Map::canPlaceTower(const unsigned int X, const unsigned int Y) const {
	if (width < X || heigth < Y) {
		return false;
	}
	
	if (dynamic_cast<Road*>(map.at(Y).at(X)) == nullptr) {
		return false;
	}
	
	return true;
}

unsigned int Map::placeNewTower(const weak_ptr<SavedTower> & towerToAdd, const char towerName, const unsigned int X, const unsigned int Y) {
    
    // Delete any previous cell
    delete map.at(Y).at(X);
    map.at(Y).at(X) = nullptr;
    
	map.at(Y).at(X) = new Tower(towerName, X, Y);
	
	Tower * cell = dynamic_cast<Tower *>(map.at(Y).at(X));
	cell->storeTower(towerToAdd);
	
	placeTowerInRange(towerToAdd, X, Y, cell->getSavedTower().lock()->getRange());
	
	return 0;
}

void Map::placeTowerInRange(const weak_ptr<SavedTower> & towerPointer, const unsigned int X, const unsigned int Y, const unsigned int currentTowerRange) {
	
	for (uint tempY = Y - currentTowerRange; tempY<(Y+currentTowerRange*2); tempY++) {
		for (uint tempX = X - currentTowerRange; tempX<(X+currentTowerRange*2); tempX++) {
			try {
				Cell * cell = map.at(tempY).at(tempX);
				cell->addTowerInRange(towerPointer);
			} catch (const out_of_range & err) {
				continue;
			}
		}
	}
}
