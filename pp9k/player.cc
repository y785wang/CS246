#include "player.h"
#include <iostream>
#define TEST false

using namespace std;

Player::Player(int **b, int group):
  group(group),size(0),board(b),isCastling(false),isEnPassant(false),isCheck(false),activated(false), doublecheck(false){
  chessmen = new Chessmen*[16];
  for(int i = 0; i < 16; i++){
    chessmen[i] = NULL;
  }
  for(int x = 1; x <= 8; x++){
    for(int y = 1; y <= 8; y++){
      char c = board[x][y];
      if(0 == group && 65 <= c && c <= 90){
        if('R' == c){
          chessmen[size] = new Rook(x,y,c,this);
          size++;
        } else if('N' == c){
          chessmen[size] = new Knight(x,y,c,this);
          size++;
        } else if('B' == c){
          chessmen[size] = new Bishop(x,y,c,this);
          size++;
        } else if('Q' == c){
          chessmen[size] = new Queen(x,y,c,this);
          size++;
        } else if('K' == c){
          chessmen[size] = new King(x,y,c,this);
          size++;
        } else if('P' == c){
          chessmen[size] = new Pawn(x,y,c,this);
          size++;
        }
      }
      if(1 == group && 97 <= c && c <= 122){
        if('r' == c){
          chessmen[size] = new Rook(x,y,c,this);
          size++;
        } else if('n' == c){
          chessmen[size] = new Knight(x,y,c,this);
          size++;
        } else if('b' == c){
          chessmen[size] = new Bishop(x,y,c,this);
          size++;
        } else if('q' == c){
          chessmen[size] = new Queen(x,y,c,this);
          size++;
        } else if('k' == c){
          chessmen[size] = new King(x,y,c,this);
          size++;
        } else if('p' == c){
          chessmen[size] = new Pawn(x,y,c,this);
          size++;
        }
      }
    }
  }
}

Player::~Player(){
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
      delete chessmen[i];
    }
  }
  delete [] chessmen;
}

bool Player::checkNull(int x, int y){
//char c = board[x][y];
//cerr<<x<<" "<<y<<" - "<<c<<endl;
  if((TEST && '_' == board[x][y]) || ((! TEST) && '0' == board[x][y])){
    return true;
  }else{
    return false;
  }
}

void Player::connect(Player *p){
  opponentPlayer = p;
}

int Player::getGroup(int x, int y){ // group for any loction on the board
  int c = board[x][y];
  if(65 <= c && c <= 90){
    return 0;
  }else{
    return 1;
  }
}

bool Player::checkCaptured(int sx, int sy, int ex, int ey){
//cerr<<"checkCaptured-step-1"<<" group "<<group<<endl;
//cerr<<sx<<sy<<ex<<ey<<endl;
  int kxy = getKingCoords();
  int kx = kxy / 10;
  int ky = kxy % 10;
//cerr<<kx<<ky<<endl;
  //the moving chessman is king
  if(kx == sx && ky == sy){
    //assuming king moved
    char a = board[kx][ky];
    char b = board[ex][ey];
    board[ex][ey] = a;
    if(TEST){
      board[kx][ky] = '_';
    }else{
      board[kx][ky] = '0';
    }
    //board[kx][ky] = '_';
    if(opponentPlayer->checkCaptured(ex,ey)){
      board[ex][ey] = b;
      board[kx][ky] = a;
      return true;
    }else{
      board[ex][ey] = b;
      board[kx][ky] = a;
      return false;
    }
  }
  if(kx == sx || ky == sy || kx - sx == ky - sy || kx - sx == sy - ky){
    int exy = ex * 10 + ey;
    if(opponentPlayer->checkCaptured(kx,ky,sx,sy,exy)){
      //cerr << "Moving like that will automatically make your king in check." << endl;
      return true;
    }else{
      return false;
    }
  }
  if(! isCheck){
    return false;
  }else{
    if(opponentPlayer->checkCaptured(kx,ky,sx,sy,ex*10+ey)){
      return true;
    }else{
      return false;
    }
  }
}

