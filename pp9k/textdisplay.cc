#include "textdisplay.h"
#include <iostream>
#include <string>
using std::endl;
using std::cout;
using std::string;
TextDisplay::TextDisplay(int n):View(n){
      	theDisplay=new char*[n];
      	for(int i=0;i<n;i++){
         	theDisplay[i]=new char[n];
         	for(int j=0;j<n;j++){
 	          	theDisplay[i][j]='0';
     		}
   	}
}

TextDisplay::~TextDisplay(){
    	for(int i=0;i<gridSize;i++){
         	delete[] theDisplay[i];
      	}
      	delete[] theDisplay;
}


void TextDisplay::notify(int r,int c,char ch,string word=""){
	if(ch=='C'||ch=='M'||ch=='S'||ch=='G'){
		return;
	}
	if(ch=='-'){
		char a;
		if((c+2)%2==0&&r%2==0||(c+2)%2==1&&r%2==1){
			a='_';
		}else{
			a=' ';
		}
		theDisplay[r+1][8-c]=a;
	}else{
     		theDisplay[r+1][8-c]=ch;
	}
}

void TextDisplay::print(){
   	for(int r=0;r<gridSize;r++){
       		for(int c=0;c<gridSize;c++){
         		cout<<theDisplay[c][r];
       		}
       	cout<<endl;
     	}
}


void TextDisplay::clear(){
	char a;
	char k='8';
	for(int i=0;i<gridSize-2;i++){
		theDisplay[0][i]=k;
		theDisplay[1][i]=' ';
	       
		k=k-1;
	}
	k='a';
	for(int j=2;j<gridSize;j++){
		theDisplay[j][8]=' ';
		theDisplay[j][9]=k;
		k=k+1;
	}
	theDisplay[0][8]=' ';
	theDisplay[0][9]=' ';
	theDisplay[1][8]=' ';
	theDisplay[1][9]=' ';
	for(int c=2;c<gridSize;c++){
		for(int r=0;r<gridSize-2;r++){
			if(((c+2)%2==0&&r%2==0)||((c+2)%2==1&&r%2==1)){
                       		a=' ';
                	}else{
                        	a='_';
                	}
			theDisplay[c][r]=a;
		}
	}
}
