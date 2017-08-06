#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>


// eger log log dosyasi  getcwd yerinde onu sil kendi acicak unutma fopen ;)

void err_sys(const char* x);
void createFIFO(char * path,int argc,char **argv);


int main(int argc, char **argv)
{


    //int x=show_dir_content(argv[1],argc,argv);
    createFIFO(argv[1],argc,argv);


  return 0;
}

void createFIFO(char * path,int argc,char **argv)
{

    char fifopath[300];
    DIR * d = opendir(path);
    if(d==NULL)
       perror("ow shit");
    struct dirent * dir;

    while ((dir = readdir(d)) != NULL) {

            if (dir->d_type != DT_DIR && strcmp(dir->d_name+strlen(dir->d_name)-4, ".txt" )==0 ){
                continue;
            }

            else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
                     strcmp(dir->d_name, "..") != 0) // if it is a directory

            {
                sprintf(fifopath,"%s/%s",path,"fifor");//creating fifo in path named fifo?
                //ex:char *myfifo="/home/username/Documents/mypipe";
                if (mkfifo(fifopath, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) < 0)
                    err_sys("mkfifo");
                char d_path[255]; // here I am using sprintf which is safer than strcat
                sprintf(d_path, "%s/%s", path, dir->d_name);
                show_dir_content(d_path,argc,argv); // recall with the new path

            }
    }

    closedir(d);
}

void err_sys(const char* x)
{
    perror(x);
    exit(1);
}