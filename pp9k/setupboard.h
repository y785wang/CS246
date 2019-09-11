#ifndef __SETUPBOARD_H__
#define __SETUPBOARD_H__
#include "board.h"
#include "setboard.h"
class Setupboard:public Setboard{
	bool danger(int);
   public:
	Setupboard(Board*);
	void setup();
	bool setupVarify();	
};
#endif
