#include "Rotor.h"



//helper function to check for errors
int Rotor :: check_all_errors(
    ifstream &configFile, char* rotor_file, char* position_file){
  int temp_int=0; //int in file
  int temp_array[alphab_index]; //max array length for first alphab_index 
  int fileposition=0;
  while(configFile>>temp_int>>ws){
    if (temp_int>alphab_index-1 || temp_int<0){
      cerr << "Invalid index configuration in rotor file "<<rotor_file<<endl;
      return INVALID_INDEX;
    }
    if(fileposition<alphab_index){
      //use temp_array to check for repeated numbers
      temp_array[fileposition]=temp_int;
      for(int j=0;j<fileposition;j++){
        if (temp_array[fileposition]==temp_array[j]){
          cerr <<"Invalid mapping of input "<<fileposition;
          cerr <<" to output "<<temp_int<<" (output ";
          cerr <<temp_int<<" is already mapped to from input "<<j<<")"<<endl;
          return INVALID_ROTOR_MAPPING;
        }
      }
      fileposition++; 
    }
  }
  if(!configFile.eof()){
    cerr << "Non-numeric character for mapping in rotor file "<<rotor_file;
    cerr <<endl;
    return NON_NUMERIC_CHARACTER;
  }
  if (fileposition<alphab_index){
    cerr << "Not all inputs mapped in rotor file: "<<rotor_file<<endl;
    return INVALID_ROTOR_MAPPING;
  }
  return NO_ERROR;
}

//construct array so it knows when to call the next rotor beside it to rotate
Rotor :: Rotor (){
  for (int i=0;i<alphab_index;i++){
    notch_array[i]=false;
  }
}

//checks if a notch is hit by a rotation  
bool Rotor :: initialize_notch(){
  if (notch_array[rotation]==true){
    return true;
  }
  return false;
}

//rotate function - the % operator adjust for post-rotation values above index
//25 + 1 = 0 (26%26)
void Rotor :: rotate(){
  rotation = (rotation+1)%alphab_index;
  if (initialize_notch()){
    nextPtr->rotate();
  }
}



//setting up the Rotor
int Rotor :: setup(int rotor_location, char* rotor_file, char* position_file) {

  //check rotor config file for errors
  ifstream setup_stream_config;
  setup_stream_config.open(rotor_file);
  if(setup_stream_config.fail()){
    setup_stream_config.close();
    cerr << "Error opening rotor file "<<rotor_file<<endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int error_code=NO_ERROR; 
  error_code=check_all_errors(setup_stream_config, rotor_file, position_file);
  if (error_code!=NO_ERROR){
    setup_stream_config.close();
    return error_code;
  }

  /*check the position file. there MUST be a position file if we count
    at least one rotor with a valid position number in the file.*/
  ifstream setup_stream_position;
  setup_stream_position.open(position_file);
  if(setup_stream_position.fail()){
    setup_stream_config.close();
    setup_stream_position.close();
    cerr << "Error opening position file "<<position_file<<endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  /*let's extract the pre-set rotations in the position file
    rotation is an int counter in the motherclass with default value 0
    by default all rotors do not have a preset rotation (rotation=0).
    rotor_location is passed into the constructor of this class with a
    min value of 0 (this is the left most rotor). */
  setup_stream_position.clear();
  setup_stream_position.seekg(0);
  if (setup_stream_position >> ws && setup_stream_position.eof()){
    cerr<<"No starting position for rotor "<<rotor_location;
    cerr<<" in rotor position file: "<<position_file<<endl;
    return NO_ROTOR_STARTING_POSITION;
  }

  /*if no errors and a position file exist
    let's build the encryption array for the rotor */
  setup_stream_config.clear();
  setup_stream_config.seekg(0);
  for(int i=0; i<alphab_index; i++){
    setup_stream_config>>encryption_array[i];
  }

  //after processing encryption array above, the setup_stream_config 'pointer'
  //should be placed just before the notch config numbers in the file
  int notch_index=0;
  while(setup_stream_config>>notch_index){
    notch_array[notch_index]=true;
  }

  //we then adjust the rotors using the preset rotation values in position 
  setup_stream_position.clear();
  setup_stream_position.seekg(0);
  int rotation_value=0;
  int rotor_in_position_file=0;

  //loop to assign right position in the position file depending on rotor_loc
  while(setup_stream_position>>rotation_value){
    if (!setup_stream_position.eof() &&
        rotor_in_position_file==rotor_location){
      rotation = rotation_value;
    }
    if (!setup_stream_position.eof()){
      rotor_in_position_file++;
    }
  }

  //if we are out of the loop before the file ends, non-numeric char error
  if(!setup_stream_position.eof()){
    cerr<< "Non-numeric character in rotor positions file "<<position_file;
    cerr<<endl;
    return NON_NUMERIC_CHARACTER;
  }
 
  //if we are out of the loop and the file ends, but cannot find a rotation
  //position in the file that corresponds to the rotor's location, error
  if (rotor_in_position_file<rotor_location){
    setup_stream_position.close();
    setup_stream_config.close();
    cerr<<"No starting position for rotor "<<rotor_location;
    cerr<<" in rotor position file: "<<position_file<<endl;
    return NO_ROTOR_STARTING_POSITION;
  }
  return NO_ERROR;
}
