#include "setupboard.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Setupboard::Setupboard(Board*b):Setboard(b){}

void Setupboard::setup(){
	p=true;// allow to print to textdisplay
	cout<<"setup Mode begins,Note! Required one king for each player"<<endl;
	cout<<"No Pawn can reach the end of the opponent's place"<<endl;
	cout<<"King can not in check"<<endl;
	cout<<"If no colour set then will be set White by default"<<endl;
        while(true){
                string func;
                char c;//chessman
                char x;
                char y;
                char colour;
                cin>>func;
                if(func=="+"){
                        cin>>c>>x>>y;
                        set(x,y,c,'+');
                }else if(func=="-"){
                        cin>>x>>y;
                       	set(x,y,'0','-');
                }else if(func=="="){
                        cin>>colour;
                        if(colour=='W'){
                  		b->setblack(false);
                        }else if(colour=='B'){
                                b->setblack(true);
                        }else{
                                cerr<<"Invalid colour"<<endl;
                        }
                }else if(func=="done"){
                        if(setupVarify()){
				p=false;
				break;
                        }else{
                                continue;
                        }
		}else if(cin.fail()){
			cin.clear();
			cerr<<"Exit by entering done"<<endl;
                }else{
                        cerr<<"SetupMode:Invalid command"<<endl;
                }
        }
}


bool Setupboard::setupVarify(){
        if(king!=1||KING!=1){
		cerr<<"You have "<<king+KING;
		cerr<<" Kings.Expected 2,and one for each"<<endl;
		return false;
	}
        for(int r=1;r<9;r++){
		if(board[r][1]=='p'||board[r][8]=='p'||board[r][1]=='P'||board[r][8]=='P'){
			cerr<<"Invalid the pawn reaches end"<<endl;
			return false;
		}
	}
        if(NUM>16||num>16){
                cerr<<"One player has too many chessmen,cannot exceed 16"<<endl;
                return false;
        }       
//cout<<king<<" "<<KING<<endl;
//cout<<num<<" "<<NUM<<endl;
	if(!danger(0)||!danger(1)){//0 K 1 k
		cerr<<"One of the Kings in check"<<endl;
		return false;
	}
	
        return true;
}


