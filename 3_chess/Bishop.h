#ifndef BISHOP_H 
#define BISHOP_H 
#include"ChessPiece.h"
using namespace std;

class Bishop: public ChessPiece{
  private:
		bool validMove(const string begMove, const string endMove);
	public:
		Bishop(const string input_color);
		virtual ~Bishop(){};
};

#endif
