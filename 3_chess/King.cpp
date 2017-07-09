#include"King.h"

King :: King(const string input_color){
  piece="King";
  color=input_color;
}
bool King :: validMove(const string begMove,const string endMove){
  char begFile=begMove[0];
  char begRank=begMove[1];
  char endFile=endMove[0];
  char endRank=endMove[1];
  int file_spaces=(endFile-begFile);
  int rank_spaces=(endRank-begRank);
  if (file_spaces<0){
    file_spaces=file_spaces*(-1);
  }
  if (rank_spaces<0){
    rank_spaces=rank_spaces*(-1);
  }
  if(file_spaces<=1 && rank_spaces<=1){
    return true;
  }
  return false;
}

