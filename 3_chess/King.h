#ifndef King_H
#define King_H
#include"ChessPiece.h"
using namespace std;

class King : public ChessPiece{
  private:
		bool validMove(const string begMove, const string endMove);
	public:
		King(const string input_color);
		virtual ~King(){};
};

#endif
