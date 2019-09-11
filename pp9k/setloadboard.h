#ifndef __SETLOADBOARD_H__
#define __SETLOADBOARD_H__
#include <string.h>
#include "setboard.h"
using std::string;
class Setloadboard:public Setboard{
	string file;
   public:
	~Setloadboard();
	Setloadboard(string,Board*);
	void setup();
};
#endif
