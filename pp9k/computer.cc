#include "computer.h"
#define TEST false

using namespace std;

Computer::Computer(int **board, int group):
  Player(board, group),level(1){}

Computer::~Computer(){}

void Computer::makeMove(){
//cerr<<"computer level is "<<level<<endl;
  //char c; // only used for debuging
  //cin >> c; // only used for debuging
  ostringstream updatedPossibleMove_LV_ONE;
  //ostringstream updatedPossibleMove1; // only used for debugging
  ostringstream updatedPossibleMove_LV_TWO;
  //ostringstream updatedPossibleMove2; // only used for debugging
  string updatedPossibleMove_LV_TWO_temp;
  ostringstream updatedPossibleMove_LV_THREE;
  //ostringstream updatedPossibleMove3; // only used for debugging;
  // generating all possible for computer Lv 1111111111111111111111111111111111
//cerr<<endl<<"generating all possible moves for computer Lv 1"<<endl;
  board[0][0] = '0';
  board[0][1] = '0';
  activated = false;
  int sx, sy, sxy, ex, ey;
  board[0][0] = '0';
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
      istringstream iss(chessmen[i]->possibleMove());
      sxy = chessmen[i]->getCoords();
      sx = sxy / 10;
      sy = sxy % 10;
      int length = iss.str().length() / 2;
//cerr<<"chessmen "<<sxy<<" could try to move to "<<iss.str()<<endl;
      for(int j = 0; j < length; j++){
        char cex, cey;
        iss >> cex >> cey;
        ex = cex - '0';
        ey = cey - '0';
//cerr<<"checking destination: "<<ex<<ey<<" - "<<endl;
//cerr<<(chessmen[i]->checkMove(ex,ey))<<((! chessmen[i]->checkBlock(ex,ey)))<<((! checkCaptured(sx,sy,ex,ey)))<<endl;
//char c;
//cin>>c;
        if(/*(ex * 10 + ey != chessmen[i]->getCoords()) &&*/
           (chessmen[i]->checkMove(ex,ey)) &&
           (! chessmen[i]->checkBlock(ex,ey)) &&
           (! checkCaptured(sx,sy,ex,ey))){
          if((! doublecheck) || (doublecheck && (chessmen[i]->getType() == 'k' || chessmen[i]->getType() == 'K'))){
            if(i < 10){
              updatedPossibleMove_LV_ONE << 0 << i << ex << ey;
              //updatedPossibleMove1 << 0 << i << ex << ey << " "; // only used for debuging
            }else{
              updatedPossibleMove_LV_ONE << i << ex << ey;
              //updatedPossibleMove1<< i << ex << ey << " "; // only used for debuging
            }
          }
        }
      }
//cerr<<"chessmen "<<sxy<<" could actually move to "<<updatedPossibleMove1.str()<<endl; // only used for debuging

//updatedPossibleMove1.str("");
    }
  }
  possibleMove = updatedPossibleMove_LV_ONE.str();
  if(doublecheck){
//cerr<<"doublecheck"<<endl;
    goto RANDOM_PICK;
  }
  if(1 == level){
    goto RANDOM_PICK;
  }

  LEVEL_TWO:
  // update possible move for Lv 22222222222222222222222222222222222222222222222
  // prefer capturing
  //cerr<<endl<<"generating all possible moves for computer Lv 2"<<endl;
  for(int i = 0; i < possibleMove.length() / 4; i++){
    istringstream iss(possibleMove.substr(i * 4, 4));
    char cindex1, cindex2, cex, cey;
    iss >> cindex1 >> cindex2 >> cex >> cey;
    int ex = cex - '0';
    int ey = cey - '0';
    if((! checkNull(ex,ey)) && (group != getGroup(ex,ey))){
      updatedPossibleMove_LV_TWO<<cindex1<<cindex2<<cex<<cey;
      //updatedPossibleMove2<<cindex1<<cindex2<<cex<<cey<<" ";
    }
  }
  updatedPossibleMove_LV_TWO_temp = updatedPossibleMove_LV_TWO.str();
  //cerr<<"prefer capture is "<<updatedPossibleMove2.str()<<endl;

  // prefer check
  updatedPossibleMove_LV_TWO.str("");
  //updatedPossibleMove2.str(""); // only used fo debugging
  for(int i = 0; i < possibleMove.length() / 4; i++){
    istringstream iss(possibleMove.substr(i*4, 4));
    char cindex1, cindex2, cex, cey;
    iss >> cindex1 >> cindex2 >> cex >> cey;
    int index1 = cindex1 - '0';
    int index2 = cindex2 - '0';
    int index = index1 * 10 + index2;
    ex = cex - '0';
    ey = cey - '0';
    int bx = chessmen[index]->getCoords() / 10;
    int by = chessmen[index]->getCoords() % 10;
    int okxy = opponentPlayer->getKingCoords();
    int okx = okxy / 10;
    int oky = okxy % 10;
    // bcakup
    char a = board[bx][by];
    char b = board[ex][ey];
    // assuming it moves
    if(TEST){
      board[bx][by] = '_';
    }else{
      board[bx][by] = '0';
    }
    //board[bx][by] = '_';
    board[ex][ey] = a;
    chessmen[index]->makeMove(ex,ey);
    int distance;
    if('p' == chessmen[index]->getType() || 'P' == chessmen[index]->getType()){
      distance = chessmen[index]->getLastMoveDistance();
    }
    if(chessmen[index]->checkMove(okx,oky) && (! chessmen[index]->checkBlock(okx,oky))){
      updatedPossibleMove_LV_TWO << index1 << index2 << ex << ey;
      //updatedPossibleMove2<<index1<<index2<<ex<<ey<<" "; // only used for debugging
    }
    // load backup
    board[bx][by] = a;
    board[ex][ey] = b;
    chessmen[index]->makeMove(bx,by);
    chessmen[index]->reduceNumMoveByTwo();
    chessmen[index]->resetLastMoveDistance(distance);
  }
