#include"ChessPiece.h"
bool ChessPiece :: check_validMove(const string begMove, const string endMove){
  if(validMove(begMove,endMove)){
    return true;
  }
  return false;
}
string ChessPiece :: get_piece(){
  return piece;
}
string ChessPiece :: get_color(){
  return color;
}

void ChessPiece :: makeMove(){
  madeFirstMove=true;
}
