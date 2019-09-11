#ifndef __GAMENOTIFICATION_H__
#define __GAMENOTIFICATION_H__
#include <string>
class GameNotification{
    public: 
	virtual void notify(int,int,char,std::string="",bool=false)=0;
};
#endif
