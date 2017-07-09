#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include "MachinePart.h"
class Plugboard : public MachinePart{
  private:
    char* filename;
    int check_all_errors(ifstream &configFile, char *filename);
  public:
    int setup(char* filename);
};

#endif
