#ifndef __GraphicDisplay_H__
#define __GraphicDisplay_H__
#include "view.h"
#include "window.h"
#include <iostream>
#include <string>
class GraphicDisplay:public View{
      Xwindow *x;
      bool face_change;
  public:
      GraphicDisplay(int);
      ~GraphicDisplay();
      virtual void notify(int,int ,char,std::string);
      virtual void print();
      virtual void clear();
      void open();
};
#endif
