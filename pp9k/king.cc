#include "king.h"
#include "player.h"

using namespace std;

bool King::checkMove(int ex, int ey){
//determind castling
//cerr<<x<<y<<ex<<ey<<endl;
  if((2 == ex - x || 2 == x - ex ) && y == ey){
    if(numMove != 0 || 5 != x || ((0 == group && 1 != y) || (1 == group && 8 != y))){
      //cerr << "Moved king cannot execute castling." << endl;
      return false;
    }
    player->castling(x,ex,ey);
    return false;
  }
//cerr << "from (" << x << "," << y << ") to (" << ex << "," << ey << ")" << endl;
  if((x == ex && (y + 1 == ey || y - 1 == ey)) ||
     (y == ey && (x + 1 == ex || x - 1 == ex)) ||
     (x - ex == y - ey && ((-1 == ex - x && -1 == ey - y) || (1 == ex - x && 1 == ey - y))) ||
     (x - ex == ey - y && ((1 == ex - x && -1 == ey - y) || (-1 == ex - x && 1 == ey - y)))){
    return true;
  } else {
    //cerr << "Ending coordinates are not reachable." << endl;
    return false;
  }
}

bool King::checkBlock(int ex, int ey){
  if(x == ex && y == ey){// castling case
    return false;
  }
  // check if the pathing is blocked
  // check destination
//cerr<<"null and samegroup - "<<(player->checkNull(ex,ey))<<(group != player->getGroup(ex,ey))<<endl;
  if(player->checkNull(ex,ey) || group != player->getGroup(ex,ey)) {
    return false;
  } else {
    //cerr << "king: Ending coordinates is one of your chessman." << endl;
    return true;
  }
}

King::King(int x, int y, char c, Player *player):
  Chessmen(x,y,c,player){}

King::~King(){}

void King::makeMove(int ex, int ey){
//cerr << "king move from (" << x << "," << y << ") to (" << ex << "," << ey << ")" << endl;
  numMove++;
  x = ex;
  y = ey;
}

char King::getType(){
  return type;
}

int King::getCoords(){
  return x * 10 + y;
}

int King::getGroup(){
  return group;
}

int King::getLastMoveDistance(){}

string King::possibleMove(){
  ostringstream oss;
  for(int i = x-1; i <= x+1; i++){
    for(int j = y-1; j <= y+1; j++){
      if(i == x && j == y){
        continue;
      }
      if(1 <= i && i <= 8 && 1 <= j && j <= 8){
        oss<<i<<j;
      }
    }
  }
  return oss.str();
}

void King::resetLastMoveDistance(int d){}










