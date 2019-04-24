#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"sys/wait.h"
int main(){
  int pipefd[2];
  int ret = pipe(pipefd);
  if(ret < 0){
    perror("pipe error");
    return -1;
  }
  int pid1 = fork();
  if(pid1 ==  0){
   close(pipefd[0]);
   dup2(pipefd[1],1);
   execlp("ps","ps","-ef",NULL);
  }
  int pid2 = fork();
  if(pid2 == 0){
   close(pipefd[1]);
   dup2(pipefd[0],0);
   execlp("grep","grep","ssh",NULL);
  }
  close(pipefd[0]);
  close(pipefd[1]);
  waitpid(pid1,NULL,0);
  waitpid(pid2,NULL,0);
  return 0;
}


//root        996      1  0 14:18 ?        00:00:00 /usr/sbin/sshd
//root       2986    996  0 14:19 ?        00:00:00 sshd: admin [priv]
//admin      2991   2986  0 14:19 ?        00:00:06 sshd: admin@pts/0
//root       3275    996  0 14:26 ?        00:00:00 sshd: admin [priv]
//admin      3279   3275  0 14:26 ?        00:00:00 sshd: admin@pts/1
//admin      9697   9695  0 16:47 pts/1    00:00:00 grep ssh
//
//root        996      1  0 14:18 ?        00:00:00 /usr/sbin/sshd
//root       2986    996  0 14:19 ?        00:00:00 sshd: admin [priv]
//admin      2991   2986  0 14:19 ?        00:00:06 sshd: admin@pts/0
//root       3275    996  0 14:26 ?        00:00:00 sshd: admin [priv]
//admin      3279   3275  0 14:26 ?        00:00:00 sshd: admin@pts/1
//admin      9783   2994  0 16:52 pts/0    00:00:00 grep --color=auto ssh

