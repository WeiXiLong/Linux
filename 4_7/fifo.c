#include"stdio.h"
#include"stdlib.h"
#include"sys/stat.h"
int main(){
  mkfifo("fifo-p",0664);
  return 0;
}
