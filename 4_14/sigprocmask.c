#include"stdio.h"
#include"signal.h"
#include"unistd.h"


void handler(int signo){
  printf("recv signo:%d\n",signo);
}

int main(){

  signal(SIGINT,handler);
  signal(SIGRTMIN+5,handler);
  //阻塞所有信号，当按下回车的时候恢复阻塞
  sigset_t set,oldset;
  sigemptyset(&set);

  sigfillset(&set);
  sigprocmask(SIG_BLOCK,&set,&oldset);
  printf("press ENTER to unblock\n");
  getchar();

  sigset_t pending;
  sigpending(&pending);
  int i = 0;
  for(i = 1; i < 64 ; ++i){
    if(sigismember(&pending,i)){
      printf("1 ");
    }else{
      printf("0 ");
    }
  }
  printf("\n");

  sigprocmask(SIG_UNBLOCK,&set,NULL);
}
