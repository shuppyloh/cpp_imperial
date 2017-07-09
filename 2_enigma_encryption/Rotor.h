#ifndef ROTOR_H
#define ROTOR_H
#include"MachinePart.h"
class Rotor : public MachinePart{
  private:
    char *filename;
    int check_all_errors(ifstream &configFile,
        char *rotor_file,
        char* position_file);
    bool initialize_notch(); //check if rotation has hit a notch
    bool notch_array[alphab_index]; //array to hold notch values
  public:
    Rotor(); //customized constructor for Rotor (additional notch array)
    int setup(int rotor_location, char* rotor_file, char* position_file); 
    void rotate();
};

#endif
