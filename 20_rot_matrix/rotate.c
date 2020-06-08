/*void rotate(char matrix[10][10]) {
int i,j;
char temp[10][10];
for (i = 0; i< 10; i++) {
for (j = 0; j< 10;j++) {
        temp[i][j] = matrix[i][j];
        
}
}
for ( i = 0; i < 10 ; i++)   {
    
    for ( j = 0; j < 5; j++) {
      
      
      
      matrix[i][j]=temp[9-j][i];
      
    
      
    }
    
  }
}
*/

void swap(char *ptr1,char *ptr2){
  char temp;
  temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}
void rotate(char matrix[10][10]){
  int i = 0 , j = 0,k = 0;
  int len = 10,z = 10;
  
  for(i = 0, z = 9;i<len/2;i++,z--){
    for(j = i,k = z ;j<len-i-1;j++,k--){
      swap(&matrix[i][j],&matrix[j][z]);
      swap(&matrix[i][j],&matrix[k][i]);
      swap(&matrix[k][i],&matrix[z][k]);
    }
  }
  
}
