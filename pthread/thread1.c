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
  printf("%d\n",i);
  //printf("%d\n",i);
}

int main()
{
  pthread_t tid;
  pthread_create(&tid, NULL, add, NULL);
  //pthread_create(&tid1,NULL,add,NULL);
  int ret = pthread_join(tid, NULL);
  if(ret == 0)
      printf("wait done\n");
  else
      perror("pthread_join\n");
  printf("main thread\n");
  return 0;
}
