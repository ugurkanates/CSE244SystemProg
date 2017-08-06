#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>
#define MILLION 1000000L
/*

System Programming Midterm

17.04.2017 10.00 deadline
UGURKAN ATES 151044012

this is seeWhat

for more info & documentation please read my documentation file

last code entry:17.04.2017 02.24 *_*;





*/
static volatile int keepRunning = 1;
void intHandler(int dummy) {
    keepRunning = 0;

}
double determinant(double[20][20],double);
void cofactor(double [20][20],double);
void transpose(double x[20][20],double y[20][20],double);
void shift_inverse(double matrix[20][20],int n);

int main()
{
	FILE *fpe=fopen("seewhat.log","a+");
	 signal(SIGINT, intHandler);

	double result1;
	double og_det=0;
	long timedif;
   	struct timespec tpend, tpstart;
    int n=2;
      pid_t pid=1,pid2=getpid();
      int i,j;
      double matrix[20][20];
   char *myfifo2 = "/tmp/kek_fifo";
       int server_to_client;
   char *myfifo3 = "/tmp/fifor_fifo";
       int fifor;
       int forke=1;

   char str[BUFSIZ];
     fifor = open(myfifo3, O_RDONLY);
    	read(fifor,&pid,sizeof(pid));
        printf("pid %d\n",pid);

   close(fifor);
	unlink(myfifo3);

     server_to_client = open(myfifo2, O_RDONLY );

      read(server_to_client,matrix,sizeof(matrix));
      close(server_to_client);
 while(1){
 			if(keepRunning==0){
 				printf("parent pid is %d",pid);
 				kill(pid,SIGKILL);
 				printf("ctrl+c geldi\n seewhat clienta ,serveride vurcam");
 				exit(0);
 			}

 			

 			pid2=getpid();
 	      read(server_to_client,matrix,sizeof(matrix));
 	       		 og_det=determinant(matrix,2*n);
 	      if (clock_gettime(CLOCK_REALTIME, &tpstart) == -1) {
				perror("Failed to get starting time");
				return 1;
				}
				 	          shift_inverse(matrix,n);

			if (clock_gettime(CLOCK_REALTIME, &tpend) == -1) {
				perror("Failed to get ending time");
				return 1;
				}
				timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
(tpend.tv_nsec - tpstart.tv_nsec)/1000;
			fprintf(fpe,"%s\n","How long it taken to calculate Shifted_inverse matrix");
			fprintf(fpe,"%ld",timedif);
			result1=determinant(matrix,2*n);
			printf("The function_to_time took %ld microseconds\n", timedif);
 	          printf("determinant of random shifted_inverse Matrix in %lf \n",determinant(matrix,2*n));
 	          printf("PID%d -- RESULT1%lf-- RESULT 2\n",pid2,result1-og_det);
 		sleep(10);
	printf("no\n");

	printf("yes\n");
 	forke=fork();
 	if(forke){

 		printf("forke buyuktur >= parent olmali %d \n",forke);
     for(i = 0; i < 2*n; i++){
        for(j = 0; j < 2*n; j++){
            printf("%2f ",matrix[i][j]);
        }
        printf("\n");
    }
 		wait(0); //parent child bekliyo xd
 	}

 	else{
 		printf("forke =0  yani child %d \n",forke);

 		exit(0);
 	}
 		//sleep(5);
 	   kill(pid,SIGUSR1);


	}	

	fclose(fpe);
   return 0;
}





  





/*For calculating Determinant of the Matrix */
 /* k is size of matrix 2nx2n so we will send n*2 to function to calculate determinant for OG result */

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

void cofactor(double num[20][20],double f)
{
 double b[20][20];
 double fac[20][20];
 double donus[20][20];
 int p,q,m,n,i,j;
 for (q=0;q<f;q++)
 {
   for (p=0;p<f;p++)
    {
     m=0;
     n=0;
     for (i=0;i<f;i++)
     {
       for (j=0;j<f;j++)
        {
          if (i != q && j != p)
          {
            b[m][n]=num[i][j];
            if (n<(f-2))
             n++;
            else
             {
               n=0;
               m++;
               }
            }
        }
      }
      fac[q][p]=pow(-1,q + p) * determinant(b,f-1);
    }
  }

  transpose(num,fac,f);

}
/*Finding transpose of matrix*/  
void transpose(double num[20][20],double fac[20][20],double r)
{
	FILE *fp=fopen("seewhat.log","a+");
  int i,j;
  double b[20][20];
  double inverse[20][20];
  double d;
 	 fprintf(fp,"%s\n","there is OG   one");

  for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {

       	  fprintf(fp, "%lf\n",num[i][j] );

         b[i][j]=fac[j][i];
        }
    }
  d=determinant(num,r);
  for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {
        num[i][j]=b[i][j] / d;
        }
    }
   printf("\n\n\nThe inverse of matrix is : \n");
 	 fprintf(fp,"%s\n","there is shifted inverse one");

   for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {
         printf("\t%f",num[i][j]);
         fprintf(fp, "%lf\n",num[i][j] );
        }
    printf("\n");
     }
     fclose(fp);
}

void shift_inverse(double matrix[20][20],int n){
  double a[20][20];
  double b[20][20];
  double c[20][20];
  double d[20][20];

  int i,j,x,y;
  for( i=0,x=0;i<n;i++,x++)
   for( j=0,y=0;j<n;j++,y++)
    a[x][y]=matrix[i][j];
  for(x=0,i=n;i<2*n;i++,x++)
   for(y=0,j=0;j<n;j++,y++)
    b[x][y]=matrix[i][j];
  for( x=0,i=0;i<n;i++,x++)
   for(j=n,y=0;j<2*n;j++,y++)
    c[x][y]=matrix[i][j];
  for( i=n,x=0;i<2*n;i++,x++)
   for(y=0,j=n;j<2*n;j++,y++)
    d[x][y]=matrix[i][j];



  cofactor(a,n);
  cofactor(b,n);
  cofactor(c,n);
  cofactor(d,n);

  for( i=0,x=0;i<n;i++,x++)
   for( j=0,y=0;j<n;j++,y++)
    matrix[i][j]=a[x][y];
  for(x=0,i=n;i<2*n;i++,x++)
   for(y=0,j=0;j<n;j++,y++)
    matrix[i][j]=b[x][y];
  for( x=0,i=0;i<n;i++,x++)
   for(j=n,y=0;j<2*n;j++,y++)
    matrix[i][j]=c[x][y];
  for( i=n,x=0;i<2*n;i++,x++)
   for(y=0,j=n;j<2*n;j++,y++)
    matrix[i][j]=d[x][y];
   //for(i=0;i<n;i++){
    //for(j=0;j<n;j++)
     // printf("%lf ",b[i][j]);
    //ters alma cagir
    //determinantı loga yazdır
    //yerline koy Ana matris return et
    
}
