#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
int counter;
pthread_mutex_t lock;

void* thread_func(void *arg)
{
    pthread_mutex_lock(&lock);

    unsigned int i;
    counter++;
    printf("\n Job %d started\n", counter);

    //Delay
    for(i=0; i<100000;i++);
  
    printf("\n Job %d finished\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}

void main()
{
	pthread_t tid1,tid2;

 	if (pthread_mutex_init(&lock, NULL) != 0)
    	{
        	printf("\n Mutex initialization failed\n");
        	exit(0);
    	}
  
        pthread_create(&tid1, NULL, &thread_func, NULL);
  	pthread_create(&tid2, NULL, &thread_func, NULL);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        pthread_mutex_destroy(&lock);

   
}
