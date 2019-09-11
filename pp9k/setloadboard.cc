#include <iostream>
#include <fstream>
#include <string>
#include "setloadboard.h"
using std::cin;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;
Setloadboard::Setloadboard(string file,Board*b):Setboard(b),file(file){}
Setloadboard::~Setloadboard(){}
void Setloadboard::setup(){
        ifstream load(file.c_str());
        string line;
	int r=0;
        while(load>>line&&(line.length()!=1)){
       		for(int c=0;c<8;c++){
               		if(line[c]!='_'){
              			set(c+'a','8'-r,line[c],'+');
                	}
                }
		r++;
        }
        if(line[0]=='W'){
                b->setblack(false);
		cout<<"White turn"<<endl;
        }else{
                b->setblack(true);
		cout<<"Black turn"<<endl;
        }
}
