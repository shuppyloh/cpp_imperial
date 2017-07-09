#include <fstream>
#include <iostream>

#include "errors.h"
#include "MachinePart.h" 
#include "Rotor.h"
#include "Plugboard.h"
#include "Reflector.h"

using namespace std;
const char ASCII_NEWLINE=10; 
const char ASCII_CARRIAGE_RETURN=13;
const char ASCII_SPACE=32;
const int MAXLEN=1024; //maximum character input length

//argv[0] is main
//argv[1] is plugboard
//argv[2] is reflector
//argv[2+1] last rotor (rotor 0th which is nearest to reflector)
//...
//argv[2+(argc-4)] first rotor (nearest to plugboard)
//argv[argc-1] is position file for rotors

int main (int argc, char* argv[]){

  //check for sufficient number of input file parameters
  if(argc<3){
    cerr << "usage: enigma plugboard-file reflector-file ";
    cerr << "(<rotor-file>* rotor-positions)?"<<endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  int error_int=NO_ERROR; //default no error before checks

  //determine number of rotors
  int number_of_rotors=0;
  number_of_rotors=(argc-4);
  if(number_of_rotors<0){
    number_of_rotors=0;
  } 

  //create Plugboard 
  Plugboard * plugboardPtr;
  plugboardPtr = new Plugboard();
  error_int=plugboardPtr->setup(argv[1]);
  if (error_int!=NO_ERROR){
    return error_int;
  }

  //create Reflector
  Reflector * reflectorPtr;
  reflectorPtr = new Reflector();
  error_int=reflectorPtr->setup(argv[2]);
  if (error_int){
    return error_int;
  }

  //create Rotor(s) from the left(nearest to reflector)
  Rotor * rotorArrayPtr[number_of_rotors];
  if(number_of_rotors>0){
    for (int i=0;i<number_of_rotors;i++){
      rotorArrayPtr[i] = new Rotor(); 
      //(i-th rotor (0th is leftmost), rotor filename, position filename)
      error_int=rotorArrayPtr[i]->setup(i, argv[3+i], argv[argc-1]);
      if (error_int!=NO_ERROR){
        return error_int;
      }
    }
  }

  //start to link parts by defining nextPtr in each machine part created
  if(number_of_rotors>0){
    //-1 to adjust position for rightmost rotor(leftmost rotor is indexed as 0)
    plugboardPtr->nextPtr = rotorArrayPtr[number_of_rotors-1];
    //loop from i=1 2nd leftmost rotor (i=0 rotor points to the reflector)
    for(int i=1;i<number_of_rotors;i++){  
      rotorArrayPtr[i]->nextPtr = rotorArrayPtr[i-1];
    }
    rotorArrayPtr[0]->nextPtr = reflectorPtr;
  }
  if(number_of_rotors==0){
    plugboardPtr->nextPtr = reflectorPtr;
  }

  //main program that takes input to encrypt and output
  char input_array[MAXLEN];
  cin.getline(input_array,MAXLEN);

  //start encrypting the input array, character by character
  char input_char;
  char output_char;
  for(int i=0; input_array[i]!='\0';){ //put input chars into an array
    input_char=input_array[i];
    if (input_char>='A' && input_char<='Z'){
      if(number_of_rotors>0){
        rotorArrayPtr[number_of_rotors-1]->rotate();//rotate BEFORE encrypt
      }
      int input_int;
      input_int=input_char-'A'; //convert to an input integer type
      MachinePart *firstobjPtr = plugboardPtr; //make plugboard first object
      firstobjPtr->encrypt(input_int); //start encryption
      if(input_int<0){//if fail, encrypt function sets input_int value as -1. 
        cerr<<"FATAL ERROR:"<<endl;
        cerr<<"Program not functioning properly";
        return 12;
      } 
      output_char=input_int+'A'; //convert integer output to char type
      cout<<output_char;
      i++;
    }
    else if 
      (input_char==ASCII_NEWLINE ||
       input_char==ASCII_CARRIAGE_RETURN ||
       input_char==ASCII_SPACE){
        i++;//skip spaces, newline, carriage return characters
      }
    else { //any other character returns error
      cerr<<input_char<<" is not a valid input character ";
      cerr<<"(input characters must be upper case letters A-Z)!"<<endl;
      return INVALID_INPUT_CHARACTER;
    }
  }
  //clean up
  delete plugboardPtr;
  delete reflectorPtr;
  for(int i=number_of_rotors; i>0; i--){
    delete rotorArrayPtr[i-1];
  }
  return 0; 
}
