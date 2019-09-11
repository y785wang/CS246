#include "chessmen.h"

Chessmen::Chessmen(int x, int y, char c, Player *player):
  x(x),y(y),type(c),numMove(0),player(player){
  if(65 <= c && c <= 90){
    group = 0;
  } else {
    group = 1;
  }
}

Chessmen::~Chessmen(){}

int Chessmen::getNumMove(){
  return numMove;
}

void Chessmen::reduceNumMoveByTwo(){
  numMove -= 2;
}


