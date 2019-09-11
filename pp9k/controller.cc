#include "controller.h"
#include "setupboard.h"
#include "setloadboard.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

Controller::Controller(){
	td=NULL;
	gd=NULL;
	b=NULL;
	sb=NULL;
}

Controller::~Controller(){//sb take out chessboard b take out board
	delete td;
	delete gd;
	delete b;
	delete sb;
}


void Controller::notify(int x,int y,char chess,string s="",bool p=false){
//		cout<<"notify textDisplay"<<endl;
		if(chess!='T'){td->notify(x,y,chess);}//T is setplayer
//		cout<<"notify graphicDisplay"<<endl;
		if(g){gd->notify(x,y,chess,s);}   
		if(p){
			td->print();
		}
}


//int board will be deleted by method b->clearboard();
void Controller::play(bool graphic,string file){
	g=graphic;
	int level1=0;
	int level2=0;
//	bool cp1=false;//computer 1
//	bool cp2=false; //computer 2
	bool open=false;
	b=new Board(this);//deleted by controller
	if(g){
		gd=new GraphicDisplay(10);//deleted by controller
	}
	td=new TextDisplay(10);//deleted by controller
	bool playing =false;
	bool played=false;
	bool WTB=false;//write to board
	if(file!=""){// load game 
		ifstream f(file.c_str());
		if(f.fail()){
			cerr<<"invalid file,Plz try again"<<endl;
			return ;
		}else{
			cout<<"loading ...."<<endl;
			td->clear();//default board
			cout<<"loading the board"<<endl;
			if(g){	
				open=true;
				gd->open();//open a window
				gd->clear();//clear to default backgroud
			}
			delete sb;
			sb=new Setloadboard(file,b);
			sb->setup();
			cout<<"setting th board"<<endl;
			sb->returnboard();//return intboard to board class
			td->print();
			WTB=true;
		}
	}
	string cmd;
	string p1;
	string p2;
	while(true){
		cin>>cmd;
		if(cmd=="game"&&!playing){
			while(true){//choosing player
				int valid=0;
			//	cp1=false;
		//		cp2=false;
				cin>>p1>>p2;
				if(cin.fail()){cin.clear();cin.ignore();cerr<<"cannot quit while choosing players"<<endl;}
				if(p1=="human"||p1.substr(0,p1.length()-1)=="computer"){
					char lv=p1[p1.length()-1];
					if(lv>'0'&&lv<'4'&&(p1.substr(0,p1.length()-1))=="computer"){
						level1=lv-'0';
						valid++;
					}else if(p1=="human"){
						valid++;
					}else{
						cerr<<"invalid level for p1"<<endl;
					}
				}
                                if(p2=="human"||p2.substr(0,p2.length()-1)=="computer"){
                                        char lv=p2[p2.length()-1];
                                        if(lv>'0'&&lv<'4'&&(p2.substr(0,p2.length()-1))=="computer"){
                                                level2=lv-'0';
						valid++;
					}else if(p1=="human"){
                                                valid++;
                                        }else{
                                                cerr<<"invalid level for p2"<<endl;
                                        }
                                }
				if(valid==2){
					break;
				}else{
					cerr<<"Invalid Player"<<endl;
				}
			}
			if(!WTB){
				cout<<"Game starting ..."<<endl;
				td->clear();//default board
				if(open&&g){gd->clear();}
				if(!open&&g){gd->open();open=true;gd->clear();}
				delete sb;
				sb=new Setboard(b);
				sb->setup();
				sb->returnboard();//set intboard to class board
				td->print();
				b->setblack(false);
				WTB=true;
			}
			sb->setplayer(p1,p2,level1,level2);
			playing=true;
			played=true;
		}else if(cmd=="setup"&&!playing&&!WTB){
			cout<<"Setup mode...."<<endl;
			if(open&&g){gd->clear();}
			td->clear();//default board;
			td->print();
			if(!open&&g){gd->open();open=true;gd->clear();}
			delete sb;
			sb=new Setupboard(b);
			sb->setup();
			sb->returnboard();
			WTB=true;//write to board
		}else if(cmd=="move"&&playing){
//	{	while(cp1&&cp2){
			b->makeMove();
			if(b->checkwin()){
				td->print();
				td->clear();//clear to default setting
				WTB=false;
				playing=false;
				b->clearboard();
	//			break;
			}else{
				td->print();
			}
//		}
//	}
		}else if(cmd=="resign"&&playing){
			b->resign();
			td->clear();
			WTB=false;
			playing=false;
			b->clearboard();
		}else if(cin.fail()){
			if(!playing){
				b->clearboard();
				if(played){b->result();}
				break;
			}else{
				cin.clear();
				cerr<<"cannot quit while playing "<<endl;
			}
		}else{
			cerr<<"Invalid command"<<endl;
		}
	}
}
