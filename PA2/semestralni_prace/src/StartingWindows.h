#ifndef StartingWindows_h
#define StartingWindows_h

#include "Windows.h"

using namespace std;
///abstract class => nothing interesting here
class StartingWindows : public Windows {
public:
    ///create win
	StartingWindows() : Windows() {}
	///refresh win
	virtual unsigned int showWindows() override;
};

#endif /* StartingWindows_h */
