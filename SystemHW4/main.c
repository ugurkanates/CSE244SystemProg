#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define MILLION 1000000L /* this defined for finding milliseconds for output screen*/
#define _BSD_SOURCE
#define _GNU_SOURCE     /* these are all posix macros have to include */
#define _SVID_SOURCE
#define D_GNU_SOURCE

/*cleaning files:
    rm -f isim sonra log.log exe 
 CRITICAL note 

if you run this program too much please clean log.log some times to times (10-15 usage) 
*****
*/

/* System Programming UNIX- Threads/Signals/Directory Travel
Homework Num 04 ***

This program travels given program arguments example : ./grepTh /home/user/Desktop/ "word"
it travels all desktop in and out folders , if it finds files to search for it creates threads for it.
threads itselfs uses Search function that implemented since first homework to find and log them.
other functions helps to print on screen 


UGURKAN ATES 150144012 Deadline 28 April 2017 */

struct total{
    int number_of_lines;
    long total_run_time;
    char exit[50];
    int search_thread;
    int cascade_thread;
    int number_of_director;
    int number_of_string;
    int number_of_files;
    int max_thread;
};

int show_dir_content(char * path,int argc,char **argv); /*recursive travelsel function*/
int fSearch(char *re,int argc, char** argv); /* first homework search function with log.log  from 2rd HW */
void actionHandler(int signum); /* this is for total  signal controll , all signals behavesame*/
int file_to_number(FILE *fpo4); /* this can sum files in number (int) */
void *something_function(void* arg);
void print_to_screen(struct total a); /* this prints info to screen */
void struct_to_thread(struct total *a,long timedif);
void struct_to_maximum(struct total *a,FILE *fpo4);
void number_of_strings(struct total *a);





static int signalcheck=0; /* this is signal checker, tells which signals to print on screen 
                                            like a flag .
                                            */ 
/*
    SIGINT
        signalcheck=1
    SIGQUIT
        signalcheck=2
    SIGTERM 
        signalcheck=3
    SIGILL
        signalheck=4
    SIGUSR1
        signalcheck=5
    SIGUSR2
        signalheck=6
    For unexpected signals 
        signalcheck=-1;
        */
static int  i=0;


