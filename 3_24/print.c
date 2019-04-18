#include"stdio.h"
#include"stdlib.h"
#include"string.h"

int main(){
  const char*msg = "Hello fwrite!\n";
  fwrite(msg,1,strlen(msg),stdout); 

  printf("hello printf\n");
  fprintf(stdout,"hello fprintf\n");
  
  return 0;
}
