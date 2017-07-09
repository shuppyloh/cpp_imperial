#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<iostream>
#include<map>
#include<string>
#include"ChessPiece.h"
#include"Pawn.h"
#include"Rook.h"
#include"Knight.h"
#include"Bishop.h"
#include"Queen.h"
#include"King.h"
using namespace std;
class ChessBoard{
  private:
    map<string,ChessPiece*>board; //<position("A1"), pointer to ChessPiece>
    void setupBoard(); //populates Board
    void deleteBoard(); //deletes all chesspiece objects on board
    bool turnCounter; //bool tracker on whose turn to play
    string turnColor; //color of the current turn, derived from turnCounter
    string turnKingPos; //board King position of current player
    string find_king(); //function to find King position
    bool check_turn(const string& begMove); //right turn?
    bool check_withinMap(const string& move); //within board coordinates?
    bool check_pieceExists(const string& move); //piece exists?
    //checker for input parameters, move validation, check validation
    bool check_inputAndMove(const string& begMove, const string& endMove);
    //check for move rules only (nested inside check_inputAndMove)
    bool check_move(const string& begMove, const string& endMove);
    //check if move causes self-check (nested inside check_inputandMove)
    bool check_ifCheck(const string& begMove, const string& endMove);
    //check on opponent?(need endMove only - already checked for move validity)
    bool check_ifCheck(const string& endMove);
    //are there legal moves left to make?
    bool check_forPossibleMoves();
    //if there are pieces blocking the movement path of pieces
    bool check_ifBlock(const string& begMove,	const string& endMove);
    //modifies pieces on the board (delete endMove piece and switch positions)
    void execute_move(const string& begMove, const string& endMove);
    //updates turnCounter, next turn of the game
    void nextTurn();
  public:
    void submitMove(const string& begMove, const string& endMove);
    //calls deleteBoard first then setupBoard for brand new game
    void resetBoard();
    ChessBoard();
};
#endif
