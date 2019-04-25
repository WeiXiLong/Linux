#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"signal.h"

struct sigaction oldact,act;

void handler(int signo){
  printf("recv signo:%d\n",signo);
  printf("pid : %d\n",getpid());
  sigaction(signo,&oldact,NULL);
}
int main(){
  act.sa_handler =  handler;
  act.sa_flags = 0;
  //清空信号集合set
  sigemptyset(&act.sa_mask);
  sigaction(SIGINT,&act,&oldact);

  while(1){
    printf("---------\n");
    sleep(1);
  }
}
