#include"Reflector.h"



//helper function to check for errors---------------------
int Reflector :: check_all_errors(ifstream &configFile, char *filename){
  int temp_int=0; //int value in file
  int temp_array[alphab_index]={0}; //max array length for reflector
  int fileposition=0;

  while(configFile>>temp_int>>ws){
    if (temp_int>alphab_index-1|| temp_int<0){
      cerr << "Invalid index configuration in reflector file "<<filename<<endl;
      return INVALID_INDEX;
    }
    if (fileposition<alphab_index){
      temp_array[fileposition]=temp_int;
      for(int j=0;j<fileposition;j++){//j is a prior position (check repeat)
        if (temp_array[fileposition]==temp_array[j]){
          cerr << "ERROR INVALID REFLECTOR MAPPPING"<<endl;
          cerr << "Non-numeric character in reflector file "<<filename<<endl;
          return INVALID_REFLECTOR_MAPPING;
        }
      }
    }
    fileposition++;
  }
  if(!configFile.eof()){
    cerr << "Non-numeric character in reflector file "<<filename<<endl;
    return NON_NUMERIC_CHARACTER;
  }
  if (fileposition!=alphab_index){
    if (fileposition<alphab_index && fileposition%2==0){
      cerr << "Insufficient number of mappings in reflector file: ";
      cerr <<filename <<endl;
    }
    else {
      cerr << "Incorrect (odd) number of parameters in reflector file ";
      cerr <<filename <<endl;
    }
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  return NO_ERROR;
}



//setting up the Reflector --------------------------------
int Reflector :: setup(char* filename){
  ifstream setup_stream;
  setup_stream.open(filename);
  if(setup_stream.fail()){
    setup_stream.close();
    cerr << "Error opening reflector file "<<filename<<endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }


  //check for errors if file has information
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
    encryption_array[encryption_evenIndex] = encryption_oddIndex;
    encryption_array[encryption_oddIndex] = encryption_evenIndex;
  }
  setup_stream.close();
  return NO_ERROR; 
}
