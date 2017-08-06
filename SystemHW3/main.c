#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#define _BSD_SOURCE
#define _GNU_SOURCE
#define _SVID_SOURCE
#define D_GNU_SOURCE

/* eger log log dosyasi  getcwd yerinde onu sil kendi acicak unutma fopen ;) */
/*cleaning files:
    /*rm -f isim sonra log.log exe */

/* System Programming UNIX- Pipes and Forks 

UGURKAN ATES 150144012 Deadline 08 AM , 21 march 17 */

int show_dir_content(char * path,int argc,char **argv);
int fSearch(char *re,int argc, char** argv);
void createFIFO(char * path,int argc,char **argv);
void removeFIFO(char * path,int argc,char **argv);
int toplayiciFIFO(char *path,int argc,char **argv);
void err_sys(const char* x);


int main(int argc, char **argv)
{
    char if_fifo_already[255];
    sprintf(if_fifo_already,"%s/%s",argv[1],"fifor");
    if( access(if_fifo_already, F_OK ) != -1 ) {
        removeFIFO(argv[1],argc,argv);
    } else {
        ;
        }

    createFIFO(argv[1],argc,argv);
    show_dir_content(argv[1],argc,argv);
    toplayiciFIFO(argv[1],argc,argv);
    removeFIFO(argv[1],argc,argv);

    return 0;
}
int show_dir_content(char * path,int argc,char **argv)
{
    int fiforesult;
    int fdp,fdr;/* this is for fifo descriptor.*/
    int totalreal=0;
    int forksayisi=0;
    char readbuffer[380];
    char buffer[350];
    int totalfound=0;
    char fpath[100];
    DIR * d = opendir(path);
    if(d==NULL)
    return -3;
    struct dirent * dir;
    int piper[2];
    pid_t typer;
    FILE *fpz =fopen("odev.txt","a+");
    while ((dir = readdir(d)) != NULL) {
       /* printf("%s write fifosumus xd\n",fifopath); */



        pipe(piper);
        /*if (pipe2(piper,O_NONBLOCK) < 0)
            perror("pipe error not able to pipe correclty\n");//pipe2 O_NONBLOCK */
        typer = fork();

        if (typer == 0) {

            close(piper[0]);

            if (dir->d_type != DT_DIR && strcmp(dir->d_name+strlen(dir->d_name)-4, ".txt" )==0 ){
                sprintf(fpath,"%s/%s",path,dir->d_name);
                totalfound+=fSearch(fpath,argc,argv);
                sprintf(buffer, "%d",totalfound);
               /* write(piper[1], buffer, (strlen(buffer)+1)); */
            }

            else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
                     strcmp(dir->d_name, "..") != 0) /* if it is a directory */

            {

                char d_path[255]; /*here I am using sprintf which is safer than strcat*/
                sprintf(d_path, "%s/%s", path, dir->d_name);
                show_dir_content(d_path,argc,argv); /* recall with the new path totalreal+= */

            }
           /*close(piper[1]);*/
           /*printf(" bu exit calisiomu %d \n",totalfound);*/
            write(piper[1], buffer, (strlen(buffer)+1)); /*DT_DIR fifo 7 degilse bı*/


          /*  //if ((fdr = open(fifopath, O_WRONLY|O_NONBLOCK)) < 0)
            //    printf("%d\n",errno);


            //if (write(fdr, &totalfound, sizeof(int)) < 0)
               //     err_sys("write");
            //close(fdr); */
            exit(0);



        }
        else if(typer>0){
           /*close(piper[1]);
          //  printf("%d bu calismaz ama deneyek \n",piper[0]);
            //read(piper[0], readbuffer, sizeof(readbuffer));
            //sprintf(fifopath,"%s/%s",path,"fifor"); */

           int a=atoi(readbuffer);
          /*  sprintf(fifopath,"%s/%s",path,"fifor");

        
           /*printf("%d after total real %d \n",totalreal,getpid());
            //rintf("readbuffer ne okuyo %s s\n",readbuffer);
           // close(piper[0]);

            //break; */
        }
    }

    while (wait(NULL) > 0){
        close(piper[1]);
        read(piper[0], readbuffer, sizeof(readbuffer));
        int a=atoi(readbuffer);
        if(a==1 || a==3)
            perror("wrong\n");
        totalreal+=atoi(readbuffer);



    }/*waitpid -1 WNOHANG
                            //read pipe
                            //read fifo */
    closedir(d);
    forksayisi++;
    return totalreal;/* finally close the directory*/
}
int fSearch(char *re,int argc, char** argv)
{
    /*printf("%s %s are ecenin olacagi path , digeri aramazi kelime \n ",re,argv[2]);*/

    /*if (argc != 3)
   {
      fprintf(stderr, "Usage: %s StringName FileName\n", argv[0]);
      printf("%d is argc num \n",argc);
      //return 1;
   } */

    /*this is done for malloc allocation */
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
        }while(1); /*loop for assigning data form text to double array 	*/


    

    for(k=0;k<i;k++){
        z=0;
        while(array[k][z]!='\n'){
            userSearch_Column=z; /*this is for printing user data a clone */
            userSearch_Row=k;
            zkopya=z;    /*this is for loop process to not lose row column datas */
            kkopya=k;  	/*this is for row data */
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
  
    return totalfound;

}

void createFIFO(char * path,int argc,char **argv)
{
    char d_path[255];
    char fifopath[300];
    DIR * d = opendir(path);
    if(d==NULL)
       perror("ow t");
    struct dirent * dir;

    while ((dir = readdir(d)) != NULL) {

            if (dir->d_type != DT_DIR && strcmp(dir->d_name+strlen(dir->d_name)-4, ".txt" )==0 ){
                continue;
            }

            else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
                     strcmp(dir->d_name, "..") != 0) /* if it is a directory*/

            {
                sprintf(d_path, "%s/%s", path, dir->d_name);
                sprintf(fifopath,"%s/%s",d_path,"fifor");/*creating fifo in path named fifo?*/
                /*x:char *myfifo="/home/username/Documents/mypipe";*/
                if (mkfifo(fifopath, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) < 0)
                    err_sys("mkfifo");
                 /* here I am using sprintf which is safer than strcat */

                createFIFO(d_path,argc,argv); /* recall with the new path*/

            }
    }
    sprintf(fifopath,"%s/%s",argv[1],"fifor");
    mkfifo(fifopath, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    closedir(d);
}
int toplayiciFIFO(char * path,int argc,char**argv)
{
    char xyz[150];
    getcwd(xyz,sizeof(xyz));
    int ch=0;
    DIR * d = opendir(path); /*open path*/
    chdir(path);
    char d_path[255];
    char kopyapath[255];
    sprintf(kopyapath, "%s",path); /* slash eklencek*/
    char ame[255];
    int returnline=0;
    int j=0;
    int i=0;
     /* if was not able return*/
    struct dirent * dir; /* for the directory entries*/
    while ((dir = readdir(d)) != NULL)
    {
        if(dir-> d_type != DT_DIR){ /* if the type is not directory just print it with blue*/
                continue;
        }
        else if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0  )
        {
            /*
        sprintf(kopyapath, "%s/%s",path,dir->d_name); //  ama sonra ic icede ./b klaso
        ru ama ./a/b olmali counter tutmuyo napcaz acaba? /
           // getcwd(kopyapath,sizeof(kopyapath));
            sprintf(kopyapath, "%s/%s",path,dir->d_name); //  ama sonra ic icede ./b klasoru 
            ama ./a/b olmali counter tutmuyo napcaz acaba?

                //sprintf(kopyapath,"%s/%s",kopyapath,dir->d_name);
              //  chdir(kopyapath);
                //getcwd(ame,sizeof(ame));
              //  d=opendir(kopyapath); */
        }
    }
    closedir(d);

    sprintf(xyz,"%s/%s",xyz,"log.log");
    FILE *fp=fopen(xyz,"a+");
    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            returnline++;
        }

    }
    fprintf(fp,"total found num of %s is %d",argv[2],returnline);
    fclose(fp);

    return returnline;
}
/* ilk son pathi sonra yukari dogru cikian ya /slaha oku sondan txt okudugn gibi yada cd .. chdir gibi cikma varsa*/

