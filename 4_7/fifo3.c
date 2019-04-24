#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"fcntl.h"

int main(){
  int outfd = open("abc.bak",O_WRONLY|O_CREAT|O_TRUNC,0664);
  if(outfd == -1){
      perror("open error");
      return -1;
  }
  int infd = open("fp",O_RDONLY);
  if(infd == -1){
      perror("open error");
      return -1;
  }
  
  char buf[1024];
  int n;
  while(n = read(infd,buf,1024) > 0){
      write(outfd,buf,n);
  }
  close(infd);
  close(outfd);
  unlink("tp");

  return 0;
  

  
  

}
