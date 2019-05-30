
#ifndef LoadGameWindows_h
#define LoadGameWindows_h

#include "NewGameWindows.h"

/// class to load saved game
class LoadGameWindows : public NewGameWindows {
public:
    ///constr
	LoadGameWindows();
    ///refresh
	virtual unsigned int showWindows() override;
};
#endif /* LoadGameWindows_h */