bool Setupboard::danger(int K){
	int x=board[0][K+1]/10;//k=0 K coords
	int y=board[0][K+1]%10;
	int q=!K?81+32:81;
	int r=!K?82+32:82;
	int p=!K?80+32:80;
	int n=!K?78+32:78;
	int k=!K?75+32:75;
	int b=!K?66+32:75;
	int i;
/////////////////////////////////////////////////////////////////
	for(i=1;x+i<9;i++){        //------>
		if(board[x+i][y]==q||board[x+i][y]==r){
			cout<<"king is in check:by qeen or rook from right"<<endl;
			return false;
		}else if(board[x+i][y]!=0){
			break;
		}
	}
//	cout<<1<<endl;
/////////////////////////////////////////////////////////
        for(i=1;x-i>0;i++){        //<--------------
                if(board[x-i][y]==q||board[x-i][y]==r){
                        cout<<"king is in check:by queen or rook from left"<<endl;
                        return false;
                }else if(board[x-i][y]!=0){
                        break;
                }
        }
	//cout<<2<<endl;
/////////////////////////////////////////////////////////////////////
        for(i=1;y+i<9;i++){    //   ^^^^^^^^^^^
                if(board[x][y+i]==q||board[x][y+i]==r){
                        cout<<"king is in check:by queen or rook from top"<<endl;
                        return false;
                }else if(board[x][y+i]!=0){
                        break;
                }
        }
//	cout<<3<<endl;
////////////////////////////////////////////////////////////////
        for(i=1;y-i>0;i++){        //vvvvvvvvvvvvv
                if(board[x][y-i]==q||board[x][y-i]==r){
                        cout<<"king is in check:by queen or rook from bottom"<<endl;
                        return false;
                }else if(board[x][y-i]!=0){
                        break;
                }
        }
//	cout<<4<<endl;
///////////////////////////////////////////////////////////////
	for(i=1;x+i<9&&y+i<9;i++){        // //////////////->
                if(board[x+i][y+i]==q||board[x+i][y+i]==b){
                        cout<<"king is in check:by queen or bishop from right top"<<endl;
                        return false;
                }else if(board[x+i][y+i]!=0){
                        break;
                }
        }
//	cout<<5<<endl;
/////////////////////////////////////////////////////////
        for(i=1;x-i>0&&y-i>0;i++){        //<-////////
                if(board[x-i][y-i]==q||board[x-i][y-i]==b){
	cout<<x-i<<" "<<y-i<<board[x-i][y-i]<<endl;
                        cout<<"king is in check:by queen or bishop from left bottom"<<endl;
                        return false;
                }else if(board[x-i][y-i]!=0){
                        break;
                }
        }
//	cout<<6<<endl;
////////////////////////////////////////////////
        for(i=1;x+i<9&&y-i>0;i++){        //\\\\\\\\\\\\\\\\\\->
                if(board[x+i][y-i]==q||board[x+i][y-i]==b){
                        cout<<"king is in check:by queen or bishop from right bottom"<<endl;
                        return false;
                }else if(board[x+i][y-i]!=0){
                        break;
                }
        }
//	cout<<7<<endl;
//////////////////////////////////////////////////////
        for(i=1;x-i>0&&y+i<9;i++){        //<-\\/
                if(board[x-i][y+i]==q||board[x-i][y+i]==b){
                        cout<<"king is in check:by queen or bishop from left top"<<endl;
                        return false;
                }else if(board[x-i][y+i]!=0){
                        break;
                }
	}
//	cout<<8<<endl;
/////////////////////////////////
	if(!K){/////////////ppppppp
		if(x+1<9&&y+1<9&&board[x+1][y+1]==p){
			cout<<"king is in check:by pawn"<<endl;
			return false;
		}else if(x-1>0&&y+1<9&&board[x-1][y+1]==p){
			cout<<"king is in check:by pawn"<<endl;
			return false;
		}
	}else{
	        if(x+1<9&&y-1>0&&board[x+1][y-1]==p){
                        cout<<"king is in check:by pawn"<<endl;
                        return false;
                }else if(x-1>0&&y-1>0&&(board[x-1][y-1]==p)){
                        cout<<"king is in check:by pawn"<<endl;
                        return false;
                }	
	}
//	cout<<9<<endl;
//////////////////////////////////////////////
	if(x+1<9&&board[x+1][y]==k||//king
	   x-1>0&&board[x-1][y]==k||
	   y+1<9&&board[x][y+1]==k||
	   y-1>0&&board[x][y-1]==k||
	   x+1<9&&y+1<9&&board[x+1][y+1]==k||
	   x-1>0&&y-1>0&&board[x-1][y-1]==k||
	   x+1<9&&y-1>0&&board[x+1][y-1]==k||
	   x-1>0&&y+1<9&&board[x-1][y+1]==k){
		cout<<"King is in check: by king"<<endl;
		return false;
	}
//	cout<<10<<endl;
/////////////////////////////////////
	if((x+1<9&&y+2<9&&board[x+1][y+2]==n)||
	   (x+1<9&&y-2>0&&board[x+1][y-2]==n)||
	   (x-1>0&&y+2<9&&board[x-1][y+2]==n)||
	   (x-1>0&&y-2>0&&board[x-1][y-2]==n)||
	   (x+2<9&&y+1<9&&board[x+2][y+1]==n)||
	   (x+2<9&&y-1>0&&board[x+2][y-1]==n)||
	   (x-2>0&&y+1<9&&board[x-2][y+1]==n)||
	   (x-2>0&&y-1>0&&board[x-2][y-1]==n)){
		cout<<"king is in check: by Knight"<<endl;
		return false;
	}
	return true;	
}
