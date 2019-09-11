#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "chessmen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Player {
 protected:
  bool doublecheck;
  std::string possibleMove;
  bool activated;
  bool isCastling;
  bool isEnPassant;
  bool isCheck;
  int group;
  Player *opponentPlayer;
  int size;
  Chessmen **chessmen; //array[16]
  int **board; // 9*9 grid
  bool checkCaptured(int, int, int, int);
  bool checkCaptured(int, int, int, int, int);
  int enPassant(int, int); // called by another enPassant
  void doubleCheck();
  void singleCheck(int, int);
 public:
  Player(int **, int);
  virtual ~Player() = 0;
  void connect(Player *);
  virtual void makeMove() = 0;
  bool checkNull(int, int); // called by chessmen
  int getGroup(int, int); // called by chessmen
  bool checkCaptured(int, int); // called by another computer
  void delinkChessmen(int, int); // called by another player
  void castling(int, int, int); // called by king
  bool enPassant(int, int, int, int);
  int getKingCoords(); // called by another player
  void checkNotify(std::string); // called by another player
  void checkDraw(int); // called by another player
  void pawnPromotion(int, int, int, Player *); // called by pawn
  virtual void setLevel(int) = 0;
};

#endif
