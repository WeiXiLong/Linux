#include"sys/wait.h"
#include"stdio.h"
#include"unistd.h"
#include"string.h"
#include"stdlib.h"
int main(){
  int pipefd[2];
  if(pipe(pipefd) == -1){
    perror("pipe error");
    return -1;
  }
  pid_t pid = fork();
  if(pid < 0){
    perror("fork error");
    return -1;
  }else if(pid == 0){
    close(pipefd[0]);
    write(pipefd[1],"hello world",12);
  }else{
    close(pipefd[1]);
    char buf[1024] = {0};
    int tmp = read(pipefd[0],buf,1023);
    printf("read buf: [%d - %s]\n",tmp,buf);
  }
  return 0;
}
