#ifndef MACHINEPART_H
#define MACHINEPART_H
#include"errors.h"
#include<iostream>
#include<fstream>

using namespace std;
class MachinePart{
  protected: 
    const static int alphab_index=26;//init 26 number of alphabets (A to Z)
    //every object holds an array to convert i to array[i]
    int encryption_array[alphab_index];     
    int rotation;  //rotation is a number between 0 and 25 (A=0)
    char *filename; //config filename underlying object
  public:
    MachinePart();
    MachinePart *nextPtr; //pointer to next object in machine
    int encrypt(int &the_input); //encrypt function to be called in main
    virtual void rotate(){}; //rotate function to increase rotation counter
    virtual ~MachinePart(){};
};


#endif
