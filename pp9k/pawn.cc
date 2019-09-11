#include "pawn.h"
#include "player.h"

using namespace std;

bool Pawn::checkMove(int ex, int ey){
  if(0 == group){
    if((x == ex && (y + 1 == ey || (y + 2 == ey && 0 == numMove))) ||
       (x + 1 == ex && y + 1 == ey) ||
       (x - 1 == ex && y + 1 == ey)) {
      return true;
    } else {
      //cerr << "Ending coordinates are not reachable." << endl;
      return false;
    }
  } else {
    if((x == ex && (y - 1 == ey || (y - 2 == ey && 0 == numMove))) ||
       (x + 1 == ex && y - 1 == ey) ||
       (x - 1 == ex && y - 1 == ey)) {
      return true;
    } else {
      //cerr << "Ending coordinates are not reachable." << endl;
      return false;
    }
  }
}

bool Pawn::checkBlock(int ex, int ey){
  // check if the pathing is blocked
  if(0 == group){
    if(y + 2 == ey && (! player->checkNull(x,y+1))){
      return true;
    }
  } else {
    if(y - 2 == ey && (! player->checkNull(x,y-1))){
      return true;
    }
  }
  // check destination
  if(x == ex){
    if(player->checkNull(ex,ey)){
      return false;
    } else {
      return true;
    }
  } else {
    if(player->enPassant(x,y,ex,ey)){
      return true;
    }else if((! player->checkNull(ex,ey)) && group != player->getGroup(ex,ey)) {
      return false;
    } else {
      //cerr << "Ending coordinates is one of your chessman." << endl;
      return true;
    }
  }
}

Pawn::Pawn(int x, int y, char c, Player *player):
  Chessmen(x,y,c,player),lastMoveDistance(0){}

Pawn::~Pawn(){}

void Pawn::makeMove(int ex, int ey){
  lastMoveDistance = ey - y > 0 ? ey - y : y - ey;
//cerr<<"lastMoveDistance is "<<lastMoveDistance<<endl;
//cerr << "pawn"<<group<<" move from (" << x << "," << y << ") to (" << ex << "," << ey << ")" << endl;
  numMove++;
  x = ex;
  y = ey;
  if((0 == group && ey == 8) || (1 == group && ey == 1)){
    player->pawnPromotion(x,y,group,player);
  }
}

char Pawn::getType(){
  return type;
}

int Pawn::getCoords(){
  return x * 10 + y;
}

int Pawn::getGroup(){
  return group;
}

int Pawn::getLastMoveDistance(){
  return lastMoveDistance;
}

string Pawn::possibleMove(){
  ostringstream oss;
  if(0 == group){
    if(y+1 <= 8){
      oss<<x<<y+1;
      if(x+1 <= 8){
        oss<<x+1<<y+1;
      }
      if(1 <= x-1){
        oss<<x-1<<y+1;
      }
    }
    if(y+2 <= 8){
      oss<<x<<y+2;
    }
  }else{
    if(y-1 >= 1){
      oss<<x<<y-1;
      if(x+1 <= 8){
        oss<<x+1<<y-1;
      }
      if(1 <= x-1){
        oss<<x-1<<y-1;
      }
    }
    if(1 <= y-2){
      oss<<x<<y-2;
    }
  }
  return oss.str();
}


void Pawn::resetLastMoveDistance(int d){
  lastMoveDistance = d;
}
