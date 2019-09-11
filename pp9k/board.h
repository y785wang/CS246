#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include "gamenotification.h"
#include "player.h"
using std::string;
class Board{
	bool black;
	Player*w;
	Player*b;
	double score[2];
	GameNotification*gn;
	int ** board;
    public:
	Board(GameNotification*);
	void setboard(int**);
	void clearboard();
	bool checkwin();
	void makeMove();
	void setplayer(string,string,int,int);
	void setblack(bool);
	void resign();
	void result();
	void notify(int,int,char,bool);
};
#endif
