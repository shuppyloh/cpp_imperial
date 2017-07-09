#ifndef KNIGHT_H
#define KNIGHT_H
#include"ChessPiece.h"
using namespace std;

class Knight: public ChessPiece{
  private:
		bool validMove(const string begMove, const string endMove);
	public:
		Knight(const string input_color);
		virtual ~Knight(){};
};

#endif
