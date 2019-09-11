#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>
#include <sstream>
#include <string>
class View {
  protected:
    const int gridSize;
  public:
    View(int n);
 virtual void notify(int,int , char ch,std::string="none") = 0;
 virtual void clear()=0;
 virtual void print() = 0;
 virtual void open()=0;   
 virtual ~View() = 0;
};

#endif
