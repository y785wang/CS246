#include "bishop.h"
#include "player.h"

using namespace std;

bool Bishop::checkMove(int ex, int ey){
  if(ey - y == ex - x || ey - y == x - ex) {
    return true;
  } else {
    //cerr << "Ending coordinates are not reachable." << endl;
    return false;
  }
}

bool Bishop::checkBlock(int ex,int ey){
  // check if the pathing is blocked
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
  // check destination
  if(player->checkNull(ex,ey) || group != player->getGroup(ex,ey)){
    //cerr<<"here2"<<endl;
    return false;
  } else {
    //cerr << "Ending coordinates is one of your chessman." << endl;
    return true;
  }
}

Bishop::Bishop(int x, int y, char c, Player *player):
  Chessmen(x,y,c,player){}

Bishop::~Bishop(){}

void Bishop::makeMove(int ex, int ey){
  numMove++;
  x = ex;
  y = ey;
}

char Bishop::getType(){
  return type;
}

int Bishop::getCoords(){
  return x * 10 + y;
}

int Bishop::getGroup(){
  return group;
}

int Bishop::getLastMoveDistance(){}

string Bishop::possibleMove(){
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
  return oss.str();
}

void Bishop::resetLastMoveDistance(int d){}


