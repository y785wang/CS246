#include "queen.h"
#include "player.h"

using namespace std;

bool Queen::checkMove(int ex, int ey){
  if(ey - y == ex - x || ey - y == x - ex || x == ex || y == ey) {
    return true;
  } else {
    //cerr << "Ending coordinates are not reachable." << endl;
    return false;
  }
}

bool Queen::checkBlock(int ex,int ey){
  // check if the pathing is blocked
  if(ex == x || ey == y){// moving like rook
    int n;
    if(ex == x){
      n = ey - y > 0 ? ey - y : y - ey;
    } else {
      n = ex - x > 0 ? ex - x : x - ex;
    }
    int deltaX = (ex - x) / n;
    int deltaY = (ey - y) / n;
    n--;
    for(int i = 1; i <= n; i++){
      if(! player->checkNull(x + deltaX * i, y + deltaY * i)){
//cerr << "checking " << x + deltaX * i << " " << y + deltaY * i << endl;
        //cerr << "Moving path is blocked." << endl;
        return true;
      }
    }
  } else {// moving like bishop
    int n = ex - x > 0 ? ex - x : x - ex;
    int deltaX = (ex - x) / n;
    int deltaY = (ey - y) / n;
    n--;
    for(int i = 1; i <= n; i++){
      if(! player->checkNull(x + deltaX * i, y + deltaY * i)){
        //cerr << "Moving path is blocked." << endl;
        return true;
      }
    }
  }
  // check destination
  if(player->checkNull(ex,ey) || group != player->getGroup(ex,ey)) {
    return false;
  } else {
    //cerr << "Ending coordinates is one of your chessman." << endl;
    return true;
  }
}

Queen::Queen(int x, int y, char c, Player *player):
  Chessmen(x,y,c,player){}

Queen::~Queen(){}

void Queen::makeMove(int ex, int ey){
  numMove++;
  x = ex;
  y = ey;
}

char Queen::getType(){
  return type;
}

int Queen::getCoords(){
  return x * 10 + y;
}

int Queen::getGroup(){
  return group;
}

int Queen::getLastMoveDistance(){}

string Queen::possibleMove(){
  ostringstream oss;
  for(int i=1; ; i++){
    if(x+1*i <= 8 && y+1*i <= 8){
      oss<<x+1*i<<y+1*i;
    }else{
      break;
    }
  }
  for(int i=1; ; i++){
    if(x+1*i <= 8 && 1 <= y-1*i){
      oss<<x+1*i<<y-1*i;
    }else{
      break;
    }
  }
  for(int i=1; ; i++){
    if(1 <= x-1*i && y+1*i <= 8){
      oss<<x-1*i<<y+1*i;
    }else{
      break;
    }
  }
  for(int i=1; ; i++){
    if(1 <= x-1*i && 1 <= y-1*i){
      oss<<x-1*i<<y-1*i;
    }else{
      break;
    }
  }
  oss<<" ";
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

void Queen::resetLastMoveDistance(int d){}


