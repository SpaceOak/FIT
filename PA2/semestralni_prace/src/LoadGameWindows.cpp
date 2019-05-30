

#include "LoadGameWindows.h"

LoadGameWindows::LoadGameWindows() : NewGameWindows() {}

unsigned int LoadGameWindows::showWindows() {
	// Load saved game
    unsigned int result = game.loadSavedGame();
    
    if (result == 1) {
        showFailedIOMessage(1);
        wgetch(window);
        return 0;
    }
    
    // Show useful game info
    infoOut();
	
	// Draw map
	unsigned int mapHeight = drawMap();
    
    // Draw available towers
	unsigned int towersHeight = drawTowerTypes(mapHeight);
	
    // Draw input and get commands from user
	getAndDealWithInput(towersHeight);
    
    wclear(window);
    wrefresh(window);
	
	return 0;
}
