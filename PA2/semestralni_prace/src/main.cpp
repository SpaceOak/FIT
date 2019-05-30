
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "StartingWindows.h"
#include "MainWindows.h"
#include "NewGameWindows.h"
#include "LoadGameWindows.h"

#define DELAY 35000
using namespace std;

int main() {
	
	initscr();
	    
    start_color();
    init_pair(3,COLOR_BLUE,COLOR_WHITE);
	
	StartingWindows StartingWindows;
	
	StartingWindows.showWindows();
	
	MainWindows mainWindows;
	
	while (true) {
		unsigned int chosenOption = mainWindows.showWindows();
        
        if (chosenOption == 0) {
            NewGameWindows newGameWindows;
            newGameWindows.showWindows();
        } else if (chosenOption == 1) {
            LoadGameWindows loadGameWindows;
            loadGameWindows.showWindows();
        } else {
			// Exit has been chosen
			endwin();
			break;
		}
	}
	
	return 0;
}
