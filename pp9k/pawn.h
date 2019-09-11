#ifndef __PAWN_H__
#define __PAWN_H__
#include "chessmen.h"

class Pawn : public Chessmen{
 protected:
  int lastMoveDistance;
 public:
  Pawn(int, int, char, Player *);
  ~Pawn();
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
