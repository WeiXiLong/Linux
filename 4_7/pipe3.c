#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"


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
  }else if (pid == 0){
    close(pipefd[0]);
    write(pipefd[1],"hello world",11);
    
  }else{
    close(pipefd[1]);
    char buf[20] = {0};
    read(pipefd[0],buf,20);
    printf("buf = %s\n",buf);
  }
  return 0;
}
