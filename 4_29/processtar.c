#include"stdio.h"
#include"unistd.h"

int main(){
  char proc[200] = {0};
  char label[5] = "|/-\\";
  int i = 0;
  for(i = 0; i <= 100; ++i){
    proc[i] = '#';
    printf("[%-100s][%d%%][%c]\r",proc,i,label[i % 4]);
    fflush(stdout);
    usleep(5000);
  }
  printf("\n");
  return 0;
}