bool Player::checkCaptured(int kx, int ky, int sx, int sy, int exy){// moving chessman is not king
//cerr<<"checkCaptured-step-2a group "<<group<<endl;
//cerr<<kx<<ky<<sx<<sy<<exy<<endl;
  bool block = false;
  int ex = exy / 10;
  int ey = exy % 10;
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
      if(chessmen[i]->checkMove(kx,ky)){
        int n;
        int x = chessmen[i]->getCoords() / 10;
        int y = chessmen[i]->getCoords() % 10;
        if(x == ex && y == ey){
          return false;
        }
        if(('p' == chessmen[i]->getType() || 'P' == chessmen[i]->getType()) && (kx == sx)){
          return false;
        }
//cerr<<"possible opponent chessman: "<<x<<y<<endl;
        if(x == kx){
          n = y - ky > 0 ? y - ky : ky - y;
        } else {
          n = x - kx > 0 ? x - kx : kx - x;
        }
//cerr<<"n = "<<n<<endl;
        int deltaX = (x - kx) / n;
        int deltaY = (y - ky) / n;
        n--;
//cerr<<deltaX<<deltaY<<endl;
//cerr<<"sxy = "<<sx<<sy<<endl;
        for(int j = 1; j <= n; j++){
//cerr<<"checking: "<<kx + deltaX * j<<ky + deltaY * j<<endl;
          bool check1;
          if(TEST){
            check1 = ('_' == board[kx + deltaX * j][ky + deltaY * j]);
          }else{
            check1 = ('0' == board[kx + deltaX * j][ky + deltaY * j]);
          }
          bool check2 = (kx + deltaX * j == ex && ky + deltaY * j == ey);
          bool check3 = (kx + deltaX * j == sx && ky + deltaY * j == sy);
//cerr<<check1<<check2<<" "<<(! check1)<<(! check3)<<endl;
          if((check1 && check2) || ((! check1) && (! check3))){
//cerr<<"block = true"<<endl;
            block = true;
            //break;
          }
        }
        if(true == block){
          block = false;
          continue;
        }else{
          return true;
        }
      }
    }
  }
  return false;
}

bool Player::checkCaptured(int ex, int ey){ // moving chessman is king
//cerr<<"checkCaptured-step-2b"<<endl;
//cerr<<"Is "<<ex<<ey<<" safe?"<<endl;
  int exy = ex * 10 + ey;
  for(int j = 0; j < 16; j++){
    if(NULL != chessmen[j]){
//cerr<<"checking: "<<chessmen[j]->getCoords()<<" - ";
//cerr<<(exy != chessmen[j]->getCoords())<<endl;
//cerr<<"hahaha"<<exy<<(exy != chessmen[j]->getCoords())<<(chessmen[j]->checkMove(ex,ey))<<((! chessmen[j]->checkBlock(ex,ey)))<<endl;
      if(exy != chessmen[j]->getCoords() && chessmen[j]->checkMove(ex,ey) && (! chessmen[j]->checkBlock(ex,ey))){
        return true;
      }
    }
  }
  return false;
}

void Player::delinkChessmen(int ex, int ey){
//cerr<<"delinkChessmen"<<endl;
  int exy = ex * 10 + ey;
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
      if(exy == chessmen[i]->getCoords()){
        if(chessmen[i]->getType() == 'k' || chessmen[i]->getType() == 'K'){
          cerr<<"case 1 - trying to delete king, coordinates: "<<chessmen[i]->getCoords()<<endl;
          char c;
          cin >> c;
        }
        delete chessmen[i];
        chessmen[i] = NULL;
        size--;
        break;
      }
    }
  }
}

