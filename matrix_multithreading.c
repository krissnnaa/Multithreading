#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define M 3
#define N 3
#define K 2

int A [M][K] = { {1,1}, {2,2}, {3,3} };
int B [K][N] = { {1,2,3}, {4,5,6} };
int C [M][N];

struct element 
{
   int row; 
   int col; 
};

//The thread function for matrix multiplication
void *threadf(void *parameter) 
{
 	struct element *data = parameter; 
 	int n, sum = 0; 
   	//matrix multiplication
   	for(n = 0; n< K; n++)
	{
	        sum += A[data->row][n] * B[n][data->col];
	}
   
   	C[data->row][data->col] = sum;
   	pthread_exit(0);
}

int main(int argc, char *argv[]) 
{

	int i,j;
	for(i = 0; i < M; i++) 
	{
		for(j = 0; j < N; j++) 
		{
			//Assignment of a row and column for each thread
			struct element *data = (struct element *) malloc(sizeof(struct element));
         		data->row= i;
         		data->col = j;
         		pthread_t tid;   
			pthread_attr_t attr; 
			pthread_attr_init(&attr);  
         		pthread_create(&tid,&attr,threadf,data);
         		pthread_join(tid, NULL);
         	
      		}
   	}

   	// Result of matrix multiplication
   	for(i = 0; i < M; i++) 
	{
      		for(j = 0; j < N; j++) 
		{
	         	printf("%d ", C[i][j]);
     		}
      		printf("\n");
   	}
	return 0;
}


