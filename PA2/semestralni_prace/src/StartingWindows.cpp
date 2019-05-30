#include "StartingWindows.h"

unsigned int StartingWindows::showWindows() {
	noecho();
	curs_set(FALSE);
	
	string StartingMessage = "Tower Defense game by dubinden";
	string introMessage = "Written in C++";
	
	mvwprintw(window, getmaxy(window) / 2 - 2, (getmaxx(window) - StartingMessage.size()) / 2, StartingMessage.c_str());
	
	mvwprintw(window, getmaxy(window) / 2, (getmaxx(window) - introMessage.size()) / 2, introMessage.c_str());
	
	wrefresh(window);
    wgetch(window);
	wclear(window);
	
	return 0;
}
