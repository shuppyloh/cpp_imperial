#ifndef PAWN_H
#define PAWN_H
#include"ChessPiece.h"
using namespace std;

class Pawn : public ChessPiece{
  private:
    bool validMove(const string begMove, const string endMove);
  public:
    Pawn(const string input_color);
    ~Pawn(){};
};

#endif
