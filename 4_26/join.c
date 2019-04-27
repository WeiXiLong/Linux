#include"stdio.h"
#include"stdlib.h"
#include"pthread.h"
#include"unistd.h"
#include"errno.h"
void* th_start(void* arg){
    pthread_detach(pthread_self());
    pthread_exit("leihao");
    while(1){
     printf("Did this happen?\n");
     sleep(1);
    }
    return NULL;
}


int main(){
  pthread_t tid;
  int ret = pthread_create(&tid,NULL,th_start,NULL);
  if(ret != 0){
    printf("pthread create error\n");
    return -1;
  }
  sleep(1);
  char* retval = NULL;
  //分离后一般不适用等待，因为分离会使得资源回收
  //这一部分是矛盾测试
  int err = pthread_join(tid,(void**)&retval);
  if(err == EINVAL){
    printf("thread cannot be waited\n ");
  }
  printf("retval : %s\n",retval);
  while(1){
    printf("I am main thread\n");
    sleep(1);
  }
  return 0;
}
