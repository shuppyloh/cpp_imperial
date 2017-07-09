#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"


/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

    std::cout << "Loading Sudoku board from file '" << filename << "'... ";

    std::ifstream in(filename);
    if (in){
        char buffer[512];
        int row = 0;
        while(in.getline(buffer,512)){
            while (row < 9) {
                for (int n=0; n<9; n++) {
                    assert(buffer[n] == '.' || isdigit(buffer[n]));
                    board[row][n] = buffer[n];
                }
                row++;
                in.getline(buffer,512);
            }

            std::cout << ((row == 9) ? "Success!" : "Failed!") << std::endl;
            assert(row == 9);
        }
    }
    else std::cerr<<"File could not be opened\n";
}

/* internal helper function */
void print_frame(int row) {
    if (!(row % 3))
        std::cout << "  +===========+===========+===========+" << std::endl;
    else
        std::cout << "  +---+---+---+---+---+---+---+---+---+" << std::endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
    std::cout << (char) ('A' + row) << " ";
    for (int i=0; i<9; i++) {
        std::cout << ( (i % 3) ? ':' : '|' ) << " ";
        std::cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
    }
    std::cout << "|" << std::endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
    std::cout << "    ";
    for (int r=0; r<9; r++) 
        std::cout << (char) ('1'+r) << "   ";
    std::cout << std::endl;
    for (int r=0; r<9; r++) {
        print_frame(r);
        print_row(board[r],r);
    }
    print_frame(9);
}

/* add your functions here */

/* Goes through each cell in the board to check and return true if it is complete */
bool is_complete(const char board [9][9]){
    for (int row=0; row<9; row++){
        for (int n=0; n<9; n++){
            if (board[row][n]=='.'){
                return false;
            }
        }
    }
    return true;
}

/* modifies the board by making a move,
   but first checking if the input range is valid
   AND that the cell that the move is being made on is first empty '.'  */
bool make_move(const char position[2], int digit, char board [9][9]){
    /* the two lines below check for range validity of input char string*/
    if (position[0]>= 'A' && position[0]<='I'){
        if (position[1]>='1' && position[1]<='9'){
            /* if the range of the char string is valid,
               check if the board already has an existing datapoint in the position */
            int row = position[0]-'A';
            int column = position[1] - '1';
            if (board[row][column]=='.' && 
                    check_row(position, digit, board) &&
                    check_col(position, digit, board) &&
                    check_9cellgrid(position, digit, board) 
                    ){
                /* if all the checks above pass, then we update the board with the input digit
                   and return true to the boolean function */
                board[row][column] = digit;
                return true;
            }
        }
    }
    return false;
}


/* saves the current board into specified filename */
bool save_board(const char *filename, const char board [9][9]){
    std::ofstream outstream;
    outstream.open(filename);
    if(!outstream){
        return false;
    }
    assert(outstream);

    for(int row=0;row<9;row++){
        for(int n=0;n<9;n++){
            outstream<<board[row][n];
        }
        outstream<<std::endl;
    }
    outstream.close();
    return true;
}

/* check if the digit is repeated in it's own row */
bool check_row(const char move[2], int digit, const char board[9][9]){
    int row = move[0]-'A';
    int column = move[1]-'1';
    for (int u_column=0;u_column<9;u_column++){
        if (u_column!=column){
            if (board[row][u_column]==digit){
                return false;
            }
        }
    }
    return true;
}

/* check if the digit is repeated in it's own col */
bool check_col(const char move[2], int digit, const char board[9][9]){
    int row = move[0]-'A';
    int column = move[1]-'1';
    for (int u_row=0;u_row<9;u_row++){
        if (u_row!=row){
            if (board[u_row][column]==digit){
                return false;
            }
        }
    }
    return true;
}

/* check if the digit appears in the 9cell grid it is on,
   not including the move's own column and row
   since they are checked separately in the two functions above */
bool check_9cellgrid(const char move[2], int digit, const char board[9][9]){
    int row = move[0]-'A'; /* converting the location information to the board */
    int column = move[1]-'1';
    for(int r=((row/3)*3);r<(((row/3)*3)+3);r++){ /* finds the grid and loops from the starting row of the grid and  */ 
        if (r!=row){ /* excluding its own row */
            for(int c=((column/3)*3);c<(((column/3)*3)+3);c++){ /* loops from the starting col */ 
                if (c!=column){ /* excluding its own col */
                    if (board[r][c]==digit){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

/* recursive function to solve the sudoku board */
bool solve_board(char board[9][9]){
    /* check first if board is complete */
    if (is_complete(board)){
        return true;
    }
    /* find the first non-empty cell in the grid for each recursion and pass the location into the position variable */
    int r=0;
    int c=0;
    while(board[r][c]!='.'&&r<9){
        c++;
        if(c==9){
            c=0;
            r++;
        }
    }
    char position[2];
    position[0]='A'+r;
    position[1]='1'+c;
    for(int digit='1';digit<='9';digit++){
        if(make_move(position,digit,board)){
            if(solve_board(board)==false){
                board[r][c]='.'; //make_move cannot happen unless the cell is empty
            }
            else return true;
        }
    }
    board[r][c]='.';
    return false;
}


bool solve_board_trace(char board[9][9],long int &trace_b, long int &trace_i){
    /* check first if board is complete */
    if (is_complete(board)){
        return true;
    }
    /* find the first non-empty cell in the grid for each recursion and pass the location into the position variable */
    int r=0;
    int c=0;
    while(board[r][c]!='.'&&r<9){
        c++;
        if(c==9){
            c=0;
            r++;
        }
    }
    char position[2];
    position[0]='A'+r;
    position[1]='1'+c;
    for(int digit='1';digit<='9';digit++){
        if(make_move(position,digit,board)){
            if(solve_board_trace(board,trace_b,trace_i)==false){
                board[r][c]='.'; //make_move cannot happen unless the cell is empty
                trace_b++;
            }
            else return true;
        }
        trace_i++;
    }
    board[r][c]='.';
    return false;
}
