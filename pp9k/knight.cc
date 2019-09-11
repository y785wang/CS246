#include "knight.h"
#include "player.h"

using namespace std;

bool Knight::checkMove(int ex, int ey){
  if((x + 1 == ex && (y + 2 == ey || y - 2 == ey)) ||
     (x + 2 == ex && (y + 1 == ey || y - 1 == ey)) ||
     (x - 1 == ex && (y + 2 == ey || y - 2 == ey)) ||
     (x - 2 == ex && (y + 1 == ey || y - 1 == ey))){
    return true;
  } else {
    return false;
  }
}

bool Knight::checkBlock(int ex, int ey){
  // check if the pathing is blocked
  // check destination
  if(player->checkNull(ex,ey) || group != player->getGroup(ex,ey)){
    return false;
  } else {
    //cerr << "Ending coordinates is one of your chessman." << endl;
    return true;
  }
}

Knight::Knight(int x, int y, char c, Player *player):
  Chessmen(x,y,c,player){}

Knight::~Knight(){}

void Knight::makeMove(int ex, int ey){
  numMove++;
  x = ex;
  y = ey;
}

char Knight::getType(){
  return type;
}

int Knight::getCoords(){
  return x * 10 + y;
}

int Knight::getGroup(){
  return group;
}

int Knight::getLastMoveDistance(){}

string Knight::possibleMove(){
  ostringstream oss;
  if(x+2 <= 8 && y+1 <= 8){
    oss<<x+2<<y+1;
  }
  if(x+2 <= 8 && 1 <= y-1){
    oss<<x+2<<y-1;
  }
  if(x+1 <= 8 && y+2 <= 8){
    oss<<x+1<<y+2;
  }
  if(x+1 <= 8 && 1 <= y-2){
    oss<<x+1<<y-2;
  }
  if(1 <= x-2 && y+1 <= 8){
    oss<<x-2<<y+1;
  }
  if(1 <= x-2 && 1 <= y-1){
    oss<<x-2<<y-1;
  }
  if(1 <= x-1 && y+2 <= 8){
    oss<<x-1<<y+2;
  }
  if(1 <= x-1 && 1 <= y-2){
    oss<<x-1<<y-2;
  }
  return oss.str();
}

void Knight::resetLastMoveDistance(int d){}









