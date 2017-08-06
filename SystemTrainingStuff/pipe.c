#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>

int function();



int main()
{
    int i;
    int     fd[2], nbytes = 0;
    pid_t   childpid;
    int 	returnval=0;
    char    string[] = "Hello, world!\n";
    char    readbuffer[80];
    char buffer[10];
    int r ;
    printf("random totly blimve %d \n",rand());
    for (i = 0; i < 2999; ++i)
    {
        pipe(fd);
        childpid = fork();
        
        if(childpid  == -1)
        {
            perror("fork");
            exit(1);
        }


        if(childpid == 0)
        {
        	
            /* Child process closes up input side of pipe */
            close(fd[0]);

            /* */
            
          	r=function();
        
            sprintf(buffer, "%d",r); 
            /* Send "string" through the output side of pipe */
            write(fd[1], buffer, (strlen(buffer)+1));
            exit(0);
        }
        else
        {
            
            /* Parent process closes up output side of pipe */
            close(fd[1]);
	
            /* Read in a string from the pipe */
            read(fd[0], readbuffer, sizeof(readbuffer));
            nbytes += atoi(readbuffer);
        }
    }

    while (wait(NULL) > 0);

   		printf("Toplam %d\n", nbytes);

    return(0);
}

int function(){
	//srand(time(NULL));
	//int r=rand();
	return 1;
}
