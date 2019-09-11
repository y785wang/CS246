#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "chessmen.h"

class Knight : public Chessmen{
 protected:
 public:
  Knight(int, int, char, Player *);
  ~Knight();
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
