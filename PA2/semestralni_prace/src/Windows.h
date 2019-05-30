
#ifndef Windows_h
#define Windows_h

#include <ncurses.h>
#include <string>

/// it is abstarct class so nothing to type here
class Windows {
public:
    ///constr
	Windows();
    ///deconstr
	virtual ~Windows();
    ///refresh windows
	virtual unsigned int showWindows() = 0;
    ///errorMessage out
    void showFailedIOMessage(const unsigned int idxOfMessage) const;
	
protected:
	WINDOW * window;
	int maxY = 0;
	int maxX = 0;
};

#endif /* Windows_h */