//cerr<<"prefer check is "<<updatedPossibleMove2.str()<<endl;
  if("" != updatedPossibleMove_LV_TWO_temp){
    possibleMove = updatedPossibleMove_LV_TWO_temp;
  }
  if("" != updatedPossibleMove_LV_TWO.str()){
    srand(time(NULL));
    int r = rand() % 5;
    if(1 != r){
      possibleMove = updatedPossibleMove_LV_TWO.str();
    }
  }
  if(2 == level){
    goto RANDOM_PICK;
  }

  LEVEL_THREE:
  // update possible move for Lv 333333333333333333333333333333333333333333
  //cerr<<endl<<"generating all possible moves for computer Lv 3"<<endl;
  //updatedPossibleMove_LV_THREE;
  //updatedPossibleMove3;
  for(int i = 0; i < possibleMove.length() / 4; i++){
    istringstream iss(possibleMove.substr(i*4, 4));
    char cindex1, cindex2, cex, cey;
    iss >> cindex1 >> cindex2 >> cex >> cey;
    int index1 = cindex1 - '0';
    int index2 = cindex2 - '0';
    int index = index1 * 10 + index2;
    ex = cex - '0';
    ey = cey - '0';
    int bx = chessmen[index]->getCoords() / 10;
    int by = chessmen[index]->getCoords() % 10;
    // backup
    //assuming it moved
    char a = board[bx][by];
    char b = board[ex][ey];
    if(TEST){
      board[bx][by] = '_';
    }else{
      board[bx][by] = '0';
    }
    //board[bx][by] = '_';
    board[ex][ey] = a;
    if(! opponentPlayer->checkCaptured(ex,ey)){
      updatedPossibleMove_LV_THREE << index1 << index2 << ex << ey;
      //updatedPossibleMove3<<index1<<index2<<ex<<ey<<" "; // only used for debugging
    }
    // load backup
    board[bx][by] = a;
    board[ex][ey] = b;
  }
  //cerr<<"prefer avoiding is "<<updatedPossibleMove3.str()<<endl;
  if("" != updatedPossibleMove_LV_THREE.str()){
    possibleMove = updatedPossibleMove_LV_THREE.str();
  }
  if(3 == level){
    goto RANDOM_PICK;
  }
  

  RANDOM_PICK:
  // ramdom pick a move from possibleMove
