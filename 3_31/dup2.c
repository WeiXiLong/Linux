#include "stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"fcntl.h"


int main(){
  int fd = open("log",O_RDWR|O_CREAT);
  if(fd < 0){
    perror("open error");
    return -1;
  }
  close(1);
  dup2(fd,1);
  for(;;){
    char buf[1024] = {0};
    ssize_t read_size = read(0,buf,sizeof(buf) - 1);
    if(read_size < 0){
      perror("read error");
      return -1;
      break;
    }
  printf("%s",buf);
  fflush(stdout);
  }
  return 0;
}