void Player::castling(int x, int ex, int ey){
//cerr<<"castling"<<endl;
  if(isCheck){
    cerr << "You are currently in check, you cannot execute castling."<<endl;
    return;
  }
  int n;
  int exy = ex * 10 + ey;
  int kx = x;
  int ky = ey;
  if(opponentPlayer->checkCaptured(ex,ey)){
    //cerr<<"Castling like that will automatically make your king in check."<<endl;
    return;
  }
  n = ex - kx > 0 ? ex - kx : kx - ex;
  int deltaX = (ex - kx) / n;
//cerr<<kx<<ky<<ex<<ey<<n<<endl;
  for(int i = 1; i <= n; i++){
//cerr<<"checking "<<kx + deltaX * i<<ey<<endl;
    if(! checkNull(kx + deltaX * i, ey)){
      //cerr << "Castling pathing is blocked." << endl;
      return;
    }
  }
  int rxy = ex > x ? 8*10+ey : 1*10+ey;
  bool rookExist = false;
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
      if(rxy == chessmen[i]->getCoords()){
        if(0 == chessmen[i]->getNumMove()){
          rookExist = true;
        }else{
          //cerr << "Moved rook cannot execute castling." << endl;
          return;
        }
      }
    }
  }
  if(! rookExist){
    //cerr << "No rook exist for executing castling." << endl;
    return;
  }
  if(! activated){
    return;
  }
  isCastling= true;
  char rook = 1 == ey ? 'R' : 'r';
  char king = 1 == ey ? 'K' : 'k';
  board[0][0] = '2';
  board[1][0] = '5';
  board[2][0] = ky + 48;
  board[3][0] = '5' + ex - x;
  board[4][0] = ey + 48;
  board[6][0] = ey + 48;
  board[8][0] = ey + 48;
  if(ex > x){
    if(TEST){
      board[5][ey] = '_';
    }else{
      board[5][ey] = '0';
    }
    //board[5][ey] = '_';
    board[6][ey] = rook;
    board[7][ey] = king;
    if(TEST){
      board[8][ey] = '_';
    }else{
      board[8][ey] = '0';
    }
    //board[8][ey] = '_';
    board[5][0] = '8';
    board[7][0] = '6';
    for(int i = 0; i < 16; i++){
      if(NULL != chessmen[i]){
        if(5*10+ey == chessmen[i]->getCoords()){
          chessmen[i]->makeMove(ex,ey);
        }
        if(8*10+ey == chessmen[i]->getCoords()){
          chessmen[i]->makeMove(ex-1,ey);
        }
      }
    }
  }else{
    if(TEST){
      board[1][ey] = '_';
    }else{
      board[1][ey] = '0';
    }
    //board[1][ey] = '_';
    board[3][ey] = king;
    board[4][ey] = rook;
    if(TEST){
      board[5][ey] = '_';
    }else{
      board[5][ey] = '0';
    }
    //board[5][ey] = '_';
    board[5][0] = '1';
    board[7][0] = '4';
    for(int i = 0; i < 16; i++){
      if(NULL != chessmen[i]){
        if(5*10+ey == chessmen[i]->getCoords()){
          chessmen[i]->makeMove(ex,ey);
        }
        if(1*10+ey == chessmen[i]->getCoords()){
          chessmen[i]->makeMove(ex+1,ey);
        }
      }
    }
  }
  return;
}

bool Player::enPassant(int x, int y, int ex, int ey){
//cerr<<"enPassant1 group "<<group<<endl;
//cerr<<x<<y<<ex<<ey<<endl;
  if('P' == board[ex][y] || 'p' == board[ex][y]){
    int lastMoveDistance = opponentPlayer->enPassant(ex,y);
    if(2 == lastMoveDistance){
      int kxy = getKingCoords();
      int kx = kxy / 10;
      int ky = kxy % 10;
      int xy = x * 10 + y;
      // backup, before enPassant executes
      char a = board[ex][ey];
      char b = board[x][y];
      char c = board[ex][y];
      // assuming enPassant is valid
      board[ex][ey] = board[x][y];
      if(TEST){
        board[x][y] = '_';
        board[ex][y] = '_';
      }else{
        board[x][y] = '0';
        board[ex][y] = '0';
      }
      //board[x][y] = '_';
      //board[ex][y] = '_';
      if(opponentPlayer->checkCaptured(kx,ky)){
        //cerr<<"En passant like that will automatically make your king in check."<<endl;
        // load backup
        board[ex][ey] = a;
        board[x][y] = b;
        board[ex][y] = c;
        return false;
      }
      if(true == activated){
        isEnPassant= true;
        board[0][0] = '3';
        board[1][0] = x + 48;
        board[2][0] = y + 48;
        board[3][0] = ex + 48;
        board[4][0] = ey + 48;
        board[5][0] = ex + 48;
        board[6][0] = y + 48;
        for(int i = 0; i < 16; i++){
          if(NULL != chessmen[i]){
            if(xy == chessmen[i]->getCoords()){
              chessmen[i]->makeMove(ex,ey);
            }
          }
        }
        opponentPlayer->delinkChessmen(ex,y);
        return true;
      }else{
        board[ex][ey] = a;
        board[x][y] = b;
        board[ex][y] = c;
        return true;
      }
    }
  }
  return false;
}

