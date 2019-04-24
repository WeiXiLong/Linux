#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"fcntl.h"
#include"sys/stat.h"
#include"string.h"
int main(){
  char *file = "./test.fifo";
  umask(0);
  int ret = mkfifo(file,0664);
  if(ret < 0){
      perror("mkfifo error");
      return -1;
  }
  printf("open file\n");
  int fd = open(file,O_WRONLY);
  if(fd < 0){
    perror("open error");
    return -1;
  }
  printf("open success!!\n");
  while(1){
    char buf[1024] = {0};
    scanf("%s",buf);
    write(fd,buf,strlen(buf));
  }
  close(fd);
  return 0;
}
