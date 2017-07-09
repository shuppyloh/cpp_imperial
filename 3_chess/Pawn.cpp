#include"Pawn.h"


Pawn :: Pawn(const string input_color){
  piece="Pawn";
  color=input_color;
}
bool Pawn :: validMove(const string begMove,const string endMove){
  char begFile=begMove[0];
  char begRank=begMove[1];
  char endFile=endMove[0];
  char endRank=endMove[1];
  if (color=="Black"){
    if(endRank==(begRank-1)){
      if(endFile==(begFile)||endFile==(begFile-1)||endFile==(begFile+1)){
        if(madeFirstMove==false){
        }
        return true;
      }
    }
    if(madeFirstMove==false && (endRank==(begRank-2))){
      return true;
    }
  }
  if (color=="White"){
    if(endRank==(begRank+1)){
      if(endFile==(begFile)||endFile==(begFile-1)||endFile==(begFile+1)){
        return true;
      }
    }
    if(madeFirstMove==false && (endRank==(begRank+2))){
      return true;
    }
  }
  return false;
}

