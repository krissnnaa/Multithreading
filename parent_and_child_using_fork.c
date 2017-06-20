#include  <stdio.h>

#include  <unistd.h>

#define   COUNT 10

void  child_process()
{
     int   i;

     for (i = 1; i <= COUNT; i++)
     {
          printf("This statement is from child process with value = %d\n", i);
     }

     printf("==Child process is done==\n");
}

void  parent_process()
{
     int   i;

     for (i = 1; i <= COUNT; i++)
     {
          printf("This statement is from parent with value = %d\n", i);
     }
     
printf("==Parent process is done==\n");

}
             
void  main()
{
 
     pid_t pid;

     pid = fork();

     if (pid != 0)
     {

     	parent_process();     
     }

     else
     {
           child_process();
     } 
          
}



