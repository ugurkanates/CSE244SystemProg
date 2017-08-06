	#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#define SIZE 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

void show_dir_content(char *path);
int fSearch(int argc, char** argv);
	

/* let us make a recursive function to print the content of a given folder */

void show_dir_content(char * path)
{
  DIR * d = opendir(path); // open the path
  if(d==NULL) return; // if was not able return
  struct dirent * dir; // for the directory entries
  while ((dir = readdir(d)) != NULL) // if we were able to read somehting from the directory
    {
      if(dir-> d_type != DT_DIR) // if the type is not directory just print it with blue
        printf("%s%s\n",BLUE, dir->d_name);
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // if it is a directory
      {
        printf("%s%s\n",GREEN, dir->d_name); // print its name in green
        char d_path[255]; // here I am using sprintf which is safer than strcat
        sprintf(d_path, "%s/%s", path, dir->d_name);
        show_dir_content(d_path); // recall with the new path
      }
	if ( strcmp(dir->d_name+strlen(dir->d_name)-4, ".txt") == 0 && score==0)
					 { 
							printf("%s \n",dir->d_name);
							printf("\n %s  \n ne geliyo \n",path);
							sprintf(clone_path, "%s/%s", path, dir->d_name);
							fSearch(argc,argv,clone_path);
							exit(1);//
    }
    closedir(d); // finally close the directory
}

int main(int argc, char **argv)
{

  printf("%s\n", NORMAL_COLOR);

    show_dir_content(argv[1]);

  printf("%s\n", NORMAL_COLOR);
  return(0);
}





/* UGURKAN ATES 151044012 

System Programming with C Homework 1 #
goals:find how many times a word repeats and which row/columns

*/

int fSearch(int argc, char** argv)
  {


	if (argc != 3)
   {	
      fprintf(stderr, "Usage: %s StringName FileName\n", argv[0]);
      return 1;
   }      
	
	
	size_t len = strlen(argv[0]);
	/*this is done for malloc allocation */
    int totalfound=0;
    char *fString=malloc(len+1);
	strcpy(fString,argv[1]);
    char *fTextName=malloc(len+1);
	strcpy(fTextName,argv[2]);	
    
	int fnum=strlen(fString);
    char array[SIZE][SIZE];
    int userSearch_Column;
    int userSearch_Row;
    int i=0;
    int j=0;
    int zkopya;
    int kkopya;
    int z=0;
    int kelimedongu=0;
    int c;
	// segmentin sebebi init atmaman cunku flen yada bi atama segment
    //yeditio argc 1 ise bişi ata.
  if (argc != 3){	
    fprintf(stderr, "Usage: %s StringName FileName\n", argv[0]);
    return 1;
   }  
   
   /* this is done for usage process programname,filestring,textname */
	FILE *fp = fopen(fTextName, "r");
	if(fp == NULL) /*  checking error connecting     */
		return -1; //error
	
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
 	
    // don't forget to terminate with the null character
    //code[n] = '\0';        	

			fclose(fp);

  for(int k=0;k<i;k++){
      z=0;
    while(array[k][z]!='\n'){
      userSearch_Column=z; /*this is for printing user data a clone */
      userSearch_Row=k;
      zkopya=z;    /*this is for loop process to not lose row column datas */
      kkopya=k;  	/*this is for row data */
      kelimedongu=0;
       for(int dongu=0;dongu<fnum;dongu++){
	if(array[kkopya][zkopya]==' ' || array[kkopya][zkopya]=='\t'){
	 zkopya++;
         kelimedongu++;
            if(array[kkopya][zkopya]=='\n'){
               kkopya++;//ama islem dongu bitince k donecez mi? k kopya mantikli
               zkopya=0;
            }
                                }
				//alt satira gecerse cok giderse fln }
				/*if(array[kkopya][zkopya]=='\t')
					//8 spaces diyolar ?
                                 * ? alt satira gecerse cok gidersa asil buna */
				if(array[kkopya][zkopya]=='\n'){
				  k++;
				  z=0;
				  dongu=fnum+1; //donguden cikmanin daha iyi yol
								}
				if(array[kkopya][zkopya]!=fString[kelimedongu]){
					
//bu donguden  zkopya dongusunden cikartici bişi lazım 
//bişiyi artır z zkopya gibi yada exit yada break yada ret
// dongu=fnum+1 ile donguden cikabilirmiyiz?
				}		
			
			if(array[kkopya][zkopya]==fString[kelimedongu]){		
		zkopya++;
                kelimedongu++;
                         if(array[kkopya][zkopya]=='\n'){
                            kkopya++;
                //ama islem dongu bitince k donecez mi? k kopya mantikli
                            zkopya=0;
                                                         }
                                     if(dongu==fnum-1){
  printf("First found row / column %d %d  '%s' is nameof textfile it found.\n ",userSearch_Row+1,userSearch_Column+1,fTextName);
					totalfound++;
							}
						
									}
									}			
			z++;	
			}
		} 
	  printf("Total Found number of  %s is %d \n",fString,totalfound);
	free(fString);
	return 0;

  }



//dynamic memory allocation(?*)
