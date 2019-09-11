#include "graphicdisplay.h"
#include <iostream>
#include <sstream>
#include <string>
#include "window.h"
using std::ostream;
using std::cout;
using std::endl;
using std::cin;
using std::stringstream;
using std::string;


GraphicDisplay::GraphicDisplay(int n):View(n),face_change(false){}

GraphicDisplay::~GraphicDisplay(){
   	delete x;
}

                                                 //chr=  
void GraphicDisplay::notify(int r,int c,char ch,string who=""){//G is resign
	//cout<<" this is r and c "<<r<<" "<<c<<endl;
     	int div=504/(gridSize-1);                //C is check
     	int colour=1;
     	stringstream s;                          //T is setplayer
	string wscore;				//S is stalement
	string bscore;                         ///M is checkmate
	bool isChess=true;
	x->fillRectangle(3*div-28,3*div,div*2,div,1);//6
	x->fillRectangle(5*div-28,3*div,div*3,div,0);//6
	if(ch=='G'||ch=='S'||ch=='M'){// white wins
		if(ch=='S'||ch=='G'){who="          "+who;}
		s<<r/10;
		if(r%10==5){s<<".5";}
		s<<" "<<c/10;
		if(c%10==5){s<<".5";}
		s>>wscore;
		s>>bscore;
		x->fillRectangle(0,div,div*2,div+40,1);
		x->fillRectangle(7*div,2*div-50,div*2+40,div+40,0);
		x->drawStr(2*div-20,1*div,who,2);//6
		x->drawStr(4*div-20,2*div,"White:  "+wscore,2);	
		x->drawStr(4*div-20,3*div,"Black:  "+bscore,2);
		if(ch=='G'||ch=='M'){
			if(who[0]=='W'||who[12]=='W'){
            	    		x->drawStr(0,div*2,"(  ^.^)",0);
                		x->drawStr(7*div+20,2*div,"(!.!  )",1);
			}else{
            	    		x->drawStr(0,div*2,"(  QAQ)",0);
                		x->drawStr(7*div+20,2*div,"(^.^  )",1);
			}
		}else if(ch=='S'){
                        x->drawStr(0,div*2,"(  X.X)",0);
                        x->drawStr(7*div+20,2*div,"(#_#  )",1);

		}
		face_change=true;
		isChess=false;
	}else if(ch=='C'){
                x->fillRectangle(0,div,div*2,div+40,1);//remove
                x->drawStr(0,div*2,"(  ._.)",0);
                x->fillRectangle(7*div,2*div-50,div*2+40,div+40,0);//remove
                x->drawStr(7*div+20,2*div,"(._.  )",1);
		x->drawStr(150,4*div,who,2);
		isChess=false;
		face_change=true;
	}else if(ch=='T'){
		isChess=false;
		x->drawStr(0,div-10,"White",0);
		x->drawStr(0,div*2,"(  ~_~)",0);
		x->drawStr(7*div+20,div,"Black",1);
		x->drawStr(7*div+20,2*div,"(^_^  )",1);
		isChess=false;
	}
	if(isChess){
     		s<<ch;
     		string ss;
     		s>>ss;
      		if(c%2==0&&r%2==1||c%2==1&&r%2==0){
   			x->fillRectangle(r*div,(8-c+4)*div,div,div,8);// 
      	 	}else{
			x->fillRectangle(r*div,(8-c+4)*div,div,div,3);// 
        	}
    		if((r>0&&r<gridSize)&&(c>0&&r<gridSize)){
     			int colour=1;
     			if(ch>='A'&&ch<='Z'){colour=0;}
     			stringstream sss;
     			sss<<ch;
     			string ss;
        		sss>>ss;
			if(ch!='-'){
      				x->drawBigString(r*div+6,(9-c+4)*div-10,"  "+ss,colour);
			if(face_change){
                		x->fillRectangle(0,div,div*2,div+40,1);//remove
                		x->fillRectangle(7*div,2*div-50,div*2+40,div+40,0);//remove
				x->drawStr(0,div*2,"(  ~_~)",0);
				x->drawStr(7*div+20,2*div,"(^_^  )",1);
				face_change=false;

			}
	/*			if(can_eat==true){
					if(colour==0){//white
			                 x->fillRectangle(0,div,div*2,div+20,1);
					 x->drawStr(0,div*2,"(#  '^')#",0);
					}else{
			                 x->fillRectangle(7*div+20,2*div-40,div*2,div,0);
					 x->drawStr(7*div+20,2*div,"~(_^_  )~",1);
					}
				}*/
   			}
	 	
		}
	}
}

void GraphicDisplay::print(){}
///clear to deafult background
void GraphicDisplay::clear(){
  	int div=504/(gridSize-1);
	char num='8';
	char letter='a';
	string str;
	for(int c=0;c<9;c++){
		for(int r=0;r<13;r++){
			if(r>3&&c==0){//left bar
              			x->fillRectangle(0,r*div,div,div,5);
                		stringstream s;
                		s<<num--;
                		s>>str;
                		x->drawBigString(10,(r+1)*div-10," "+str,1);//num
			}else if(r==12&&c>0){
              			x->fillRectangle(c*div,12*div,div,div,5);//bottom
          		        stringstream s;
                	 	s<<letter++;
                		s>>str;
                	 	x->drawBigString(c*div+7,(9+4)*div-10," "+str,1);//letter
			}else if(r<4&&c<4) {
				x->fillRectangle(c*div,r*div,div,div,1);//top scr
			}else if(r<4&&c==4){
				x->fillRectangle(c*div-28,r*div,div,div,1);//to
		    	}else if(r<4&&c>=4){
				x->fillRectangle(c*div-28,r*div,div,div,0);//to
	        	}else if(r>3){
				if(c%2==0&&r%2==0||c%2==1&&r%2==1){
//// print chessmen info
					x->fillRectangle(c*div,r*div,div,div,3);
				}else{
					x->fillRectangle(c*div,r*div,div,div,8);

				}
			}
		}
	}
	x->fillRectangle(0,12*div,div,div,1);
	x->fillRectangle(8*div,0,div,div*4,0);
}
void GraphicDisplay::open(){
	x=new Xwindow(504,728);
  	x->fillRectangle(0,0,504,504,0);//56
}
