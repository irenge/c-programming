#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  size_t i, j, len;

 len = strlen(str);
 if(len < 2)
   return;

  i = len-1 ;
  char strd[len];
  
  for( j = 0; j < len; j++) {
   
    strd[j] = str[i];
    i--;
  }
  strd[len] = '\0';
  //str = strd;
  for(i = 0; i< len; i++)
     str[i] =strd[i];
  str[len] = '\0';
  
}
  

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's loj, Stardate 42523.7";
  char str4[] = "Hello, my name is Inijo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
