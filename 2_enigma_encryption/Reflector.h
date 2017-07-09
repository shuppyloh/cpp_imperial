#ifndef REFLECTOR_H
#define REFLECTOR_H
#include "MachinePart.h"
class Reflector : public MachinePart{
  private:
  char* filename;
  int check_all_errors(ifstream &configFile, char* filename);
  public:
  int setup(char* filename);
};

#endif
