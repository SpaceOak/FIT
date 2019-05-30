
#include "NewGameWindows.h"
#include <sstream>

const string help = "ListOfCommands: start, save, exit, add 'letter' 'x' 'y'";

NewGameWindows::NewGameWindows() : Windows() {}

/// start
unsigned int NewGameWindows::showWindows() {
    unsigned int result = game.startNewGame();
    
    /// if error then end prog's agony
    if (result == 1) {
        showFailedIOMessage(1);
        wgetch(window);
        return 0;
    }
    /// get mapScreeen
    unsigned int mapHeight = drawMap();
    /// drow content if game is loaded
    unsigned int towersHeight = drawTowerTypes(mapHeight);
    /// start game
    getAndDealWithInput(towersHeight);
    
    wclear(window);
    wrefresh(window);
    
    return 0;
}

void NewGameWindows::infoOut() const {
    // Display round and available money
    
    wmove(window, 2, 0);
    wclrtoeol(window);
    
    string roundMessage = "Round: " + to_string(game.getRound());
    mvwaddstr(window, 2, (getmaxx(window) - roundMessage.size()) / 2, roundMessage.c_str());
    
    wmove(window, 3, 0);
    wclrtoeol(window);
    
    string moneyMessage = "Money: " + to_string(game.getMoneyAvailable());
    mvwaddstr(window, 3, (getmaxx(window) - moneyMessage.size()) / 2, moneyMessage.c_str());
}

unsigned int NewGameWindows::drawMap() const {
	unsigned int heigthFromTop = 5;
	
	for (unsigned int i = 0; i<game.mapOfGame.map.size(); i++) {
		for (unsigned int j = 0; j<game.mapOfGame.map[i].size(); j++) {
			mvwaddch(window, heigthFromTop, ((getmaxx(window) - game.mapOfGame.map[i].size()) / 2) + j, game.mapOfGame.map[i][j]->getChar());
		}
		heigthFromTop++;
	}
	
	wrefresh(window);
	
	return heigthFromTop;
}

unsigned int NewGameWindows::drawTowerTypes(const unsigned int heightFromTop) const {
	unsigned int Y = heightFromTop + 1;
	unsigned int X = getmaxx(window);
	
	for (auto & item : game.defaultTowers) {
		string towerName = "";
		towerName.push_back(item.first);

		string towerDetails = towerName + ":\t" + to_string(item.second.getHealth()) + " HP,\t" + to_string(item.second.getCost()) + " $,\t" + to_string(item.second.getRange()) + " range,\t" + to_string(item.second.getAttack()) + " attack";
		mvwaddstr(window, Y, (X - towerDetails.size()) / 2, towerDetails.c_str());
		Y++;
	}
	
	wrefresh(window);
	
	return Y;
}

unsigned int NewGameWindows::getAndDealWithInput(const unsigned int heightFromTop) {
    
    // Display command
	const unsigned int inputY = heightFromTop + 2;
	
	string commandString = "Command:";
    
    unsigned int inputX = 5 + commandString.size() + 1;
    
	mvwaddstr(window, inputY, 5, commandString.c_str());
	wmove(window, inputY, 5 + commandString.size() + 1);
	wrefresh(window);
	
	noecho();
    curs_set(true);
	
    // Process any user input
	while (true) {
        int str = 0;
        string input = "";

        infoOut();
		
		while ((str = wgetch(window)) != 10) {
			// Clear any error
			wmove(window, 0, 0);
			wclrtoeol(window);
			
			if (str == KEY_BACKSPACE || str == KEY_DC|| str == 127) {
				if (!input.empty()) {
					input.pop_back();
					inputX--;
					wmove(window, inputY, inputX);
					mvwaddch(window, inputY, inputX, ' ');
					wmove(window, inputY, inputX);
				}
			} else {
				input.push_back((char) str);
				mvwaddch(window, inputY, inputX, (char) str);
				inputX++;
			}
			
			wrefresh(window);
		}
		
		unsigned int result = executeInput(input);
		
		// The game has ended, go back to menu Windows
		if (result == 1) {
			curs_set(false);
			return 0;
		}
		
        // Reset input and cursor position
		input = "";
		inputX = 5 + commandString.size() + 1;
		
		wmove(window, inputY, inputX);
		wclrtoeol(window);
		wmove(window, inputY, inputX);
		
		wrefresh(window);
	}
}

unsigned int NewGameWindows::executeInput(const string input) {
	if (input == "start") {
				
		// Clear out status of every cell
		if (game.getRound() != 0) {
			game.cleanUpMap();
		}
		
		game.prepareRound();
		
		while (true) {
			
			game.findPath();
			
			unsigned int result = game.moveCritters();
			
            infoOut();
			drawMap();
            
			usleep(80000);

			// Lost, because one or more Critters have reached the end			
			if (result == 1) {
				string lostMessage = "You have lost! Press any key to exit the game.";
				
				mvwaddstr(window, 0, (getmaxx(window) - lostMessage.size()) / 2, lostMessage.c_str());
				wrefresh(window);
                
                wgetch(window);
                
                game.destroyGame();
				
				return 1;
			// Won, because all solders are down
			} else if (result == 2) {
				string wonMessage = "";
				
				if (game.getRound() == 10) {
					wonMessage = "You have won the game! Press any key to exit.";
				} else {
					wonMessage = "You have won this round!";
				}
				
				mvwaddstr(window, 0, (getmaxx(window) - wonMessage.size()) / 2, wonMessage.c_str());
				wrefresh(window);
                
				if (game.getRound() == 10) {
                    wgetch(window);
                    game.destroyGame();
					return 1;
				} else {
					return 0;
				}
			} else if (result == 3) {
				// Lost, because every tower has been destroyed
				string lostMessage = "You have lost! Press any key to exit the game.";
				
				mvwaddstr(window, 0, (getmaxx(window) - lostMessage.size()) / 2, lostMessage.c_str());
				wrefresh(window);
                
                wgetch(window);
                
                game.destroyGame();
				
				return 1;
			}
		}
		
		return 0;
	} else if (input == "save") {
		unsigned int result = game.saveGame();
        
        if (result == 1) {
            showFailedIOMessage(0);
            wgetch(window);
        }
		
		return 0;
	} else if (input == "exit") {
		game.destroyGame();
		
		return 1;
	} else {
        // add towerName X Y command
		string command, towerName, x, y, check;
		
		istringstream stream(input, istringstream::in);
		
		stream >> command >> towerName >> x >> y >> check;
		
		if (command != "add" || check != "") {
			string errorMessage = help;
			mvwaddstr(window, 0, (getmaxx(window) - errorMessage.size()) / 2, errorMessage.c_str());
			
			return 0;
		}
		
        // Coordinates check
		unsigned int X = 0;
		unsigned int Y = 0;
		
		try {
			X = stoi(x);
			Y = stoi(y);
		} catch(...) {
			string errorMessage = help;
			mvwaddstr(window, 0, (getmaxx(window) - errorMessage.size()) / 2, errorMessage.c_str());
			
			wrefresh(window);
			return 0;
		}
		
		unsigned int success = game.placeNewTower((char) towerName[0], X, Y);
		
		if (success == 0) {
			mvwaddch(window, Y + 5, X + ((getmaxx(window) - game.mapOfGame.map[0].size()) / 2), (char) towerName[0]);
		} else {
			string errorMessage = help;
			mvwaddstr(window, 0, (getmaxx(window) - errorMessage.size()) / 2, errorMessage.c_str());
		}
        infoOut();
		
		wrefresh(window);
		
		return 0;
	}
    

    
	
	return 0;
}
