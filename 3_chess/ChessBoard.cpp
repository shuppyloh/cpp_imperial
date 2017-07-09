#include "ChessBoard.h"

ChessBoard :: ChessBoard (){
  setupBoard();
}

void ChessBoard :: setupBoard (){
  cout<<"A new chess game is started!"<<endl;
  turnCounter=0;
  turnColor="White";
  turnKingPos="E1";
  string square="FR";
  string w="White";
  string b="Black";
  //make empty spaces
  for(char file='A';file<='H';file++){
    square[0]=file;
    for(char rank='3';rank<='6';rank++){
      square[1]=rank;
      board[square]=NULL;
    }
  }
  //make pawns
  for(char file='A';file<='H';file++){
    square[0]=file;
    square[1]='2';
    board[square]=new Pawn(w);
    square[1]='7';
    board[square]=new Pawn(b);
  }
  //make other pieces
  board["A1"]=new Rook(w);board["H1"]=new Rook(w);
  board["A8"]=new Rook(b);board["H8"]=new Rook(b);
  board["B1"]=new Knight(w);board["G1"]=new Knight(w);
  board["B8"]=new Knight(b);board["G8"]=new Knight(b);
  board["C1"]=new Bishop(w);board["F1"]=new Bishop(w);
  board["C8"]=new Bishop(b);board["F8"]=new Bishop(b);
  board["D1"]=new Queen(w);board["E1"]=new King(w);
  board["D8"]=new Queen(b);board["E8"]=new King(b);
}

void ChessBoard :: submitMove(const string& begMove, const string& endMove){
  //check if input is valid, then in nested check_Move, check if move valid
  if(check_inputAndMove(begMove, endMove)==true){
    cout<<turnColor<<"'s "<<board[begMove]->get_piece()<<" moves from ";
    cout<<begMove<<" to "<<endMove;
    //if there is an opponent piece at ending square, output capture msg
    if(check_pieceExists(endMove)){
      string endColor=board[endMove]->get_color();
      string endPiece=board[endMove]->get_piece();
      cout<<" taking "<<endColor<<"'s "<<endPiece;
    }
    cout<<endl;
    //manipulate the board by calling execute function
    execute_move(begMove, endMove);

    //switch to next turn
    nextTurn();

    //check for incheck or checkmate and output message
    if(check_ifCheck(endMove) && check_forPossibleMoves()==true){
      cout<<turnColor<<" is in check"<<endl;
    }
    if(check_ifCheck(endMove) && check_forPossibleMoves()==false){
      cout<<turnColor<<" is in checkmate"<<endl;
    }
    if(check_ifCheck(endMove)==false && check_forPossibleMoves()==false){
      cout<<turnColor<<" has no legal moves left to make. Stalemate!"<<endl;
    }
  }
}

void ChessBoard :: resetBoard(){
  deleteBoard();
  setupBoard();
}

string ChessBoard:: find_king(){
  string square="FR";
  for(char file='A';file<='H';file++){
    square[0]=file;
    for(char rank='1';rank<='8';rank++){
      square[1]=rank;
      if (board[square]!=NULL &&
          board[square]->get_piece()=="King" &&
          board[square]->get_color()==turnColor){
        return square;
      }
    }
  }
  return 0;
}

bool ChessBoard:: check_turn(const string& begMove){
  string begColor=board[begMove]->get_color();
  if(begColor==turnColor){
    return true;
  }
  return false;
}

bool ChessBoard:: check_withinMap(const string& move){
  if(move.length()>2){
    return false;
  }
  if(move[0]>'H'||move[0]<'A'||move[1]>'8'|| move[1]<'1'){
    return false;
  }
  return true;
}

bool ChessBoard:: check_pieceExists(const string& move){
  if(board[move]==NULL){
    return false;
  }
  return true;
}

