#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
int i = 0;
void *add(void* arg)
{
  (void)arg;
  //if(arg)
  //{
  //  printf("thread2\n");
  //  pthread_cancel((pthread_t)arg);
  //  pthread_exit(NULL);
  //}
  i++;
  //printf("%d\n",i);
  pthread_exit(NULL);
}

int main()
{
  pthread_t tid;
  pthread_create(&tid, NULL, add, NULL);
  pthread_t tid1;
  pthread_create(&tid1,NULL,add,NULL);
  printf("main thread\n");
  sleep(1);
  printf("i = %d\n",i);
  return 0;
}
