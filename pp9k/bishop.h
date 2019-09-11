#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "chessmen.h"

class Bishop : public Chessmen{
 protected:
 public:
  Bishop(int, int, char, Player *);
  ~Bishop();
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