int Player::enPassant(int x, int y){
//cerr<<"enPassant2 group "<<group<<endl;
  int xy = x * 10 + y;
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
      if(xy == chessmen[i]->getCoords()){
        return chessmen[i]->getLastMoveDistance();
      }
    }
  }
}

int Player::getKingCoords(){
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
      if('k' == chessmen[i]->getType() || 'K' == chessmen[i]->getType()){
        return chessmen[i]->getCoords();
      }
    }
  }
}

void Player::checkNotify(string s){
//cerr<<"checkNotify is "<<s<<" group is "<<group<<endl;
  isCheck = true;
  if(4 == s.length()){
    doubleCheck();
  }else{
    istringstream iss(s);
    int cxy,cx,cy;
    iss >> cxy;
    cx = cxy / 10;
    cy = cxy % 10;
    singleCheck(cx, cy);
  }
}

void Player::doubleCheck(){
//cerr<<"enter doubleCheck"<<endl;
  doublecheck = true;
  int kxy = getKingCoords();
  int kx = kxy / 10;
  int ky = kxy % 10;
//cerr<<"group is "<<group<<", king locates "<<kxy<<", opponent chessman is "<<s<<endl;
  int index;
  for(int i = 0; i < 16; i++){
    if(NULL !=chessmen[i]){
      if(kxy == chessmen[i]->getCoords()){
        index = i;
        break;
      }
    }
  }
  bool existSafePlaceToMove = false;
//cerr<<(chessmen[index]->checkMove(kx-1,ky))<<" "<<(! chessmen[index]->checkBlock(kx-1,ky))<<endl;
  for(int i = kx-1; i <= kx+1; i++){
    for(int j = ky-1; j <= ky+1; j++){
      if((i != kx || j != ky) && 1 <= i && i <= 8 && 1 <= j && j <= 8 &&
         chessmen[index]->checkMove(i,j) && (! chessmen[index]->checkBlock(i,j))){
        char a = board[kx][ky];
        char b = board[i][j];
        board[i][j] = 'a';
        if(TEST){
          board[kx][ky] = '_';
        }else{
          board[kx][ky] = '0';
        }
        //board[kx][ky] = '_';
        if(! opponentPlayer->checkCaptured(i,j)){
          existSafePlaceToMove = true;
          board[i][j] = b;
          board[kx][ky] = a;
//cerr<<"moving your to "<<i<<j<<" is safe"<<endl;
          goto next;
        }
        board[i][j] = b;
        board[kx][ky] = a;
      }
    }
  }
  next:
  if(! existSafePlaceToMove){
    board[0][1] = '5';
    ///*yi xia nei rong he bing shi xu shan diao
    if(0 == group){
      cerr<<"Checkmate! Black wins!"<<endl;
    }else{
      cerr<<"Checkmate! White wins!"<<endl;
    }//*/
  }
}

