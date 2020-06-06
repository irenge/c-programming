#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
 /* int i,j;
  int len = strlen(str) - 1;
  char less[len+1];
  
  for (i = len, j = 0;j<= len ; i--,j++ ) 
    less[j] = str[i]; 
  for( i = 0 ; i <=len ; i++ )
    str[i] = less[i];


*/

 int j, i;
    int tmpry = 0;

    for(i=0; str[i] != 0; i++);
    for(j = 0; j <i/2; j++)
    {
        tmpry = str[j];
        str[j]=str[i - 1 - j];
        str[i - 1 - j] = tmpry;
    }
 
}
    
  

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's loj, Stardate 42523.7";
  char str4[] = "Hello, my name is Inijo Montoya.";
  char str5[] = "You can be my winjman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
