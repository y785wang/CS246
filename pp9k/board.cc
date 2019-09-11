#include "board.h"
#include "human.h"
#include "player.h"
#include "computer.h"
#include <iostream>

using namespace std;

Board::Board(GameNotification* g):gn(g){
	board=NULL;
	score[0]=0;
	score[1]=0;
	w=NULL;
	b=NULL;
}
void Board::setboard(int** b){
	board=b;
}
	
void Board::result(){
	cout<<"Final Score:"<<endl;
	double sw=score[0]/10.0;
	double sb=score[1]/10.0;
	cout<<"White: "<<sw<<endl;
	cout<<"Black: "<<sb<<endl;
}

void Board::resign(){
	string s="resign initialize fail";
	if(black){
		s="White  wins!";
		cout<<s<<endl;
		score[0]+=10;
	}else{
		s="Black  wins!";
		cout<<s<<endl;
		score[1]+=10;
	}
	gn->notify(score[0],score[1],'G',s);
}
void Board::clearboard(){
	if(board==NULL){return;}
	for(int c=0;c<9;c++){
		delete [] board[c];
	}
	delete [] board;
	delete w;
	delete b;
	board=NULL;
	w=NULL;
	b=NULL;
}


bool Board::checkwin(){
	char sign=board[0][0];
	char sign2=board[0][1];
	if(sign=='1'){//normal move
		gn->notify(board[1][0]-'0',board[2][0]-'0','-');
		gn->notify(board[3][0]-'0',board[4][0]-'0',board[5][0]);
	}else if(sign=='2'){//castling
		gn->notify(board[1][0]-'0',board[2][0]-'0','-',"rookf");
		gn->notify(board[3][0]-'0',board[4][0]-'0',board[board[3][0]-'0'][board[4][0]-'0'],"rookt");
		gn->notify(board[5][0]-'0',board[6][0]-'0','-',"kingf");
		gn->notify(board[7][0]-'0',board[8][0]-'0',board[board[7][0]-'0'][board[8][0]-'0'],"kingt");
	}else if(sign=='3'){//en pa balal
		gn->notify(board[1][0]-'0',board[2][0]-'0','-',"enf");
		gn->notify(board[5][0]-'0',board[6][0]-'0','-');
		gn->notify(board[3][0]-'0',board[4][0]-'0',board[board[3][0]-'0'][board[4][0]-'0'],"ent");
	}//------0  1
	if(sign2=='4'){//detect a check
		string Who=(!black)?"White is in check!":"Black is in check!";
		gn->notify(-1,-1,'C',Who);
		cout<<Who<<endl;
		//     0  1
	}else if(sign2=='5'){//
		string who="checkmate initialize fail";
		if(black){
			score[0]+=10;
			who="Checkmate! White wins!";
		}else{
			score[1]+=10;
			who="Checkmate! Black wins!";
		}
		gn->notify(score[0],score[1],'M',who);
		return true;
		///    0 1
	}else if(sign2=='6'){//Stalement
		string  who="Stalement!";
		cout<<who<<endl;
//		cout<<"before at board w is "<<score[0]<<endl;
//		cout<<"before at board b is "<<score[1]<<endl;
		score[0]=score[0]+5;
		score[1]=score[1]+5;
//		cout<<"after at board w is "<<score[0]<<endl;
//		cout<<"after at board b is "<<score[1]<<endl;
		gn->notify(score[0],score[1],'S',who);
		return true;
		// ???
	}else if(sign=='7'){//promotion
	//	char ch=(board[5][0]>'A')?'P':'p';
		gn->notify(board[1][0]-'0',board[2][0]-'0','-');
		gn->notify(board[3][0]-'0',board[4][0]-'0',board[5][0]);
	}
	return false;
}



void Board::makeMove(){
	//cout<<"Now black is "<<black<<endl;
	if(black){
		cout<<"black makes move"<<endl;
		b->makeMove();
	}else{
		cout<<"white makse move"<<endl;
		w->makeMove();
	}
cerr<<"make move successful"<<endl;
//	if(board[0][0]=='1'){
//		notify(board[1][0]-48,board[2][0]-48,'-',false);
//		notify(board[3][0]-48,board[4][0]-48,board[5][0],false);
//	}
	black=(black)?false:true;
}

void Board::setplayer(string p1,string p2,int lv1,int lv2){
	delete w;
	delete b;
	w=NULL;
	b=NULL;
	int b1,b2;//is bot or not
	if(p1=="human"){
		b1=0;
	   	w=new Human(board,0);
	}else{	
		b1=1;
	        w=new Computer(board,0);
		w->setLevel(lv1);	
	}
	if(p2=="human"){
		b2=0;
		b=new Human(board,1);
	}else{
		b2=1;
	        b=new Computer(board,1);	
		b->setLevel(lv2);
	///
	}
	w->connect(b);
	b->connect(w);
	gn->notify(b1,b2,'T',"");
}

void Board::setblack(bool b){
	black=b;
}

void Board::notify(int x,int y,char ch,bool p){
	gn->notify(x,y,ch,"",p);
}
