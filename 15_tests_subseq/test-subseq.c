#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);
int main()
{
  int array1[] ={ 1, 2, 1, 3, 5};
  int array2[] = { -1, 0, 6,7, 4, 5,9};
  int array3[] = {2,4,3,6,9,11,-3,4,6,5};
  int array4[] = {6,6,6,6,7};
  int array5[] ={-7};

  if(maxSeq(array1, 5) != 3){    
    printf("Failure on sequence 1, 2, 1, 3, 5\n");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(NULL, 0)) {
    printf("Failure: no array found\n");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array1, 0)) {
    printf("Failure on 1, 2, 1, 3, 5 for NULL\n");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array1, 5) != 3) {
    printf("Failure on 1, 2, 1, 3, 5\n");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array2, 7) != 4) {
    printf("Failure on -1, 0, 6,7, 4, 5,9\n");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array3, 9) != 4) {
    printf("Failure on 2,4,3,6,9,11,-3,4,6,5 \n");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array4, 5) != 2) {
    printf("Failure on 6,6,6,6,7\n");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array5, 1) != 1) {
    printf("Failure  on -7\n");
    exit(EXIT_FAILURE);
  }
  
  return EXIT_SUCCESS;
}
