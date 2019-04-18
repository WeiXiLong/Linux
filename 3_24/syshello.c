#include"stdio.h"
#include"stdlib.h"
#include"fcntl.h"
//#include"sys/types.h"
#include"stdio.h"
#include"unistd.h"
#include"sys/stat.h"
#include"string.h"
int main(){
 // umask(0);
 // int fd = open("myfile",O_WRONLY|O_CREAT,0664);
 // if(fd < 0){
 //   perror("open");
 //   return -1;
 // }
 // int count = 5;
 // const char* msg = "hello ChongQing!\n";
 // int len = strlen(msg);

 // while(count--){
 //   write(fd,msg,len);

 // }
  int fd = open("myfile",O_RDONLY);
  if(fd < 0){
    perror("open");
    return -1;
  }

  const char* msg = "hello bit\n";
  char buf[1024];
  while(1){
    ssize_t ret = read(fd,buf,strlen(msg));
    if(ret > 0){
      printf("%s",buf);
    }else{
      break;
    }
  }
  close(fd);
  return 0;
  
}
