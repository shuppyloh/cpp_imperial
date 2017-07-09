#ifndef ROOK_H
#define ROOK_H 
#include"ChessPiece.h"
using namespace std;

class Rook: public ChessPiece{
  private:
		bool validMove(const string begMove, const string endMove);
	public:
		Rook(const string input_color);
		virtual ~Rook(){};
};

#endif
