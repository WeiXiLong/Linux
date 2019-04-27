#include"stdio.h"
#include"unistd.h"
#include"pthread.h"
#include"unistd.h"



int main(){
  pthread_t tid;
  int ret = pthread_create(&tid,NULL,th_start,(void*)"");
  
  return 0;
}
