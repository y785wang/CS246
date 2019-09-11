#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

class Human : public Player {
 protected:
 public:
  Human(int**, int);
  ~Human();
  void makeMove();
  void setLevel(int);
};

#endif
