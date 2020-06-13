#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(){
  if((power(0,0) != 1) || (power(2,3) != 8)){
        return EXIT_FAILURE;
  }
  else if(power(0,10) != 0){
    return EXIT_FAILURE;
  }
  else if(power(10,0) != 1){
    return EXIT_FAILURE;
  }
  else if(power(-2,1) !=(unsigned) -2){
    return EXIT_FAILURE;
  }
  else if(power(2,32) != 0){
    return EXIT_FAILURE;
  }
  else
    return EXIT_SUCCESS;
  }
  
