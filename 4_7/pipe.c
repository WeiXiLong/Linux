#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"string.h"

int main(){
  int fds[2];
  char buf[100];
  int len;

  if(pipe(fds) == -1){
   perror("pipe error"),exit(1);
  }
  //read from stdin
  while(fgets(buf,100,stdin)){
    len = strlen(buf);
    //write into fds 
    if(write(fds[1],buf,len) != len){
      perror("write to pipe "); 
      break;
    }
    memset(buf,0x00,sizeof(buf));

    //read from pipe 
    if( (len =read(fds[0],buf,100)) == -1){
        perror("read form pipe");
        break;
    }

    //write to stdout
    if(write(1,buf,len) != len ){
      perror("write to stdout");
      break;
    }
  }
}

