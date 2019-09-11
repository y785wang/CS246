#ifndef __CHESSMEN_H__
#define __CHESSMEN_H__

#include <string>

class Player;

class Chessmen {

 protected:
  int x;
  int y;
  int numMove;
  Player *player;
  int group;
  char type;
 public:
  Chessmen(int, int, char, Player *);
  virtual ~Chessmen() = 0;
  virtual bool checkMove(int, int) = 0;
  virtual bool checkBlock(int, int) = 0;
  virtual void makeMove(int, int) = 0;
  virtual char getType() = 0;
  virtual int getCoords() = 0;
  virtual int getGroup() = 0;
  virtual int getLastMoveDistance() = 0;
  int getNumMove();
  virtual std::string possibleMove() = 0;
  void reduceNumMoveByTwo();
  virtual void resetLastMoveDistance(int) = 0;
};

#endif