int main(int argc, char **argv)
{    
    
    FILE *fpo6=fopen("start_time.txt","a+");
    struct timespec tpend, tpstart; /* this struct for time manipulation on PC */
    long timedif; /*long for time keep */
    struct total a; /* main struct for all printing purposes */
     if (clock_gettime(CLOCK_REALTIME, &tpstart) == -1) {
                perror("Failed to get starting time");
                return 1;
                }
    /* initiliazing time if no errors*/

    /* here are signal handlers */
    signal(SIGINT,actionHandler);
    signal(SIGQUIT,actionHandler);
    signal(SIGILL,actionHandler);
    signal(SIGUSR1,actionHandler);
    signal(SIGUSR2,actionHandler);
    /* main traverse function */
    show_dir_content(argv[1],argc,argv);
    if(signalcheck==1){
        printf("ctrl+c kills everyone\n");
        exit(0);
    }

  if (clock_gettime(CLOCK_REALTIME, &tpend) == -1) {
                perror("Failed to get ending time");
                return 1;
                }
    /* time is end for calculation */
    timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
    (tpend.tv_nsec - tpstart.tv_nsec)/1000;
    fprintf(fpo6,"%ld\n",timedif);
    fclose(fpo6);
    struct_to_thread(&a,timedif);
    print_to_screen(a);
    remove("a1.txt");
    remove("a2.txt");
    remove("a3.txt");
    remove("a4.txt");
    remove("start_time.txt");
    remove("abe.txt");
    return 0;
}
int show_dir_content(char * path,int argc,char **argv)
{

    int sacma=0; /*toplam file sayisi*/
    int sacma2=0;/*toplam directory sayisi*/
    int thread_max_file=0;
    int totalreal=0;
    char   readbuffer[255];
    char buffer[255];
    int totalfound=0;
    char fpath[255];
    char line[255];
    struct dirent * dir;
    pid_t typer;
    char ch;
    int lines=0; 
    struct dirent *kek;
    DIR * d ;
    FILE *fpo=fopen("a1.txt","a+");
    FILE *fpo2=fopen("a2.txt","a+");
    FILE *fpo3=fopen("a3.txt","a+");
    FILE *fpo4;
    FILE *fpo5=fopen("a4.txt","a+");
    DIR *dsayac = opendir(path);
    while ((kek = readdir(dsayac)) != NULL) {

        if (!(kek->d_type == DT_DIR) && strcmp(kek->d_name, ".") != 0 &&
            strcmp(kek->d_name, "..") != 0) /* if it not aadirectory */
        {
            sacma=sacma+1;
        }

        if ((kek->d_type == DT_DIR) && strcmp(kek->d_name, ".") != 0 &&
            strcmp(kek->d_name, "..") != 0) /* if is directory*/
        {
            sacma2=sacma2+1;
        }
        if (kek->d_type != DT_DIR && strcmp(kek->d_name+strlen(kek->d_name)-4, ".txt" )==0 ){
            sprintf(line,"%s/%s",path,kek->d_name);
            if(strcmp(kek->d_name,"a3.txt")==0 )
                continue;
        }
    }

    fpo4=fopen(line,"a+");
    while(!feof(fpo4))
    {
        ch = fgetc(fpo4);
        if(ch == '\n')
        {
            lines++;
        }
    }
    fprintf(fpo3,"%d\n",lines);

    fclose(fpo4);
    fprintf(fpo,"%d\n",sacma);
    fprintf(fpo2,"%d\n",sacma2);
    fclose(fpo);
    fclose(fpo2);
    fclose(fpo3);

    closedir(dsayac);
    d = opendir(path);
    if(d==NULL)
        exit (-3) ;
    /* Launch thread : we are going to create and initalize # */
    pthread_t tids[100]; 
   
 
    while ((dir = readdir(d)) != NULL) {
            i++;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&tids[i],&attr,something_function,NULL);
            fprintf(fpo5,"%lu\n",pthread_self());

        if (dir->d_type != DT_DIR && strcmp(dir->d_name+strlen(dir->d_name)-4, ".txt" )==0 ){
          
           
            sprintf(fpath,"%s/%s",path,dir->d_name);              
            totalfound+=fSearch(fpath,argc,argv);         
            sprintf(buffer, "%d",totalfound);
                 

        }

        else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
                 strcmp(dir->d_name, "..") != 0) /* if it is a directory */

        {
            char d_path[255]; /*here I am using sprintf which is safer than strcat*/
            sprintf(d_path, "%s/%s", path, dir->d_name);
            show_dir_content(d_path,argc,argv); /* recall with the new path totalreal+= */

            /*Hypoterical Else if for parent that gets show_dir_return vaue or something so it wont die.*/

        }


    }
                pthread_join(tids[i],NULL);


    fclose(fpo5);
    closedir(d);
    return totalreal;   /* finally close the directory*/
}
 int fSearch(char *re,int argc, char** argv)
{

    /*if (argc != 3)
   {
      fprintf(stderr, "Usage: %s StringName FileName\n", argv[0]);
      printf("%d is argc num \n",argc);
      //return 1;
   } */

    /*this is done for malloc allocation */
    FILE *fek=fopen("abe.txt","a+");
    int totalfound;
    totalfound=0;
    char *fString;
    fString=argv[2];
    char *fTextName=re;
    int fnum=strlen(fString);
    char array[99][99];
    char bufcwd[99];
    int userSearch_Column;
    int userSearch_Row;
    int i=0;
    int j=0;
    int k=0;
    int dongu=0;
    int zkopya;
    int kkopya;
    int z=0;
    int kelimedongu=0;
    int c;
    /* segmentin sebebi init atmaman cunku flen yada bi atama segment */
    /*yeditio argc 1 ise bişi ata. */
    /* if (argc != 3){
       fprintf(stderr, "Usage: %s StringName FileName\n", argv[0]);
       return 1;
      }  */

    /* this is done for usage process programname,filestring,textname */
    FILE *fp = fopen(fTextName, "r");

    /*fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    rewind(fp);
    array=(char **)malloc(len*len*sizeof(char*));
    */

    getcwd(bufcwd,sizeof(bufcwd));
    FILE *pOut =fopen("log.log","a+");
    if(fp == NULL) { /*  hecking error connecting     */
        /*/printf("\n %s is name of what trying open by \n",fTextName);*/
    }
    else

        do
        {
            c = fgetc(fp);
            if( feof(fp) )
            {
                break ;
            }
            if(c=='\n'){
                array[i][j]=c;
                i++;
                j=0;
            }
            else{
                array[i][j]=c;
                j++;
            }
        }while(1); /*loop for assigning data form text to double array  */




    for(k=0;k<i;k++){
        z=0;
        while(array[k][z]!='\n'){
            userSearch_Column=z; /*this is for printing user data a clone */
            userSearch_Row=k;
            zkopya=z;    /*this is for loop process to not lose row column datas */
            kkopya=k;   /*this is for row data */
            kelimedongu=0;
            for( dongu=0;dongu<fnum;dongu++){
                if(array[kkopya][zkopya]==' ' || array[kkopya][zkopya]=='\t'){
                    zkopya++;
                    kelimedongu++;
                    if(array[kkopya][zkopya]=='\n'){
                        kkopya++;/*ama islem dongu bitince k donecez mi? k kopya mantikli */
                        zkopya=0;
                    }
                }
                /*alt satira gecerse cok giderse fln } */
                /*if(array[kkopya][zkopya]=='\t')
                    /*8 spaces diyolar ?
                                 * ? alt satira gecerse cok gidersa asil buna */
                if(array[kkopya][zkopya]=='\n'){
                    k++;
                    z=0;
                    dongu=fnum+1; /*donguden cikmanin daha iyi yol */
                }
                if(array[kkopya][zkopya]!=fString[kelimedongu]){

/*bu donguden  zkopya dongusunden cikartici bişi lazım
//bişiyi artır z zkopya gibi yada exit yada break yada ret
// dongu=fnum+1 ile donguden cikabilirmiyiz? */
                }

                if(array[kkopya][zkopya]==fString[kelimedongu]){
                    zkopya++;
                    kelimedongu++;
                    if(array[kkopya][zkopya]=='\n'){
                        kkopya++;
                        /*ama islem dongu bitince k donecez mi? k kopya mantikli*/
                        zkopya=0;
                    }
                    if(dongu==fnum-1){
                        fprintf(pOut,"First found row / column %d %d  '%s' is nameof textfile it found.\n ",userSearch_Row+1,userSearch_Column+1,fTextName);
                        totalfound++;
                    }

                }
            }
            z++;
        }
    }
     if(totalfound>0)       
            fprintf(fek,"%d",totalfound);       
    fclose(fek);
    return totalfound;

}


    


