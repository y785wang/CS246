#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "view.h"
#include "setboard.h"
#include "gamenotification.h"
#include "string.h"

class Controller : public GameNotification{//: public GameNotification{
	View*td;
	View*gd;
	Setboard *sb; 
	Board *b;
	bool g;
    public:
	Controller();
	~Controller();
	void play(bool,std::string);
	void notify(int,int,char,std::string,bool);//X Y and chess
};
#endif
