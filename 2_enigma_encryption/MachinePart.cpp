#include "MachinePart.h"

MachinePart :: MachinePart (){
  //encryption array (all subclasses have this array)
  for (int i=0; i<alphab_index; i++){
    encryption_array[i]=i;
  }
  //default null pointer, always null for reflector
  nextPtr = NULL;
  //default 0 rotation for rotors, always 0 for plugboard and reflector
  rotation = 0; 
}


int MachinePart :: encrypt(int &the_input){

  /* base case terminating condition nextPtr=NULL (in reflector);
     return the encrypted value out from reflector without further calls*/ 
  if(nextPtr==NULL){
    /*Input into object's encryption array adjusted by a +ve rotation
      %operation converts post-rotation numbers exceeding 25(26=0)*/ 
    the_input=(the_input+rotation)%alphab_index;
    /* Output from object's encryption array adjusted by a -ve rotation
       the + and % operations convert post-rotation numbers below 0 (-1=25)*/
    the_input=(encryption_array[the_input]-rotation+alphab_index)%alphab_index;
    return the_input;
  }

  /* else encrypt and recursively call until base case*/
  the_input=(the_input+rotation)%alphab_index;
  the_input=(encryption_array[the_input]-rotation+alphab_index)%alphab_index;
  the_input=(nextPtr->encrypt(the_input) + rotation) % alphab_index;

  /* After hitting reflector, exit each object from the reverse direction.
     The reverse encryption process does not incur rotations. */

  /* We first find the matching encrypted output value on array*/
  int output_index=0;
  while(encryption_array[output_index]!=the_input){
    output_index++;
    //should never happen if program is working properly.
    if(output_index>=(alphab_index)){       
      return -1;
    }
  }
  /* We then encrypt the value backwards by -ve rotations (we 'added' rotations
    as we were entering our machineparts. */
  the_input = (output_index-rotation+alphab_index)%alphab_index;
  return the_input;
}
