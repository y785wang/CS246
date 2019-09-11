#ifndef __SETBOARD_H__
#define __SETBOARD_H__
#include <string>
#include "board.h"
using std::string;
class Setboard{
 protected:
	Board* b;
	bool p;//print or not
	int king,KING,num,NUM;
	int**board;
	bool black;
	void set(char,char,char,char);
 public:
	void setplayer(string,string,int,int);
	Setboard(Board*);
	virtual ~Setboard();
	void returnboard();
	virtual void setup();
};
#endif
