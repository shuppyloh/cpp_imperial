chess: ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Rook.o \
  Knight.o Bishop.o Queen.o King.o
	g++ ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Rook.o\
	  Knight.o Bishop.o Queen.o King.o -Wall -g -o chess
ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ ChessMain.cpp -Wall -g -c
ChessBoard.o: ChessBoard.h ChessBoard.cpp
	g++ ChessBoard.cpp -Wall -g -c
ChessPiece.o: ChessPiece.h ChessPiece.cpp
	g++ ChessPiece.cpp -Wall -g -c
Pawn.o: Pawn.h Pawn.cpp
	g++ Pawn.cpp -Wall -g -c
Rook.o: Rook.h Rook.cpp
	g++ Rook.cpp -Wall -g -c
Knight.o: Knight.h Knight.cpp
	g++ Knight.cpp -Wall -g -c
Bishop.o: Bishop.h Bishop.cpp
	g++ Bishop.cpp -Wall -g -c
Queen.o: Queen.h Queen.cpp
	g++ Queen.cpp -Wall -g -c
King.o: King.h King.cpp
	g++ King.cpp -Wall -g -c
