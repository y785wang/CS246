#include <iostream>
#include "controller.h"
#include "graphicdisplay.h"
#include "view.h"
using namespace std;

int main(int arg,char*argv[]){
	Controller c;
	if(arg>3){
		cerr<<"too many argument,expected 3"<<endl;
	}
	string arg1;
	string arg2;
	if(arg==3){
		arg1=argv[1];
		arg2=argv[2];
		if(arg1=="-g"){
			c.play(true,arg2);
		}else if(arg2=="-g"){
			c.play(true,arg1);
		}else{
			cerr<<"expected -g and file"<<endl;
		}
	}else if(arg==2){
		arg1=argv[1];
		if(arg1=="-g"){
			c.play(true,"");
		}else{
			c.play(false,arg1);
		}
	}else{
		c.play(false,"");
	}
}