bool ChessBoard:: check_inputAndMove(const string& begMove,
    const string& endMove){
  //make sure input is valid
  if (check_withinMap(begMove)==false ||
      check_withinMap(endMove)==false){
    cout<<"Invalid move (not within chessboard coordinates)!"<<endl;
    return false;
  }
  //make sure piece exists
  if (check_pieceExists(begMove)==false){ 
    cout<<"There is no piece at position "<<begMove<<"!"<<endl;
    return false;
  }
  string begColor=board[begMove]->get_color();
  string begPiece=board[begMove]->get_piece();
  if (check_turn(begMove)==false){
    cout<<"It is not "<<begColor<<"'s turn to move!"<<endl;
    return false;
  }
  //if input is valid call move rules checker
  if(check_move(begMove,endMove)==false){
    cout<<begColor<<"'s "<<begPiece;
    cout<<" cannot move to "<<endMove<<"!"<<endl;
    return false;
  }
  //if we reach here, we try move and see if the move result in a check
  if(check_ifCheck(begMove,endMove)==true){
    cout<<begColor<<"'s "<<begPiece;
    cout<<" cannot move to "<<endMove<<"!"<<endl;
    return false;
  }
  return true;
}

bool ChessBoard:: check_move(const string& begMove, const string& endMove){
  string begPiece=board[begMove]->get_piece();
  string begColor=board[begMove]->get_color();
  string endColor;
  //you cannot move to a same-space
  if(begMove==endMove){
    return false;
  }
  //talk to chesspiece object and check if it is able to move to its rules 
  if(board[begMove]->check_validMove(begMove, endMove)==false){
    return false;
  }
  //you cannot capture a friendly piece
  if(check_pieceExists(endMove)){
    endColor=board[endMove]->get_color();
    if(endColor==begColor){
      return false;
    }
  }
  //check if move path is blocked
  if(begPiece!="Knight" && check_ifBlock(begMove,endMove)==true){
    return false;
  }
  //special checks if it is a Pawn
  if(begPiece=="Pawn"){
    if(endMove[0]!=begMove[0] && board[endMove]==NULL){
      return false; //return false if move diag to empty square;
    }
    if(endMove[1]!=begMove[1] && endMove[0]==begMove[0] && 
        board[endMove]!=NULL){
      return false; //return false if move vert to non-empty square;
    }
  }
  return true;
}

//this checks if a player in turn causes check on himself 
bool ChessBoard::check_ifCheck(const string& begMove, const string& endMove){ 
  //temp pointer to keep endMove object
  ChessPiece* tempPiecePtr=NULL;
  tempPiecePtr=board[endMove];
  //execute move without deleting endMove pobject
  board[endMove]=board[begMove];
  board[begMove]=NULL;
  //we create a separate king position as we might have moved the king
  string tempKingPos=find_king();
  //for every enemy piece out there check if it can move to the king's position
  for(char file='A';file<='H';file++){
    string square="FR";
    square[0]=file;
    for(char rank='1';rank<='8';rank++){
      square[1]=rank;
      if (check_pieceExists(square) && board[square]->get_color()!=turnColor){
        if(check_move(square,tempKingPos)==true){
          //revert the hypothetical move on the board as we quit the function
          board[begMove]=board[endMove];
          board[endMove]=tempPiecePtr;
          return true;
        }
      }
    }
  }
  //revert the hypothetical move on the board as we quit the function
  board[begMove]=board[endMove];
  board[endMove]=tempPiecePtr;
  return false;
}

//polymorphism: if function takes one move input, the move has already been
//validated and we check if it causes a check on the opponent player
bool ChessBoard::check_ifCheck(const string& endMove){
  if(check_move(endMove, turnKingPos)){
    return true;
  }
  return false;
}

