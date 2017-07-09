#ifndef QUEEN_H 
#define QUEEN_H 
#include"ChessPiece.h"
using namespace std;

class Queen: public ChessPiece{
  private:
		bool validMove(const string begMove, const string endMove);
	public:
		Queen(const string input_color);
		virtual ~Queen(){};
};

#endif
