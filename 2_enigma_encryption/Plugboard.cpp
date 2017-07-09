#include "Plugboard.h"



//helper function to check for all errors
int Plugboard :: check_all_errors(ifstream &configFile, char *filename){
  int temp_int=0; // int in file
  int temp_array[alphab_index]; //max array length for plugboard
  int fileposition=0;

  while(configFile>>temp_int>>ws){
    if (temp_int>(alphab_index-1) || temp_int<0){
      cerr << "Invalid index configuration in plugboard file "<<filename;
      cerr << endl;
      return INVALID_INDEX;
    }
    if (fileposition<alphab_index){
      temp_array[fileposition]=temp_int;
      for(int j=0;j<fileposition;j++){ //j is a prior position (check repeat)
        if (temp_array[fileposition]==temp_array[j]){
          cerr << "Impossible plugboard configuration in plugboard file ";
          cerr << filename<<endl;
          return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        }
      }
    }
    fileposition++;
  }
  if(!configFile.eof()){
    cerr << "Non-numeric character in plugboard file "<<filename<<endl;
    return NON_NUMERIC_CHARACTER;
  }
  // if after loop, location in file is odd or exceeds alphab_index
  if (fileposition%2!=0 || fileposition>alphab_index){
      cerr << "Incorrect number of parameters in plugboard file ";
      cerr << filename<<endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
return NO_ERROR;
}



//setting up the plugboard 
int Plugboard :: setup(char* filename){
  ifstream setup_stream;
  setup_stream.open(filename);
  if(setup_stream.fail()){
    setup_stream.close();
    cerr << "Error opening plugboard file "<<filename<<endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  //skip the whole encryption process if file is null or has no information
  if (setup_stream >> ws && setup_stream.eof()){
    return NO_ERROR;
  }

  //check for errors to return error code
  setup_stream.clear();
  setup_stream.seekg(0);
  int error_code=NO_ERROR;
  error_code=check_all_errors(setup_stream, filename);
  if(error_code!=NO_ERROR){
    setup_stream.close();
    return error_code;
  }

  //if no errors, begin encryption mapping process 
  setup_stream.clear();
  setup_stream.seekg(0);
  int encryption_evenIndex=0, encryption_oddIndex=0;
  while(setup_stream>>encryption_evenIndex){ 
    setup_stream>>encryption_oddIndex; 
    //swap values
    encryption_array[encryption_evenIndex] = encryption_oddIndex;
    encryption_array[encryption_oddIndex] = encryption_evenIndex;
  }
  setup_stream.close();
  return NO_ERROR; 
}