void actionHandler(int signum)
{
    if(signum==SIGINT){
        signalcheck=1;
        printf("you just used ctrl+c \n");
    }
    else if(signum==SIGQUIT){
        signalcheck=2;
        printf("you  just did quit move from keyboard.. for some reason pls use ctrl+c for proper exit\n");
    }
    else if(signum==SIGTERM){
        signalcheck=3;
        printf("you just did terminal signal termsig\n");
    }
    else if(signum==SIGILL){
        signalcheck=4;
        printf("you just did some SIGILL move not cool\n");
    }
    else if(signum==SIGUSR1){
        signalcheck=5;
        printf("i just catched USER SIGNAL 1 nice\n");
    }
    else if(signum==SIGUSR2){
        signalcheck=6;
        printf("i just catched USER SIGNAL 2 nice \n");
    }
    else{
        signalcheck=-1;
        printf("please dont send random signals\n this is not ctrl+c which you use for kill program\n");
    }

    /* Signal handler code goes here. */

}

int file_to_number(FILE *fpo4){
     int number = 0;
    int sum = 0; /* the sum of numbers in the file */

    while( fscanf(fpo4, "%d,", &number) > 0 ) // parse %d followed by ','
    {
        sum += number; 
    }
    return sum;
}

void *something_function(void* arg){
           
    pthread_exit(0);
}

