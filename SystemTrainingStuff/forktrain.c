#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

//usage of STDer important ! > no buffer so much much faster then Printf but not sure on fprintf or perror.
int main(int argc, char** argv) {
    pid_t childzeroerror=fork();
    int error;

    if(childzeroerror<0){
        perror("I couldn't create a fork process. NO pid for you #");
		error=errno;		
		exit(-1);
 
	}
    else if(childzeroerror==0){
        printf("i suc created a fork. \n");
        printf("My id is %d , my parent id is :%d \n",getpid(),getppid());
		execl("/bin/echo","echo","echo i am \n",NULL);
    }

    else {
    printf("i am return in Parent means that fork>0 \n");
    printf("my id is %d , which should be equal to Child id  , my parent id %d \n",childzeroerror,getpid()); 
	wait(NULL);    
	}
	
	sleep(60);	
    return 0;
}