void Player::singleCheck(int cx, int cy){
//cerr<<"~~~~~~~~~~singleCheck step-1~~~~~~~~~~"<<endl;
  char k = 0 == group ? 'K' : 'k';
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i]){
//cerr<<"checking: "<<chessmen[i]->getCoords()<<endl;
//cerr<<(chessmen[i]->checkMove(cx,cy))<<(! chessmen[i]->checkBlock(cx,cy))<<(k != chessmen[i]->getType())<<endl;
      if(k != chessmen[i]->getType() &&
         chessmen[i]->checkMove(cx,cy) && 
         (! chessmen[i]->checkBlock(cx,cy))){
//cerr<<cx<<cy<<" can be captured by "<<chessmen[i]->getCoords()<<endl;
        return;
      }
    }
  }
//cerr<<"~~~~~~~~~~singleCheck step-2~~~~~~~~~~"<<endl;
  int kxy = getKingCoords();
  int kx = kxy / 10;
  int ky = kxy % 10;
  int index;
  for(int i = 0; i < 16; i++){
    if(NULL !=chessmen[i]){
      if(kxy == chessmen[i]->getCoords()){
        index = i;
        break;
      }
    }
  }
  for(int i = kx-1; i <= kx+1; i++){
    for(int j = ky-1; j <= ky+1; j++){
      if((i != kx || i != j) && (1 <= i && i <= 8 && 1 <= j && j <= 8)){
//cerr<<"trying to move to: "<<i<<j<<endl;
//cerr<<"move & block - "<<(chessmen[index]->checkMove(i,j))<<((! chessmen[index]->checkBlock(i,j)))<<endl;
        char a = board[kx][ky];
        char b = board[i][j];
        if(chessmen[index]->checkMove(i,j) && (! chessmen[index]->checkBlock(i,j))){
          board[i][j] = a;
          board[kx][ky] = '_';
          if(! opponentPlayer->checkCaptured(i,j)){
            board[i][j] = b;
            board[kx][ky] = a;
//cerr<<"coordinates "<<i<<j<<" is safe"<<endl;
            return;
          }
          board[i][j] = b;
          board[kx][ky] = a;
        }
      }
    }
  }
//cerr<<"~~~~~~~~~~singleCheck step-3~~~~~~~~~~"<<endl;
  int n;
  if(cx == kx){
    n = cy - ky > 0 ? cy - ky : ky - cy;
  } else {
    n = cx - kx > 0 ? cx - kx : kx - cx;
  }
  int deltaX = (cx - kx) / n;
  int deltaY = (cy - ky) / n;
  n--;
//cerr<<"n = "<<n<<endl;
//cerr<<deltaX<<deltaY<<endl;
//cerr<<cx<<cy<<endl;
  for(int i = 0; i < 16; i++){
    if(NULL != chessmen[i] && kxy != chessmen[i]->getCoords()){
//cerr<<"cherking our chessman "<<chessmen[i]->getCoords()<<endl;
      for(int j = 1; j <= n; j++){
//cerr<<"cherking - "<<kx+deltaX*j<<ky+deltaY*j<<endl;
        if(chessmen[i]->checkMove(kx+deltaX*j,ky+deltaY*j) && (! chessmen[i]->checkBlock(kx+deltaX*j,ky+deltaY*j))){
//cerr<<"moving "<<chessmen[i]->getCoords()<<" to "<<kx+deltaX*j<<ky+deltaY*j<<" can block "<<cx<<cy<<endl;
          return;
        }
      }
    }
  }
//cerr<<"~~~~~~~~~~~~~~~finally~~~~~~~~~~~~~~~~"<<endl;
  board[0][1] = '5';
  if(TEST){
    if(0 == group){
      cerr<<"Checkmate! Black wins!"<<endl;
      char e;
      cin >> e;
    }else{
      cerr<<"Checkmate! White wins!"<<endl;
      char e;
      cin >> e;
    }
  }
}

