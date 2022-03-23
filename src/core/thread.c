#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

void sthread(pthread_t thread_id)
{
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
}
   
int main(int argc, const char * argv[])
{
    pthread_t thread_id_a,thread_id_b;
    printf("Before Thread\n");

    sthread(thread_id_a);
    sthread(thread_id_b);

    printf("After Thread\n");
    exit(0);
}