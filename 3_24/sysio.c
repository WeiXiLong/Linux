#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"sys/stat.h"
#include"fcntl.h"
#include"string.h"
int main(){
  umask(0);
  int fd = open("myfile2",O_RDWR|O_CREAT|O_APPEND,0777);
  if(fd < 0){
    perror("open");
    return -1;
  }
  char buf[1024]  = "nihao~~~!!";
  int ret = write(fd,buf,strlen(buf));
  if(ret < 0){
    perror("write");
    return -1;
  }
  //off_t lseek(int fd, off_t offset, int whence); 
  //SEEK_SET
  //The offset is set to offset bytes.
  //SEEK_CUR
  //The offset is set to its current location plus offset bytes.
  //SEEK_END
  //The offset is set to the size of the file plus offset bytes.
  lseek(fd,0,SEEK_SET);
  memset(buf,0,sizeof(buf));
  ret = read(fd,buf,1023);
  if(ret < 0){
    perror("read error");
    return -1;
  }
  printf("read buf :[%s]\n",buf);
  close(fd);
  return 0;
}
