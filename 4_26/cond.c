#include"stdio.h"
#include"unistd.h"
#include"pthread.h"
pthread_mutex_t mutex;
int have_noodle = 1;
pthread_cond_t cond;
void* th_boss(void* arg){
  while(1){
    pthread_mutex_lock(&mutex);
    if(have_noodle == 1){
      //int pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);
      //cond:   条件变量
      //mutex:  互斥锁
      //pthread_cond_wait 中集合了解锁后挂起的操作（原子操作）
      //有可能没来得及挂起就已经有人唤醒了---白唤醒---导致死等
      pthread_cond_wait(&cond,&mutex);
    }
    //面被人买了，需要在做一碗
    printf("need to make a new noodel +1\n");
    have_noodle += 1;
    //唤醒至少一个等待的人
    //int pthread_con_signal(pthread_cond_t *cond);
    //广播唤醒，唤醒所有等待的人
    //int pthread_cond_broadcast(pthread_cond_t *cond);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
  }
  return NULL;
}

void* th_customer(void* arg){
  while(1){
    pthread_mutex_lock(&mutex);
    if(have_noodle == 0){
      //等待
      pthread_cond_wait(&cond,&mutex);
    }
    //有面吃
    printf("noodle have eaten \n");
    have_noodle -= 1;
    //吃碗面后还想吃一碗，因此执行唤醒老板的操作
    //先解锁，再唤醒；避免唤醒的时候出现别人的操作而没有解锁导致没写步骤消失
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
  }
  return NULL;
}

int main(){
  pthread_t tid1,tid2;
  pthread_cond_init(&cond,NULL);
  pthread_mutex_init(&mutex,NULL);
  int ret  = pthread_create(&tid1,NULL,th_boss,NULL);
  if(ret != 0){
    printf("create boss error\n");
    return -1;
  }
  ret = pthread_create(&tid2,NULL,th_customer,NULL);
  if(ret != 0){
    printf("create customer  error\n");
    return -1;
  }
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  //销毁条件变量
  
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);
  return 0;
}