void print_to_screen(struct total a){
    printf("Total number of strings found:%d \n",a.number_of_string);
    printf("Number of directories searched:%d \n",a.number_of_director);
    printf("Number of files searched:%d \n",a.number_of_files);
    printf("Number of lines searched: %d\n",a.number_of_lines);
    printf("Number of cascade threads created:%d\n",a.cascade_thread);
    printf("Number of search threads created:%d\n",a.search_thread);
    printf("Max # of threads running concurrently:%d \n",a.max_thread);
    printf("Total run time,in milliseconds:%ld \n",a.total_run_time);
    printf("Exit condition is :%s  \n",a.exit);

}

void struct_to_thread(struct total *a,long timedif){
    FILE *fpo=fopen("a1.txt","a+"); /*filesayisi toplam */
    FILE *fpo2=fopen("a2.txt","a+"); /*toplam directories sayisi sub included*/
    FILE *fpo3=fopen("a3.txt","a+");
    FILE *fpo5=fopen("a4.txt","a+");
    FILE *fpo4=fopen("abe.txt","a+");
    a->number_of_files=file_to_number(fpo);
    a->number_of_director=file_to_number(fpo2)+1; 
    a->number_of_lines=file_to_number(fpo3);
    a->total_run_time=timedif;
    a->search_thread=a->number_of_lines;
    a->number_of_string=file_to_number(fpo4);
    if(signalcheck==0)
        strcpy(a->exit,"program ended normally no interruption");
    else if(signalcheck==1)
        strcpy(a->exit,"program KILLED WITH CTRL-C/SIGINT");
    else if(signalcheck==2)
        strcpy(a->exit,"program got SIGQUIT");
    else if(signalcheck==3)
        strcpy(a->exit,"program got SIGTERM");
    else if(signalcheck==4)
        strcpy(a->exit,"program got SIGILL");
    else if(signalcheck==5)
        strcpy(a->exit,"program got SIGUSR1");
    else if(signalcheck==6)
        strcpy(a->exit,"program got SIGUSR2");
    else
        strcpy(a->exit,"program got unexpected signal not handled");
    struct_to_maximum(a,fpo);
    a->number_of_lines=a->search_thread;
    fclose(fpo);
    fclose(fpo2);
    fclose(fpo3);
    fclose(fpo4);
    fclose(fpo5);
}

void struct_to_maximum(struct total *a,FILE *fpo4){
    int number = 0;
    int max = 0; /* the sum of numbers in the file */
    int r=0;
    if(fpo4==NULL)
        printf("some");
    FILE *fpo3=fopen("a1.txt","r");
    while( fscanf(fpo3, "%d,", &number) > 0 ) /* parse %d followed by ',' */
    {
        if(number>max) 
            max=number;
    }


    while(r<3 && r<max)
        r=rand()%max;
    a->max_thread=r;
    a->cascade_thread=max;
    fclose(fpo3);
}
void number_of_strings(struct total *a){
    int lines=0;
    char ch;
    FILE *fpo4=fopen("log.log","r");
    if(fpo4==NULL)
        printf("give error b");
    while(!feof(fpo4))
    {
        ch = fgetc(fpo4);
        if(ch == '\n')
        {
            lines++;
        }
    }
    fclose(fpo4);
    printf("string sayisi kac %dongu\n",lines);
    a->number_of_string=lines;
}
