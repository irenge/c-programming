#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  if (str)
    {
      char * end = str + strlen(str) - 1;

      // swap the values in the two given variables
      // XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a,b) do\
	{\
	  a ^= b;\
	  b ^= a;\
	  a ^= b;\
	} while (0)

      // walk inwards from both ends of the string,
      // swapping until we get to the middle
      while (str < end)
	{
	  XOR_SWAP(*str, *end);
	  str++;
	  end--;
	}
      #   undef XOR_SWAP
    }
}





  /*char temp;
  size_t len = strlen(str) - 1;
  size_t i;
  size_t k = len;

  for(i = 0; i < len; i++)
    {
      temp = str[k];
      str[k] = str[i];
      str[i] = temp;
      k--;
  */
      /*As 2 characters are changing place for each cycle of the loop
	 only traverse half the array of characters */
  /*    if(k == (len / 2))
	{
	  break;
	}
    }
}


*/
/*//WRITE ME!
  int i,j;
  int len = strlen(str) - 1;
  char less[len];
  
  for (i = len, j = 0;j<= len ;  ) 
    less[j++] = str[i--];
  less[len] = '\0';
  for( i = 0 ; i <=len ; i++ )
    str[i] = less[i];
  str[i+1] = '\0';
}

*/

  /*
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
  */
/*
  char *p1 = str;
  char *p2 = str;

  while (*p1 != '\0')
    p
}
*/  

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
