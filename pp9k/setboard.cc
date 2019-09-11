#include "setboard.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cerr;
using std::cin;
// gn-------ctor--->Board
// player,black------setplayer---->
// clearboard----------clearboard---->
Setboard::~Setboard(){}
Setboard::Setboard(Board*b):b(b){
	p=false;
        king=0;KING=0;num=0;NUM=0;
       	board=new int*[9];
	for(int c=0;c<9;c++){
     		board[c]=new int[9];
       		for(int r=0;r<9;r++){
 			board[c][r]='0';
		}
	}
}

void Setboard::returnboard(){
	b->setboard(board);
	board=NULL;
}


void Setboard::setplayer(string p1,string p2,int lv1,int lv2){
	b->setplayer(p1,p2,lv1,lv2);
	b=NULL;
}

void Setboard::setup(){
	cout<<"default setting startring"<<endl;
       	for(int c=1;c<9;c++){
    		set(c+96,'2','P','+');
       	        set(c+96,'7','p','+');
       	}                        //set rook
       	set('a','8','r','+');
       	set('a','1','R','+');
       	set('h','8','r','+');
       	set('h','1','R','+');
       	set('b','8','n','+');  //set knight
       	set('b','1','N','+');
       	set('g','8','n','+');  //set knight
       	set('g','1','N','+');
       	set('e','8','k','+');
       	set('e','1','K','+');
       	set('c','8','b','+');//set bishop
       	set('f','8','b','+');
       	set('c','1','B','+');
       	set('f','1','B','+');
       	set('d','8','q','+');//queen
       	set('d','1','Q','+');
}


void Setboard::set(char cx,char cy,char chess,char func){//x coord y coord
	int x=cx-96,y=cy-'0',valid=0;
        if(x>=1&&x<=8&&y>=1&&y<=8){
                valid++;
        }else{
                cerr<<"Invalid move,Plz try again";
                cerr<<" x has to be a~h y has to be 1~8"<<endl;
        }
        if(valid==1&&func=='-'){
		if(board[x][y]=='K'){//K=1000,k=100
			NUM--;//num of K
			KING--;
		}else if(board[x][y]=='k'){
			king--;//num of k
			num--;
		}else if(board[x][y]>='A'&&board[x][y]<='Z'){
			NUM--;
		}else if(board[x][y]>='a'&&board[x][y]<='z'){
			num--;
		}
		board[x][y]=0;
		b->notify(x,y,'-',p);
        }
        if(valid==1&&func=='+'){
		if(board[x][y]=='K'){KING--;NUM--;}
		if(board[x][y]=='k'){king--;num--;}
        	if(chess=='K'){
			board[0][1]=x*10+y;//coord of K
			KING++;
			valid++;
                }else if(chess=='k'){
			board[0][2]=x*10+y;
			king++;
			valid++;
          	}
                else if(chess=='Q'||chess=='q'){valid++;}
                else if(chess=='B'||chess=='b'){valid++;}
                else if(chess=='R'||chess=='r'){valid++;}
                else if(chess=='N'||chess=='n'){valid++;}
                else if(chess=='P'||chess=='p'){valid++;}
           	else{
                cerr<<"Invalid chessman: "<<chess<<"Plz try again and";
                cerr<<" choose one of K Q B R N P"<<endl;
		}
		if(valid==2){
			if(chess<='Z'&&chess>='A'){
				NUM++;
				if(board[x][y]>='a'&&board[x][y]<='z'){NUM--;num++;}
			}else{
				num++;
				if(board[x][y]>='A'&&board[x][y]<='Z'){num--;NUM++;}
			}
	//		cout<<"setting"<<endl;
			board[x][y]=chess;
	//		cout<<"complete"<<endl;
			b->notify(x,y,chess,p);
	//		cout<<"notify complete"<<endl;
		}
        }
}

