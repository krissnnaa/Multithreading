#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
char buffer[3];
int count=2,n=0,c=0;
pthread_t producer_thread[3],supply_thread;
pthread_mutex_t Lock;
sem_t full,empty;
void *hotdog_maker_1(void *para) 
{
 	
 	sem_wait(&empty);
	pthread_mutex_lock(&Lock);
	if((count>=0)&&(n==0||n==2))
	{
		buffer[n]='S'; // S for sausage
		n++;
		if(n==3)
		{
			n=0;
		}
		count--;
		pthread_mutex_unlock(&Lock);
		sem_post(&full);	
		sleep(1);
	}
	pthread_exit(0);
	return 0;
}


void *hotdog_maker_2(void *para) 
{
 	sem_wait(&empty);
	pthread_mutex_lock(&Lock);
	if((count>=0)&&(n==1))
	{
		buffer[n]='B'; // B for bun
		n++;
		count--;
		pthread_mutex_unlock(&Lock);
		sem_post(&full);
		sleep(1);
	}
	pthread_exit(0);
	return 0;
}


void *hotdog_maker_3(void *para) 
{
 	sem_wait(&empty);
	pthread_mutex_lock(&Lock);
	if((count>=0)&&(n==0||n==2))
	{
		buffer[n]='M'; // M for mustard
		n++;
		count--;
   		pthread_mutex_unlock(&Lock);
		sem_post(&full);
		sleep(1);
	}	
	pthread_exit(0);
	return 0;
}


void *supply_func(void *para) 
{
 	sem_wait(&full);
	sem_wait(&full);
	pthread_mutex_lock(&Lock);
   	if(c==0)
	{
  		printf("\nSupplier supplies: %c and %c\n",buffer[0],buffer[1]);		
		buffer[0]='\0'; // Supplier vaccants buffer
		buffer[1]='\0';
		n=c;
		c=1;

	}
	
	else if(c==1)
	{
		printf("\nSupplier supplies: %c and %c\n",buffer[1],buffer[2]);		
		buffer[1]='\0'; // Supplier vaccants buffer
		buffer[2]='\0';
		n=c;
		c=2;
	}
	else
	{
  		printf("\nSupplier supplies: %c and %c\n",buffer[2],buffer[0]);		
		buffer[2]='\0'; // Supplier vaccants buffer
		buffer[0]='\0';
		n=2;
		c=0;

	}
	
	count=1;
	pthread_mutex_unlock(&Lock);
	sem_post(&empty);
	sem_post(&empty);
	sleep(1);
	pthread_exit(0);
	return 0;
}

void main()
{
	pthread_mutex_init(&Lock,NULL);
	sem_init(&full,0,0);
	sem_init(&empty,0,3);
	while(1)
	{
		pthread_create(&producer_thread[0],NULL,&hotdog_maker_1,NULL);
		pthread_join(producer_thread[0], NULL);
		pthread_create(&producer_thread[1],NULL,&hotdog_maker_2,NULL);
		pthread_join(producer_thread[1], NULL);		
		pthread_create(&producer_thread[2],NULL,&hotdog_maker_3,NULL);
		pthread_join(producer_thread[2], NULL);
		pthread_create(&supply_thread,NULL,&supply_func,NULL);
		pthread_join(supply_thread, NULL);
	
	}
}
