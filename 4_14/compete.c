#include"stdio.h"
#include"stdlib.h"
#include"signal.h"
#include"unistd.h"
int a = 0;
int b = 0;

int add(){
  a++;
  sleep(10);
  b++;
  return a+b;
}

void handler(int signo){

  printf("signal------%d\n",add());
}

int main(){
    signal(SIGINT,handler);
    printf("main-------%d\n",add());
  return 0;
}
