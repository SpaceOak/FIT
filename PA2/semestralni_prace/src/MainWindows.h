
#ifndef MainWindows_h
#define MainWindows_h

#include "Windows.h"

#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

/// this class show main menu
class MainWindows : public Windows {
public:
    ///constr
	MainWindows() : Windows() {}
    ///refresh win
    virtual unsigned int showWindows() override;
    ///go to menu
    void showMenu(const unsigned int chosenOption = 0) const;
private:
    vector<string> messages = {"New Game", "Load Saved Game", "Exit"};
};

#endif /* MainWindows_h */
