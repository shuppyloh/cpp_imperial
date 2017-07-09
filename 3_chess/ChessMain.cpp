#include <iostream>

using namespace std;

#include "ChessBoard.h"

int main() {
  ChessBoard cb; 
  cout<<"CHECKING PAWN"<<endl<<endl;
  cout<<"moves should be allowed"<<endl<<endl;

  cb.submitMove("D2", "D4");
  cb.submitMove("D7", "D5");
  cout<<endl;

  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E5");
  cout<<endl;

  cb.submitMove("F2", "F3");
  cb.submitMove("F7", "F6");
  cout<<endl;

  cb.submitMove("H2", "H4");
  cb.submitMove("A7", "A5");
  cout<<endl;

  cb.submitMove("C1", "H6");
  cb.submitMove("F8", "A3");
  cout<<endl;

  cout<<"moves shouldn't be allowed:"<<endl<<endl;
  cb.submitMove("D4", "D5");
  cb.submitMove("D4", "C5");
  cb.submitMove("D4", "E6");
  cb.submitMove("d4", "E5");
  cb.submitMove("84", "E5");
  cb.submitMove("D4", "C4");
  cb.submitMove("D4", "D3");
  cb.submitMove("D4", "D2");
  cb.submitMove("D4", "I4");
  cb.submitMove("A2", "A4");
  cb.submitMove("A2", "A3");
  cb.submitMove("F3", "E4");
  cb.submitMove("H7", "H5");
  cout<<endl;

  cout<<"moves should be allowed, taking pieces:"<<endl<<endl;

  cb.submitMove("D4", "E5");
  cb.submitMove("F6", "E5");
  cout<<endl;

  cb.resetBoard();

  cout<<"CHECKING ROOK"<<endl<<endl;

  cout<<"moves should be allowed"<<endl<<endl;

  cb.submitMove("A2", "A4");
  cb.submitMove("H7", "H5");
  cout<<endl;

  cb.submitMove("A1", "A3");
  cb.submitMove("H8", "H6");
  cout<<endl;

  cb.submitMove("A3", "D3");
  cb.submitMove("H6", "F6");
  cout<<endl;

  cout<<"moves shouldn't be allowed:"<<endl<<endl;
  cb.submitMove("D3", "I3");
  cb.submitMove("D3", "E4");
  cb.submitMove("D3", "C5");
  cb.submitMove("d3", "d4");
  cb.submitMove("80", "D4");
  cb.submitMove("D3", "D2");
  cb.submitMove("D3", "D8");
  cb.submitMove("D3", "D9");
  cb.submitMove("F6", "F4");
  cout<<endl;

  cout<<"moves should be allowed, taking pieces:"<<endl<<endl;

  cb.submitMove("D3", "D7");
  cb.submitMove("F6", "F2");
  cout<<endl;

  cout<<"black should be placed in check:"<<endl<<endl;
  cb.submitMove("D7", "D8");
  cout<<endl;

  cout<<"illegal move because in check:"<<endl<<endl;
  cb.submitMove("F2", "F3");
  cout<<endl;

  cout<<"only legal move for black:"<<endl<<endl;
  cb.submitMove("E8", "D8");
  cout<<endl;

  cb.resetBoard();

  cout<<"CHECKING KNIGHT"<<endl<<endl;
  cout<<"moves should be allowed"<<endl<<endl;

  cb.submitMove("B1", "C3");
  cb.submitMove("B8", "C6");
  cout<<endl;

  cb.submitMove("G1", "F3");
  cb.submitMove("G8", "F6");
  cout<<endl;

  cb.submitMove("F3", "D4");
  cb.submitMove("F6", "H5");
  cout<<endl;

  cb.submitMove("D4", "F5");
  cb.submitMove("H5", "G3");
  cout<<endl;

  cout<<"moves shouldn't be allowed:"<<endl<<endl;
  cb.submitMove("C3", "D1");
  cb.submitMove("C3", "D4");
  cb.submitMove("C3", "C5");
  cb.submitMove("C3", "C2");
  cb.submitMove("C3", "d5");
  cb.submitMove("80", "D5");
  cb.submitMove("C3", "F6");
  cb.submitMove("C3", "B6");
  cb.submitMove("C6", "D4");
  cout<<endl;

  cout<<"black should be placed in check:"<<endl<<endl;
  cb.submitMove("F5", "D6");
  cout<<endl;

  cout<<"illegal moves because in check:"<<endl<<endl;
  cb.submitMove("G3", "H1");
  cb.submitMove("G3", "G2");
  cb.submitMove("G3", "I4");
  cout<<endl;

  cout<<"legal move for black:"<<endl<<endl;
  cb.submitMove("C7", "D6");
  cout<<endl;

  cb.resetBoard();
  cout<<"CHECKING BISHOP"<<endl<<endl;

  cout<<"moves should be allowed"<<endl<<endl;

  cb.submitMove("D2", "D4");
  cb.submitMove("D7", "D5");
  cout<<endl;

  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E5");
  cout<<endl;

  cb.submitMove("C1", "D2");
  cb.submitMove("F8", "B4");
  cout<<endl;

  cb.submitMove("F1", "C4");
  cb.submitMove("C8", "G4");
  cout<<endl;

  cout<<"moves shouldn't be allowed:"<<endl<<endl;
  cb.submitMove("C4", "B4");
  cb.submitMove("C4", "A2");
  cb.submitMove("C4", "A7");
  cb.submitMove("C4", "H9");
  cb.submitMove("C4", "G8");
  cb.submitMove("c4", "d3");
  cb.submitMove("D2", "E3");
  cb.submitMove("C4", "F7");
  cb.submitMove("D2", "D3");
  cout<<endl;

  cout<<"moves should be allowed, taking pieces:"<<endl<<endl;

  cb.submitMove("C4", "D5");
  cb.submitMove("G4", "D1");
  cout<<endl;

  cout<<"black should be placed in check:"<<endl<<endl;
  cb.submitMove("D5", "F7");
  cout<<endl;

  cout<<"illegal move because in check:"<<endl<<endl;
  cb.submitMove("D1", "F3");
  cout<<endl;

  cout<<"only legal move for black:"<<endl<<endl;
  cb.submitMove("E8", "F7");
  cout<<endl;
  cb.resetBoard();

  cout<<"CHECKING KING"<<endl<<endl;

  cout<<"moves should be allowed"<<endl<<endl;

  cb.submitMove("D2", "D4");
  cb.submitMove("D7", "D5");
  cout<<endl;

  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E5");
  cout<<endl;

  cb.submitMove("F1", "A6");
  cb.submitMove("C8", "H3");
  cout<<endl;

  cb.submitMove("D1", "H5");
  cb.submitMove("F8", "A3");
  cout<<endl;

  cb.submitMove("H5", "H3");
  cb.submitMove("E5", "D4");
  cout<<endl;

  cb.submitMove("C1", "H6");
  cb.submitMove("D8", "H4");
  cout<<endl;

  cb.submitMove("E4", "D5");
  cb.submitMove("H4", "H6");
  cout<<endl;

  cb.submitMove("H3", "A3");
  cb.submitMove("H6", "A6");
  cout<<endl;

  cb.submitMove("A3", "A6");
  cb.submitMove("B7", "A6");
  cout<<endl;

  cb.submitMove("E1", "E2");
  cb.submitMove("E8", "E7");
  cout<<endl;

  cb.submitMove("E2", "F3");
  cb.submitMove("E7", "F6");
  cout<<endl;

  cb.submitMove("F3", "F4");
  cb.submitMove("F6", "G6");
  cout<<endl;

  cout<<"moves shouldn't be allowed:"<<endl<<endl;
  cb.submitMove("F4", "F6");
  cb.submitMove("F4", "H2");
  cb.submitMove("F4", "G5");
  cb.submitMove("F4", "E3");
  cb.submitMove("80", "E4");
  cb.submitMove("F4", "d2");
  cb.submitMove("F4", "F7");
  cb.submitMove("F4", "I4");
  cb.submitMove("F4", "D4");
  cout<<endl;

  cb.resetBoard();
  cout<<"CHECKING QUEEN"<<endl<<endl;
  cout<<"moves should be allowed"<<endl<<endl;

  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E5");
  cout<<endl;

  cb.submitMove("D1", "F3");
  cb.submitMove("D8", "F6");
  cout<<endl;

  cb.submitMove("F3", "D3");
  cb.submitMove("F6", "H6");
  cout<<endl;

  cout<<"moves shouldn't be allowed:"<<endl<<endl;
  cb.submitMove("D3", "I3");
  cb.submitMove("D3", "E5");
  cb.submitMove("D3", "E4");
  cb.submitMove("d3", "C4");
  cb.submitMove("80", "D4");
  cb.submitMove("D3", "F5");
  cb.submitMove("D3", "D2");
  cb.submitMove("D3", "D9");
  cb.submitMove("D3", "D8");
  cb.submitMove("H6", "H4");
  cout<<endl;

  cout<<"Moves should be allowed:"<<endl<<endl;
  cb.submitMove("D3", "D6");
  cb.submitMove("H6", "H3");
  cout<<endl;

  cout<<"black should be placed in check:"<<endl<<endl;
  cb.submitMove("D6", "D7");
  cout<<endl;

  cout<<"illegal moves because in check:"<<endl<<endl;
  cb.submitMove("H3", "H2");
  cb.submitMove("H3", "D3");
  cout<<endl;
  cout<<"Black can take white queen:"<<endl<<endl;
  cb.submitMove("H3", "D7");

  cb.resetBoard();
  cout<<"CHECKING STALEMATE"<<endl<<endl;
  cb.submitMove("C2", "C4");
  cb.submitMove("H7", "H5");
  cout<<endl;

  cb.submitMove("H2", "H4");
  cb.submitMove("A7", "A5");
  cout<<endl;

  cb.submitMove("D1", "A4");
  cb.submitMove("A8", "A6");
  cout<<endl;

  cb.submitMove("A4", "A5");
  cb.submitMove("A6", "H6");
  cout<<endl;

  cb.submitMove("A5", "C7");
  cb.submitMove("F7", "F6");
  cout<<endl;

  cb.submitMove("C7", "D7");
  cb.submitMove("E8", "F7");
  cout<<endl;

  cb.submitMove("D7", "B7");
  cb.submitMove("D8", "D3");
  cout<<endl;

  cb.submitMove("B7", "B8");
  cb.submitMove("D3", "H7");
  cout<<endl;

  cb.submitMove("B8", "C8");
  cb.submitMove("F7", "G6");
  cout<<endl;

  cout<<"Black should be placed in stalemate:"<<endl;

  cb.submitMove("C8", "E6");

  return 0;
}
