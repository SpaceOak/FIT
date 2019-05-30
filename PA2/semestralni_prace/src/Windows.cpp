
#include "Windows.h"

using namespace std;

Windows::Windows() : window(newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0)) {
	maxX = getmaxy(stdscr);
	maxY = getmaxx(stdscr);
}

Windows::~Windows() {
	delwin(window);
}

void Windows::showFailedIOMessage(const unsigned int idxOfMessage) const {
    string failMessage;
    if (idxOfMessage == 1) {
        failMessage = "File feel's bad! Nothing to do here.";
    } else if (idxOfMessage == 0) {
        failMessage = "Game save has failed!";
    }
    mvwaddstr(window, 0, (getmaxx(window) - failMessage.size()) / 1.5f, failMessage.c_str());
    
    wrefresh(window);
    wmove(window, 0, 0);
    wclrtoeol(window);
}
