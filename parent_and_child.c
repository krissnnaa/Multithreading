#include<stdio.h>

#include<unistd.h>

int main()
{

	int pid;

	printf("Before the use of forking\n");
	
	printf("Parent process with ID %d\n",getpid());	

	pid=fork();

	printf("Just after forking\n");

	if(pid==0)
	{

		printf("I am a child process with ID %d\n",getpid());
	}
	
	else
	{
		printf("I am the parent process with PID %d\n",getpid());
	}

	return 0;
}
