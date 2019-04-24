#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"string.h"
#include"errno.h"
#include"fcntl.h"
#include"sys/stat.h"
int main(int argc,char* argv[]){
  mkfifo("tp",0664);
  int infd = open("abc",O_RDONLY);
  if(infd == -1){
    perror("open error");
    return -1;
  }  
  int outfd = open("tp",O_WRONLY);
  if(outfd == -1 ){
    perror("open error");
    return -1;
  }

  char buf[1024];
  int n;
  while((n = read(infd,buf,1024)) > 0){
      write(outfd,buf,n);
  }
  close(infd);
  close(outfd);
  return 0;
}
