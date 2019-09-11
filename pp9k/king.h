#ifndef __KING_H__
#define __KING_H__
#include "chessmen.h"

class King : public Chessmen{
 protected:
 public:
  King(int, int, char, Player *);
  ~King();
  bool checkMove(int, int);
  bool checkBlock(int, int);
  bool checkCaptured();
  void makeMove(int, int);
  char getType();
  int getCoords();
  int getGroup();
  int getLastMoveDistance();
  std::string possibleMove();
  void resetLastMoveDistance(int);
};

#endif
