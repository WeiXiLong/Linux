#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"pthread.h"
pthread_mutex_t mutex;
int ticket = 100;
void* th_start(void* arg){
    //加锁需要在临界资源访问之前
    //int pthread_mutex_lock(pthread_mutex_t *mutex);
    //阻塞加锁加不上锁就会阻塞
    while(1){
    pthread_mutex_lock(&mutex);
    if(ticket >  0){
      usleep(1000);
      printf("yellow bull --%d--get a ticket:%d\n",(int)arg,ticket);
      ticket--;
    }else{
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    }
    //解锁需要在线程任意有可能退出的地方进行解锁
    pthread_mutex_unlock(&mutex);
  }
    return NULL;
}

int main(){
  pthread_t tid[4];
  int i = 0;
  pthread_mutex_init(&mutex,NULL);
  for(;i < 4 ; ++i){
    int ret = pthread_create(&tid[i],NULL,th_start,(void*)i);
    if(ret != 0){
      printf("yellow bull don't exit\n");
      return -1;
    }
  }
  for(i = 0; i < 4; ++i){
    pthread_join(tid[i],NULL);
  }
  pthread_mutex_destroy(&mutex);
  return 0;
}
