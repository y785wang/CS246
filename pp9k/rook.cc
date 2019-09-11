#include "rook.h"
#include "player.h"

using namespace std;

bool Rook::checkMove(int ex,int ey){ 
//cerr<<"rook try to move from "<<x<<y<<" to "<<ex<<","<<ey<<endl;
  if(x == ex || y == ey) {
    return true;
  } else {
    //cerr << "Ending coordinates are not reachable." << endl;
    return false;
  }
}

bool Rook::checkBlock(int ex,int ey){
//cerr << "here1" << endl;
  // check if the pathing is blocked
  int n;
  if(ex == x){
    n = ey - y > 0 ? ey - y : y - ey;
  } else {
    n = ex - x > 0 ? ex - x : x - ex;
  }
  int deltaX = (ex - x) / n;
  int deltaY = (ey - y) / n;
  n--;
//cerr << "x  = " << x << ", y = " << y << endl;
//cerr << "ex  = " << ex << ", ey = " << ey << endl;
//cerr << "deltaX = " << deltaX << endl;
//cerr << "deltaY = " << deltaY << endl;
//cerr << "n = " << n << endl;
  for(int i = 1; i <= n; i++){
//cerr << "checking " << x + deltaX * i << " " << y + deltaY * i << endl;
    if(! player->checkNull(x + deltaX * i, y + deltaY * i)){
      //cerr << "Moving path is blocked." << endl;
      return true;
    }
  }
  // check destination
  if(player->checkNull(ex,ey) || group != player->getGroup(ex,ey)) {
//cerr << "here2" << endl;
    return false;
  } else {
    //cerr << "Ending coordinates is one of your chessman." << endl;
    return true;
  }
}

Rook::Rook(int x, int y, char c, Player *player):
  Chessmen(x,y,c,player){}

Rook::~Rook(){}

void Rook::makeMove(int ex, int ey){
//cerr << "rook move from (" << x << "," << y << ") to (" << ex << "," << ey << ")" << endl;
  numMove++;
  x = ex;
  y = ey;
}

char Rook::getType(){
  return type;
}

int Rook::getCoords(){
  return x * 10 + y;
}

int Rook::getGroup(){
  return group;
}

int Rook::getLastMoveDistance(){}

string Rook::possibleMove(){
  ostringstream oss;
  for(int i = 1; i <= 8; i++){
    if(i == y){
      continue;
    }
    oss<<x<<i;
  }
  for(int i = 1; i <= 8; i++){
    if(i == x){
      continue;
    }
    oss<<i<<y;
  }
  return oss.str();
}

void Rook::resetLastMoveDistance(int d){}