//for every allied piece on the board, check if it can make any possible move
//allied piece position is "square", potential move it can make is "square2"
bool ChessBoard:: check_forPossibleMoves(){
  for(char file='A';file<='H';file++){
    string square="FR";
    square[0]=file;
    for(char rank='1';rank<='8';rank++){
      square[1]=rank;
      if (board[square]!=NULL && board[square]->get_color()==turnColor){
        //another loop for the endmove square2
        for(char file='A';file<='H';file++){
          string square2="FR";
          square2[0]=file;
          for(char rank='1';rank<='8';rank++){
            square2[1]=rank;
            if(check_move(square,square2) &&
                check_ifCheck(square,square2)==false){
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

//block checker
bool ChessBoard:: check_ifBlock(const string& begMove,	const string& endMove){
  char begFile=begMove[0];
  char begRank=begMove[1];
  char endFile=endMove[0];
  char endRank=endMove[1];
  int file_spaces=(endFile-begFile);
  int rank_spaces=(endRank-begRank);
  //if pieces moves horizontally(Pawn(2 Steps), Rook, Queen)
  //if move horizontally right
  if(file_spaces>1 && rank_spaces==0){
    for (int i=file_spaces-1;i>0;i--){
      string square="FR";
      square[0]=begFile+i;
      square[1]=begRank;
      if (board[square]!=NULL){
        return true;
      }
    }
  }
  //if move horizontally left 
  if(file_spaces<(-1) && rank_spaces==0){
    for (int i=file_spaces+1;i<0;i++){
      string square="FR";
      square[0]=begFile+i;
      square[1]=begRank;
      if (board[square]!=NULL){
        return true;
      }
    }
  }

  //if pieces moves vertically(Pawn(2 Steps), Rook, Queen)
  //if move vertically up
  if(file_spaces==0 && rank_spaces>1){
    for (int i=rank_spaces-1;i>0;i--){
      string square="FR";
      square[0]=begFile;
      square[1]=begRank+i;
      if (board[square]!=NULL){
        return true;
      }
    }
  }
  //if move vertically down
  if(file_spaces==0 && rank_spaces<-1){
    for (int i=rank_spaces+1;i<0;i++){
      string square="FR";
      square[0]=begFile;
      square[1]=begRank+i;
      if (board[square]!=NULL){
        return true;
      }
    }
  }
  //if pieces move diagonally(Bishop, Queen)
  //moving right-top
  if(file_spaces>1 && rank_spaces>1){
    for (int i=file_spaces-1;i>0;i--){
      string square="FR";
      square[0]=begFile+i;
      square[1]=begRank+i;
      if (board[square]!=NULL){
        return true;
      }
    }
  }
  //moving right-bottom
  if(file_spaces>1 && rank_spaces<-1){
    for (int i=file_spaces-1;i>0;i--){
      string square="FR";
      square[0]=begFile+i;
      square[1]=begRank-i;
      if (board[square]!=NULL){
        return true;
      }
    }
  }
  //moving left-top
  if(file_spaces<-1 && rank_spaces>1){
    for (int i=file_spaces+1;i<0;i++){
      string square="FR";
      square[0]=begFile+i;
      square[1]=begRank-i;
      if (board[square]!=NULL){
        return true;
      }
    }
  }
  //moving left-bottom
  if(file_spaces<-1 && rank_spaces<-1){
    for (int i=rank_spaces+1;i<0;i++){
      string square="FR";
      square[0]=begFile+i;
      square[1]=begRank+i;
      if (board[square]!=NULL){
        return true;
      }
    }
  }
  return false;//no blocks by default
}

//
void ChessBoard :: execute_move(const string& begMove, const string& endMove){
  board[begMove]->makeMove();//to change objects' first move counter
  delete board[endMove];
  board[endMove]=board[begMove];
  board[begMove]=NULL;
}

void ChessBoard:: nextTurn(){
  turnCounter=(turnCounter+1)%2; //changes bool counter
  //update color string
  if (turnCounter==0){
    turnColor.clear();
    turnColor="White"; 
  }
  if (turnCounter==1){
    turnColor.clear();
    turnColor="Black";
  }
  //update current king's position 
  turnKingPos.clear();
  turnKingPos=find_king();
}

void ChessBoard :: deleteBoard(){
  //delete all chesspieces on the board to free up memory
  for(char file='A';file<='H';file++){
    string square="FR";
    square[0]=file;
    for(char rank='1';rank<='8';rank++){
      square[1]=rank;
      delete board[square];
    }
  }
}
