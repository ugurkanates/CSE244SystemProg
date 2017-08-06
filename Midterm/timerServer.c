#define _POSIX_C_SOURCE 199309L

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
/*

System Programming Midterm

17.04.2017 10.00 deadline
UGURKAN ATES 151044012

this is timerServer

for more info & documentation please read my documentation file

last code entry:17.04.2017 02.24 *_*;





*/
#define MILLION 1000000L
void actionHandler(int signum);
void matrix_init(double m[20][20],int n);
void reset(double **m);
void randome(double myPointer[20][20],int n);
double determinant(double a[20][20],double k);
void sigHandler(int signum);


/*static volatile int keepRunning = 1;
void intHandler(int dummy) {
    keepRunning = 0;

}*/
static int signalcheck=0;
int main(int argc,char **argv)
{

	FILE *fp=fopen("timeserver.log","a+");
	if(argc!=4){
		printf("usage is:./timeServer <ticks in miliseconds> <n> <mainpipename>");
		exit(-99);
	}
	double det;
   	  int i,j;
   	  long timedif;
   	  struct timespec tpend, tpstart;
		
   	  int zaman=atoi(argv[1]);
      int n=atoi(argv[2]);
   	  //int n=2;
      char pipe_user[50];
      strcpy(pipe_user,argv[3]);
      pid_t pide=getpid();
      printf("pide is %d \n",pide);
	   struct sigaction action;
	   action.sa_handler=actionHandler; 
	   action.sa_flags = 0;

	   struct sigaction action2;
	   action2.sa_handler=sigHandler; 
	   action2.sa_flags = 0;


   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";
   int forke;
   int server_to_client;
   char *myfifo2 = "/tmp/kek_fifo";
   char *myfifo3 = "/tmp/fifor_fifo";
   int fifor;
   char buf[BUFSIZ];
   double M[20][20];
	matrix_init(M,n);
  
   /* create the FIFO (named pipe) */
 //  mkfifo(myfifo, 0666);
  mkfifo(myfifo2, 0666);
   mkfifo(myfifo3,0666);
   
   fifor =open(myfifo3,O_WRONLY);
   write(fifor,&pide,sizeof(pide));
   close(fifor);
   unlink(myfifo3);

   if ((sigemptyset(&action.sa_mask) == -1) ||
      (sigaction(SIGUSR1, &action, NULL) == -1))
      perror("Failed to install SIGURS1 signal handler");
   
   /* open, read, and display the message from the FIFO */
  // client_to_server = open(myfifo, O_RDONLY);
 	      if (clock_gettime(CLOCK_REALTIME, &tpstart) == -1) {
				perror("Failed to get starting time");
				return 1;
				}
					randome(M,n);
			if (clock_gettime(CLOCK_REALTIME, &tpend) == -1) {
				perror("Failed to get ending time");
				return 1;
				}
				timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
(tpend.tv_nsec - tpstart.tv_nsec)/1000;
  		fprintf(fp,"%ld %d %lf %s\n",timedif,pide,det,"in order time in ms,client pid(?),determinant");
   printf("Server ON.\n");
	         server_to_client = open(myfifo2, O_WRONLY );
	           write(server_to_client,M,sizeof(M));
         close(server_to_client);
         unlink(myfifo2);

         for(i = 0; i < 2*n; i++){
        for(j = 0; j < 2*n; j++){
            printf("%2f ",M[i][j]);
        }
        printf("\n");
    }
   while (1)
   {
   			

   			det=determinant(M,n);
   		 if (clock_gettime(CLOCK_REALTIME, &tpstart) == -1) {
				perror("Failed to get starting time");
				return 1;
				}
   					         randome(M,n);
   		if (clock_gettime(CLOCK_REALTIME, &tpend) == -1) {
				perror("Failed to get ending time");
				return 1;
				}
				timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
(tpend.tv_nsec - tpstart.tv_nsec)/1000;
		fprintf(fp,"%ld %d %lf %s\n",timedif,pide,det,"in order time in ms,client pid(?),determinant");


   		           write(server_to_client,M,sizeof(M));

      //while icinde ama read olacagi icin matrix gelene kdr beklicek xd :P i guess x_x? idk
      //matrix readlicek sonra ilk initler sanırım falan filen yada ustte
      //cocuk birini yapar diger digerini

	   
   if(signalcheck==1){
   //if signal arrived look compare some static data in sigaction i guess onu orrda artir bunun sonunda azlat
   forke=fork();
   if(forke==0){
      while(1){
      	sleep(10);
         randome(M,n);
         

       
         printf("matrix yarat\n");
         //sleep(5);
         //create matrix send to fifo bitchez
      }
   }
  
      // clean buf from any data 
     // memset(buf, 0, sizeof(buf)); */
         //sleep(5);
   }
   signalcheck=0;
   }

 //  close(client_to_server);
 //  close(server_to_client);
// unlink(myfifo);
  // unlink(myfifo2);
   return 0;
}
 void actionHandler(int signum)
{
    signalcheck=1;
      if(signum==SIGUSR1)
         printf("i catched signal USR1 code from client  i guess \n");
    /* Signal handler code goes here. */
   
}
void sigHandler(int signum)
{
    signalcheck=1;
      if(signum==SIGKILL)
         printf("CTRL + C geldi seeWhat . bye. \n");
     exit(0);
    /* Signal handler code goes here. */
   
}



void matrix_init(double m[20][20],int z){
    /* 
    this function purpose to create
    2Nx2N int matrix n being int z
    then initing this matrix to 0 before random numbers take in part
    it has error checks .
    blah!*/
    int i, j,n=z;
    double **k = (double **) malloc(n * sizeof(double*));

    if(m == NULL){
        printf("Error full matrix not created");
        exit(-1);
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            m[i][j] = 0;
        }
    }

}


 void reset(double** myPointer) {
    /*this functiono only resets heap memory taken with malloc early on.
     */
     if (myPointer) {
         free(*myPointer);
         *myPointer = NULL;
     }
 }

 void randome(double  myPointer[20][20],int n){
    int i,j;
    int r;
    srand ( time(NULL) );
    for(i=0;i<n*2;i++)
        for(j=0;j<n*2;j++)
            myPointer[i][j]=rand()%10;
 }

double determinant(double a[20][20],double k)
{
  double s=1,det=0;
  double b[20][20];
  int i,j,m,n,c;
  if (k==1)
    {
     return (a[0][0]);
    }
  else
    {
     det=0;
     for (c=0;c<k;c++)
       {
        m=0;
        n=0;
        for (i=0;i<k;i++)
          {
            for (j=0;j<k;j++)
              {
                b[i][j]=0;
                if (i != 0 && j != c)
                 {
                   b[m][n]=a[i][j];
                   if (n<(k-2))
                    n++;
                   else
                    {
                     n=0;
                     m++;
                     }
                   }
               }
             }
          det=det + s * (a[0][c] * determinant(b,k-1));
          s=-1 * s;
          }
    }

    return (det);
}
