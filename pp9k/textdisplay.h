#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
#include "view.h"
#include <string>
class TextDisplay : public View{
  char **theDisplay; 
  void setdisplay();        
 public:
  TextDisplay(int n); //one arg constructor where the parameter is the gridSize
  ~TextDisplay(); //dtor
  virtual void notify(int,int, char ch,std::string);  
  virtual void print();	
  virtual void clear();
  virtual void open(){}
};

#endif
