#include "human.h"
#define TEST false

using namespace std;

Human::Human(int **board, int group):
  Player(board, group){}

Human::~Human(){}

void Human::makeMove(){
//cerr<<"start making move"<<endl;
  board[0][0] = '0';
  board[0][1] = '0';
//cerr<<"group "<<group<<" activated from "<<activated;
  activated = true;
//cerr<<" to "<<activated<<endl;
  bool reMakeMove;
  while(true){
    reMakeMove = false;
    int sx,sy,ex,ey;
    char c1,c2,c3,c4;
    cin >> c1;
    sx = c1 - 96;
    cin >> c2;
    sy = c2 - 48;
    cin >> c3;
    ex = c3 - 96;
    cin >> c4;
    ey = c4 - 48;
    // check valid input
    if(sx < 1  || sx > 8 || sy < 1 || sy > 8){
      cerr << "\"" << c1 << c2 << "\"";
      cerr << " is not valid starting coordinates." << endl;
      cerr << "Please re-enter starting and ending coordinates." << endl;
      reMakeMove = true;
    }else if(ex < 1  || ex > 8 || ey < 1 || ey > 8){
      cerr << "\"" << c3 << c4 << "\"";
      cerr << " is not valid ending coordinates." << endl;
      cerr << "Please re-enter starting and ending coordinates." << endl;
      reMakeMove = true;
    }else{
      if(sx == ex && sy == ey){
        cerr << "You cannot move a chassman to it current location." << endl;
        cerr << "Please re-enter starting and ending coordinates." << endl;
        reMakeMove = true;
      } else if(checkNull(sx,sy)){
        cerr << "There is no chessman on coordinates ";
        cerr << "\"" << c1 << c2 << "\"." << endl;
        cerr << "Please re-enter starting and ending coordinates." << endl;
        reMakeMove = true;
      }else if(group != getGroup(sx,sy)){
        cerr << "You cannot move opponent's chessmen" << endl;
        cerr << "Please re-enter starting and ending coordinates." << endl;
        reMakeMove = true;
      }else{
        for(int i = 0; i < 16; i++){
          if(NULL != chessmen[i]){
            int sxy = sx * 10 + sy;
            if(sxy == chessmen[i]->getCoords()){
//cerr << true << endl;
//cerr << "checkMove = " << chessmen[i]->checkMove(ex,ey) << endl;
//cerr << "checkBlock= " << (! chessmen[i]->checkBlock(ex,ey)) << endl;
              if(chessmen[i]->checkMove(ex,ey) &&
                 (! chessmen[i]->checkBlock(ex,ey)) &&
                 (! checkCaptured(sx,sy,ex,ey))){
                if((! isCastling) && (! isEnPassant)){
                  isCheck = false;
                  doublecheck = false;
                  board[ex][ey] = board[sx][sy];
                  if(TEST){
                    board[sx][sy] = '_';
                  }else{
                    board[sx][sy] = '0';
                  }
                  board[0][0] = '1';
                  board[1][0] = sx + 48;
                  board[2][0] = sy + 48;
                  board[3][0] = ex + 48;
                  board[4][0] = ey + 48;
                  board[5][0] = chessmen[i]->getType();
                  opponentPlayer->delinkChessmen(ex,ey);
                  chessmen[i]->makeMove(ex,ey);
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
//cerr<<"group "<<group<<" activated from "<<activated;
                  activated = false;
//cerr<<" to "<<activated<<endl;
                  break;
                }
              }else{
                if(true != isCastling && true != isEnPassant){
                  cerr << "Moving chessman from ";
                  cerr << "\"" << c1 << c2 << "\"";
                  cerr << " to ";
                  cerr << "\"" << c3 << c4 << "\"";
                  cerr << " is invalid." << endl;
                  cerr << "Please re-enter starting and ending coordinates." << endl;
                  reMakeMove = true;
                }else{
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
                    if(TEST){
                      if(0 == group){
                        cerr << "Black is in check" << endl;
                      }else{
                        cerr << "White is in check" << endl;
                      }
                    }
                    opponentPlayer->checkNotify(oss.str());
                  }
                  isCastling = false;
                  isEnPassant = false;
                }
              }
              //isCastling = false;
              //isEnPassant = false;
            }
          }
        }
      }
    }
//cerr<<"group "<<group<<" activated from "<<activated;
    activated = false;
//cerr<<" to "<<activated<<endl;
    if(reMakeMove){
      continue;
    }else{
      opponentPlayer->checkDraw(size);
      break;
    }
  }
}

void Human::setLevel(int x){}
