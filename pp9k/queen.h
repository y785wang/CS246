#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "chessmen.h"

class Queen : public Chessmen{
 protected:
 public:
  Queen(int, int, char, Player *);
  ~Queen();
  bool checkMove(int, int);
  bool checkBlock(int, int);
  void makeMove(int, int);
  char getType();
  int getCoords();
  int getGroup();
  int getLastMoveDistance();
  std::string possibleMove();
  void resetLastMoveDistance(int);
};

#endif