//cerr<<"random pick"<<endl;
  int numPossibleMove = possibleMove.length() / 4;
  srand(time(NULL));
  int randomNum = rand() % numPossibleMove;
  istringstream pickedMove(possibleMove.substr(randomNum * 4, 4));
  char cindex1, cindex2, cex, cey;
  pickedMove >> cindex1 >> cindex2 >> cex >> cey;
//cerr<<"pick "<<cindex1<<cindex2<<cex<<cey<<endl;
  int index1 = cindex1 - '0';
  int index2 = cindex2 - '0';
  int index = index1 * 10 + index2;
  ex = cex - '0';
  ey = cey - '0';
  isEnPassant = false;
  isCastling = false;
  activated = true;
//cerr<<"index is "<<index<<endl;
//cerr<<(chessmen[index]->checkMove(ex,ey))<<(! chessmen[index]->checkBlock(ex,ey))<<endl;
  if((chessmen[index]->checkMove(ex,ey)) &&
     (! chessmen[index]->checkBlock(ex,ey))){
    if((! isCastling) && (! isEnPassant)){
      isCheck = false;
      doublecheck = false;
      int sxy = chessmen[index]->getCoords();
      sx = sxy / 10;
      sy = sxy % 10;
//cerr<<"makeMove "<<sx<<sy<<ex<<ey<<endl;
      board[ex][ey] = board[sx][sy];
      if(TEST){
        board[sx][sy] = '_';
      }else{
        board[sx][sy] = '0';
      }
      //board[sx][sy] = '_';
      board[0][0] = '1';
      board[1][0] = sx + 48;
      board[2][0] = sy + 48;
      board[3][0] = ex + 48;
      board[4][0] = ey + 48;
      board[5][0] = chessmen[index]->getType();
      opponentPlayer->delinkChessmen(ex,ey);
      chessmen[index]->makeMove(ex,ey);
      int okxy = opponentPlayer->getKingCoords();
      int okx = okxy / 10;
      int oky = okxy % 10;
      ostringstream oss;
      for(int j = 0; j < 16; j++){
        if(NULL != chessmen[j]){
          if(chessmen[j]->checkMove(okx,oky) && (! chessmen[j]->checkBlock(okx,oky))){
             int xy = chessmen[j]->getCoords();
             oss << xy;
          }
        }
      }
      if("" != oss.str()){
        //yi xia nei rong he bing shi xu shan diao
        board[0][1] = '4';
        if(0 == group){
          //cerr << "Black is in check" << endl;
        }else{
          //cerr << "White is in check" << endl;
        }
        opponentPlayer->checkNotify(oss.str());
      }
    }
  }else{
    if(true == isCastling || true == isEnPassant){
      // if castling or enpassant will automatically make opponent's king in check
      int okxy = opponentPlayer->getKingCoords();
      int okx = okxy / 10;
      int oky = okxy % 10;
      ostringstream oss;
      for(int j = 0; j < 16; j++){
        if(NULL != chessmen[j]){
          if(chessmen[j]->checkMove(okx,oky) && (! chessmen[j]->checkBlock(okx,oky))){
            int xy = chessmen[j]->getCoords();
            oss << xy;
          }
        }
      }
      if("" != oss.str()){
        //yi xia nei rong he bing shi xu shan diao
        board[0][1] = '4';
        if(0 == group){
          //cerr << "Black is in check" << endl;
        }else{
          //cerr << "White is in check" << endl;
        }
        opponentPlayer->checkNotify(oss.str());
      }
      isCastling = false;
      isEnPassant = false;
    }
  }
  opponentPlayer->checkDraw(size);
  activated = false;
}

void Computer::setLevel(int l){
  level = l;
}

