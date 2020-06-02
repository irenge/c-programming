#include<stdio.h>

size_t maxSeq(int * array, size_t n) {
  if(n <= 0)
    return 0;
  
  size_t count = 1;
  int i;
  size_t seq = 1;
  for (i = 0; i< n; i++){
    if(array[i] > array[i-1]) {
      ++count;
      if ( count > seq ) 
	seq  = count;
    } else {
      count = 1;
    }
    
  }
  return seq;
}