void Player::checkDraw(int opponentSize){
//cerr<<"checkDraw - start"<<endl;
  bool draw = false;
  if(opponentSize == size && opponentSize == 1){
    draw = true;
  }else if(! isCheck){
    draw = true;
    for(int i = 0; i < 16; i++){
      if(NULL != chessmen[i]){
//cerr<<"chessman "<<chessmen[i]->getCoords()<<" could try to move to ";
//cerr<<chessmen[i]->possibleMove()<<endl;
        istringstream iss(chessmen[i]->possibleMove());
        while(true){
          char pcx,pcy;
          iss>>pcx>>pcy;
          if(iss.eof()){
            break;
          }
          int pix = pcx - '0';
          int piy = pcy - '0';
//cerr<<"~~~~~~~~~~trying to move "<<pix<<piy<<"~~~~~~~~~~"<<endl;
          int sxy = chessmen[i]->getCoords();
          int sx = sxy / 10;
          int sy = sxy % 10;
          if(chessmen[i]->checkMove(pix ,piy) &&
             (! chessmen[i]->checkBlock(pix ,piy)) &&
             (! checkCaptured(sx,sy,pix,piy))){
            draw = false;
//cerr<<"~~~~~~~~moving "<<pix<<piy<<" is possible~~~~~~~~"<<endl;
            goto checkDraw;
          }
//cerr<<"~~~~~~~moving "<<pix<<piy<<" is impossible~~~~~~~"<<endl;
        }
      }      
    }
  }
  checkDraw:
  if(draw){
    board[0][1] = '6';
    if(TEST){
      cerr<<"Draw"<<endl;
      char e;
      cin >> e;
    }
//cerr<<"checkDraw - end with draw"<<endl;
    return;
  }
//cerr<<"checkDraw - end withnot draw"<<endl;
}

void Player::pawnPromotion(int x, int y, int pawnGroup, Player *player){
  if(! activated){
    //cerr<<"pawnPromotion faild because of unactivated"<<endl;
    return;
  }
  int index;
  char c;
  if("" != possibleMove){ // determind if this player is a computer
    /*srand(time(NULL));
    int i = rand() % 1 + 1;
    if(1 == i){
      c = 'n';
    }else{
      c = 'q';
    }*/
    c = 'q';
    goto next;
  }
  cout << "Pawn promotion, please enter promotion type." << endl;
  cout << "Valid promotion type is one character from following:" << endl;
  cout << "r: rook, n: knight, b: bishop or q: queen." << endl;
  while(cin >> c){
    if(c != 'r' && c != 'n' && c != 'b' && c != 'q'){
      cerr << c << " is invalid promotion type, please re-enter."<<endl;
      cerr << "Valid promotion type is one character from following:" << endl;
      cerr << "r: rook, n: knight, b: bishop or q: queen." << endl;
      continue;
    }else{
      next:
//cerr<<"pawnPromotion: "<<c<<" "<<x<<y<<pawnGroup<<endl;
      for(int i = 0; i < 16; i++){
        if(NULL != chessmen[i] && x*10+y == chessmen[i]->getCoords()){
          if(chessmen[i]->getType() == 'k' || chessmen[i]->getType() == 'K'){
            cerr<<"case 2 - trying to delete king, coordinates: "<<chessmen[i]->getCoords()<<endl;
            char c;
            cin >> c;
          }
          delete chessmen[i];
          board[0][0] = '7';
          if('r' == c){
            if(0 == pawnGroup){
              c -= 32;
            }
            chessmen[i] = new Rook(x,y,c,player);
            board[x][y] = c;
            board[5][0] = chessmen[i]->getType();
            break;
          }
          if('n' == c){
            if(0 == pawnGroup){
              c -= 32;
            }
            chessmen[i] = new Knight(x,y,c,player);
            board[x][y] = c;
            board[5][0] = chessmen[i]->getType();
            break;
          }
          if('b' == c){
            if(0 == pawnGroup){
              c -= 32;
            }
            chessmen[i] = new Bishop(x,y,c,player);
            board[x][y] = c;
            board[5][0] = chessmen[i]->getType();
            break;
          }
          if('q' == c){
            if(0 == pawnGroup){
              c -= 32;
            }
            chessmen[i] = new Queen(x,y,c,player);
            board[x][y] = c;
            board[5][0] = chessmen[i]->getType();
            break;
          }
        }
      }
      break;
    }
  }
}









