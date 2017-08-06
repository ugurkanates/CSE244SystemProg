/* piperead.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>

void err_sys(const char *msg);
void err_usr(const char *msg);

int main(int argc, char *argv[])
{
    int fd;
    int result, val;

    if (argc != 2) 
        err_usr("yanlis sayida arguman girildi!\n");

    if ((fd = open(argv[1], O_RDONLY)) < 0)
        err_sys("open");

    while ((result = read(fd, &val, sizeof(int))) > 0)
        printf("%d\n", val);

    if (result < 0)
        err_sys("read");

    close(fd);

    return 0;
}

void err_sys(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void err_usr(const char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}