#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include<string>
#include<iostream>
using namespace std;

class ChessPiece{
  friend class ChessBoard;
  protected:
  //constructor is protected (excxlusive to friend class ChessBoard)
  //if ChessPiece derived object is created not from ChessBoard class,
  //compiler will complain
    ChessPiece (): madeFirstMove(false),color(""),piece(""){};
    ChessPiece (ChessPiece &obj){};
    bool madeFirstMove; //counter
    void makeMove(); //increase counter 
    string color;
    string piece;
    string get_piece();
    string get_color();
    //checks if object move is valid, check calls a pure virtual function
    bool check_validMove(const string begMove, const string endMove);
    virtual bool validMove(const string begMove, const string endMove)=0;
  public:
    virtual ~ChessPiece(){};
};
#endif
