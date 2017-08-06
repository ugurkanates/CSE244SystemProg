#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

void main(){
	int piper[2];
	pid_t score;
	pipe(piper);
	for(int i=0;i<10;i++)
	{
		score=fork();

		if(score==0){
			int buffer[99]=getpid();
			close(piper[0]);
			write(piper[1],buffer,strlen((buffer)+1);

		}
		else(score>0){
			close(piper[1]);
			char readbuffer[99];
			read(piper[0],readbuffer,sizeof(readbuffer));
		}


	}
	
	printf("")
}