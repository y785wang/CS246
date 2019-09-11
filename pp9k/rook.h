#ifndef __ROOK_H__
#define __ROOK_H__
#include "chessmen.h"

class Rook : public Chessmen{
 protected:
 public:
  Rook(int, int, char, Player *);
  ~Rook();
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