void removeFIFO(char * path,int argc,char **argv)
{
    char d_path[255];
    char fifopath[300];
    DIR * d = opendir(path);
    if(d==NULL)
        perror("ow z");
    struct dirent * dir;

    while ((dir = readdir(d)) != NULL) {

        if (dir->d_type != DT_DIR && strcmp(dir->d_name+strlen(dir->d_name)-4, ".txt" )==0 ){
            continue;
        }

        else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
                 strcmp(dir->d_name, "..") != 0) /* if it is a directory */

        {
            sprintf(d_path, "%s/%s", path, dir->d_name);
            sprintf(fifopath,"%s/%s",d_path,"fifor");/*creating fifo in path named fifo? */
            /*ex:char *myfifo="/home/username/Documents/mypipe";*/
           /* if (mkfifo(fifopath, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) < 0)
              //  err_sys("mkfifo"); */
            unlink(fifopath);
            /* here I am using sprintf which is safer than strcat*/

            removeFIFO(d_path,argc,argv); /* recall with the new path*/

        }
    }
    sprintf(fifopath,"%s/%s",argv[1],"fifor");
    unlink(fifopath);
    /*mkfifo(fifopath, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);*/
    closedir(d);
}

void err_sys(const char* x)
{
    perror(x);
    exit(1);
}
