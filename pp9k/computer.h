#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer : public Player {
 protected:
  int level;
 public:
  Computer (int**, int);
  ~Computer ();
  void makeMove();
  void setLevel(int);
};

#endif
