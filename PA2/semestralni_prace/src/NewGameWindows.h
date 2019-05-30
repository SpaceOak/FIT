

#ifndef NewGameWindows_h
#define NewGameWindows_h

#include "Windows.h"
#include "Game.h"

#include <unistd.h>
///class to create new game
class NewGameWindows : public Windows {
public:
    ///empty constr
	NewGameWindows();
    ///refresh win
	virtual unsigned int showWindows() override;
    ///show game info
    void infoOut() const;
    ///download create map                    
	unsigned int drawMap() const;  
    ///download create tower types                 
	unsigned int drawTowerTypes(const unsigned int height) const;
    ///deal with input
	unsigned int getAndDealWithInput(const unsigned int height);
    ///continue of prev foo
	unsigned int executeInput(const string input);
	
protected:
	Game game;
};

#endif /* NewGameWindows_h */
