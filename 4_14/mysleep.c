#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"signal.h"
void handler(int signo){
    sleep(10);
}

int mysleep(int nsec){
  signal(SIGALRM,handler);
  sigset_t set,old;
  sigemptyset(&set);
  sigprocmask(SIG_BLOCK,&set,&old);
  alarm(nsec);

  sigprocmask(SIG_UNBLOCK,&set,&old);
  
  sigset_t mask;
  sigfillset(&mask);
  sigdelset(&mask,SIGALRM);
  sigsuspend(&mask);
  sigprocmask(SIG_SETMASK,&old,NULL);
  signal(SIGALRM,SIG_DFL);
}
int main(){
  signal(SIGQUIT,handler);
  mysleep(3);
  printf("-----------\n");
  return 0;
}
